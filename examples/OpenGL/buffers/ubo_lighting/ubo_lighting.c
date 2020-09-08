
/* ubo_lighting.c - OpenGL-based Cg 3.1 example showing use
   of UBO buffers for material, lighting, and transforms. */

/* Requires the OpenGL Utility Toolkit (GLUT) and Cg runtime (version 3.1). */

#include <assert.h>   /* for assert */
#include <stdio.h>    /* for printf and NULL */
#include <stdlib.h>   /* for exit */
#include <string.h>   /* for memset */
#include <math.h>     /* for sin and cos */

#include <GL/glew.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifdef _WIN32
#include <GL/wglew.h>
#else
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#else
#include <GL/glxew.h>
#endif
#endif

#include <Cg/cg.h>    /* Can't include this?  Is Cg Toolkit installed? */
#include <Cg/cgGL.h>

#include "matrix.h"
#include "materials.h"
#include "request_vsync.h"

static CGcontext myCgContext;
static CGprofile myCgVertexProfile = CG_PROFILE_GP4VP;
static CGprogram myCgVertexProgram;
static CGparameter material_param, transform_param, lightSetStatic_param, lightSetPerView_param;
static CGbuffer *material_buffer, transform_buffer, lightSetStatic_buffer, lightSetPerView_buffer;
static GLuint *material_bufferGL, transform_bufferGL, lightSetStatic_bufferGL, lightSetPerView_bufferGL;

static int object_material[2] = { 0, 3 };
static int enableSync = 1;  /* Sync buffer swaps to monitor refresh rate. */

static const char *myProgramName = "ubo_lighting",

                  *myVertexProgramFileName = "ubo_lighting.cg",
#if 1
                  *myVertexProgramName = "vertex_lighting";
#else
                  *myVertexProgramName = "vertex_transform";
#endif

static void checkForCgError(const char *situation)
{
  CGerror error;
  const char *string = cgGetLastErrorString(&error);

  if (error != CG_NO_ERROR) {
    printf("%s: %s: %s\n",
      myProgramName, situation, string);
    if (error == CG_COMPILER_ERROR) {
      printf("%s\n", cgGetLastListing(myCgContext));
    }
    exit(1);
  }
}

/* Forward declared GLUT callbacks registered by main. */
static void display(void);
static void keyboard(unsigned char c, int x, int y);
static void menu(int item);
static void reshape(int width, int height);

void parameterBufferInfo(const char *name)
{
  CGparameter param = cgGetNamedParameter(myCgVertexProgram, name);

  printf("%s (0x%p):\n", name, param);
  printf(" index = %d\n", cgGetParameterBufferIndex(param));
  printf(" offset = %d\n", cgGetParameterBufferOffset(param));
}

typedef float float4x4[16];
typedef struct {
  float4x4 modelview;
  float4x4 inverse_modelview;
  float4x4 modelview_projection;
} Transform;

#define MAX_LIGHTS 8

typedef struct {
  int   enabled[4];
  float ambient[4];
  float diffuse[4];
  float specular[4];
  float k0[4], k1[4], k2[4];
} LightSourceStatic;

typedef struct {
  float global_ambient[4];
  LightSourceStatic source[MAX_LIGHTS];
} LightSet;

typedef struct {
  float position[4];
} LightSourcePerView;

typedef struct {
  LightSourcePerView source[MAX_LIGHTS];
} LightSetPerView;

LightSet lightSet;
LightSetPerView lightSetPerView_world, lightSetPerView_eye;

void initLight(LightSet *lightSet, int ndx)
{
  lightSet->source[ndx].enabled[0] = 1;
  lightSet->source[ndx].ambient[0] = 0;
  lightSet->source[ndx].ambient[1] = 0;
  lightSet->source[ndx].ambient[2] = 0;
  lightSet->source[ndx].ambient[3] = 0;
  lightSet->source[ndx].diffuse[0] = 0.9;
  lightSet->source[ndx].diffuse[1] = 0.9;
  lightSet->source[ndx].diffuse[2] = 0.9;
  lightSet->source[ndx].diffuse[3] = 0.9;
  lightSet->source[ndx].specular[0] = 0.9;
  lightSet->source[ndx].specular[1] = 0.9;
  lightSet->source[ndx].specular[2] = 0.9;
  lightSet->source[ndx].specular[3] = 0;
#if 1
  // Inverse square law attenuation
  lightSet->source[ndx].k0[0] = 0.7;
  lightSet->source[ndx].k1[0] = 0;
  lightSet->source[ndx].k2[0] = 0.001;
#else
  // No attenuation
  lightSet->source[ndx].k0[0] = 1;
  lightSet->source[ndx].k1[0] = 0;
  lightSet->source[ndx].k2[0] = 0;
#endif
}

void initBuffers(void)
{
  int i;

  memset(&lightSet, 0, sizeof(lightSet));
  lightSet.global_ambient[0] = 0.1;
  lightSet.global_ambient[1] = 0.1;
  lightSet.global_ambient[2] = 0.1;
  lightSet.global_ambient[3] = 0.1;

  initLight(&lightSet, 0);
  initLight(&lightSet, 1);

  lightSetPerView_world.source[0].position[0] = 0;
  lightSetPerView_world.source[0].position[1] = 2;
  lightSetPerView_world.source[0].position[2] = 4;
  lightSetPerView_world.source[0].position[3] = 1;

  lightSetPerView_world.source[1].position[0] = 0;
  lightSetPerView_world.source[1].position[1] = -2;
  lightSetPerView_world.source[1].position[2] = 4;
  lightSetPerView_world.source[1].position[3] = 1;

  material_param        = cgGetNamedProgramUniformBuffer(myCgVertexProgram, "MaterialBuffer");
  transform_param       = cgGetNamedProgramUniformBuffer(myCgVertexProgram, "TransformBuffer");
  lightSetStatic_param  = cgGetNamedProgramUniformBuffer(myCgVertexProgram, "LightSetStaticBuffer");
  lightSetPerView_param = cgGetNamedProgramUniformBuffer(myCgVertexProgram, "LightSetPerViewBuffer");


  /* Create transform */

  glGenBuffers(1, &transform_bufferGL);
  glBindBuffer(GL_UNIFORM_BUFFER, transform_bufferGL);
  glBufferData(GL_UNIFORM_BUFFER, 3*16*sizeof(float), NULL, GL_DYNAMIC_DRAW);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);

  transform_buffer = cgGLCreateBufferFromObject(myCgContext, transform_bufferGL, CG_FALSE);
  cgSetUniformBufferParameter( transform_param, transform_buffer );

  /* Create lightSet */

  glGenBuffers(1, &lightSetStatic_bufferGL);
  glBindBuffer(GL_UNIFORM_BUFFER, lightSetStatic_bufferGL);
  glBufferData(GL_UNIFORM_BUFFER, sizeof(lightSet), &lightSet, GL_STATIC_DRAW);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);

  lightSetStatic_buffer = cgGLCreateBufferFromObject(myCgContext, lightSetStatic_bufferGL, CG_FALSE);
  cgSetUniformBufferParameter( lightSetStatic_param, lightSetStatic_buffer );

  /* Create lightSetPerView */

  glGenBuffers(1, &lightSetPerView_bufferGL);
  glBindBuffer(GL_UNIFORM_BUFFER, lightSetPerView_bufferGL);
  glBufferData(GL_UNIFORM_BUFFER, sizeof(LightSetPerView), NULL, GL_DYNAMIC_DRAW);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);

  lightSetPerView_buffer = cgGLCreateBufferFromObject(myCgContext, lightSetPerView_bufferGL, CG_FALSE);
  cgSetUniformBufferParameter( lightSetPerView_param, lightSetPerView_buffer );

  /* Create material */

  material_buffer = malloc(sizeof(CGbuffer) * materialInfoCount);
  material_bufferGL = malloc(sizeof(GLuint) * materialInfoCount);

  /* Create a set of material buffers. */
  for (i=0; i<materialInfoCount; i++) {
    glGenBuffers(1, &material_bufferGL[i]);
    glBindBuffer(GL_UNIFORM_BUFFER, material_bufferGL[i]);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(MaterialData), &materialInfo[i].data, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    material_buffer[i] = cgGLCreateBufferFromObject(myCgContext, material_bufferGL[i], CG_FALSE);
  }

  checkForCgError("initBuffers");
}

int main(int argc, char **argv)
{
  int i;
  const char * listing = NULL;

  glutInitWindowSize(400, 400);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInit(&argc, argv);

  for (i=1; i<argc; i++) {
    if (!strcmp("-nosync", argv[i])) {
      enableSync = 0;
    }
  }

  glutCreateWindow(myProgramName);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutReshapeFunc(reshape);

  /* Initialize OpenGL entry points. */
  if (glewInit()!=GLEW_OK || !GLEW_VERSION_1_1) {
    fprintf(stderr, "%s: Failed to initialize GLEW. OpenGL 1.1 required.\n", myProgramName);    
    exit(1);
  }

  requestSynchronizedSwapBuffers(enableSync);
  glClearColor(0.2, 0.2, 0.2, 0.0);  /* Gray background */
  glEnable(GL_DEPTH_TEST);

  myCgContext = cgCreateContext();
  checkForCgError("creating context");

  cgSetContextBehavior(myCgContext,CG_BEHAVIOR_3100);
  if (cgGetContextBehavior(myCgContext)<CG_BEHAVIOR_3100) {
    fprintf(stderr, "%s: Cg 3.1 behavior required.\n", myProgramName);    
    exit(1);
  }

  cgGLSetOptimalOptions(myCgVertexProfile);
  checkForCgError("selecting vertex profile");

  myCgVertexProgram =
        cgCreateProgramFromFile(
          myCgContext,              /* Cg runtime context */
          CG_SOURCE,                /* Program in human-readable form */
          myVertexProgramFileName,  /* Name of file containing program */
          myCgVertexProfile,        /* Profile */
          myVertexProgramName,      /* Entry function name */
          NULL);                    /* extra compiler options */
  
  checkForCgError("creating vertex program from file");

  listing = cgGetLastListing(myCgContext);
  if (listing) {
    printf("listing:\n%s\n", listing);
  }

  cgGLLoadProgram(myCgVertexProgram);
  checkForCgError("loading vertex program");

  initBuffers();

  printf("program:\n%s\n", cgGetProgramString(myCgVertexProgram, CG_COMPILED_PROGRAM));

  glutCreateMenu(menu);
  glutAddMenuEntry("[ ] Animate", ' ');
  glutAddMenuEntry("[1] Update sphere 1", '1');
  glutAddMenuEntry("[2] Update sphere 2", '2');
  glutAddMenuEntry("[3] Change material of sphere 1", '3');
  glutAddMenuEntry("[4] Change material of  sphere 2", '4');
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  glutMainLoop();
  return 0;
}

float myProjectionMatrix[16];

static void reshape(int width, int height)
{
  double aspectRatio = (float) width / (float) height;
  double fieldOfView = 70.0; /* Degrees */

  /* Build projection matrix once. */
  makePerspectiveMatrix(fieldOfView, aspectRatio,
                        1.0, 20.0,  /* Znear and Zfar */
                        myProjectionMatrix);
  glViewport(0, 0, width, height);
}

static int myAnimating = 0;
static float eyeAngle = 1.6;

static void advance(int ignored)
{
  eyeAngle += 0.01;

  if (!myAnimating)
    return;  /* Return without rendering or registering another timer func. */

  glutPostRedisplay();
}

static void gl_loadRowMajorMatrix(GLenum matrixMode, const float mat[16])
{
  float transpose_mat[16];

  transposeMatrix(transpose_mat, mat);
  glMatrixMode(matrixMode);
  glLoadMatrixf(transpose_mat);
}

void renderLightPositions(const float projection[16], const float view[16])
{
  int i;

  gl_loadRowMajorMatrix(GL_PROJECTION, projection);
  gl_loadRowMajorMatrix(GL_MODELVIEW, view);
  for (i=0; i<2; i++) {
    if (lightSet.source[i].enabled[0]) {
      glPushMatrix();
        glTranslatef(lightSetPerView_world.source[i].position[0],
                     lightSetPerView_world.source[i].position[1],
                     lightSetPerView_world.source[i].position[2]);
        glColor3fv(lightSet.source[i].diffuse);
        glutSolidSphere(0.3, 10, 10);
      glPopMatrix();
    }
  }
}

void bind_material_buffer(int object)
{
    // Can also use cgSetUniformBufferParameter
    cgSetProgramBuffer(myCgVertexProgram, cgGetParameterBufferIndex(material_param), material_buffer[object_material[object]]);
}

void update_transform_buffer(Transform *transform)
{
  glBindBuffer(GL_UNIFORM_BUFFER, transform_bufferGL);
  glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Transform), transform);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

static void drawLitSphere(const float projectionMatrix[16], const float viewMatrix[16], int object, float xTranslate)
{
  Transform transform;
  float modelMatrix[16];

  makeTranslateMatrix(xTranslate, 0, 0, modelMatrix);
  multMatrix(transform.modelview, viewMatrix, modelMatrix);
  multMatrix(transform.modelview_projection, projectionMatrix, transform.modelview);
  invertMatrix(transform.inverse_modelview, transform.modelview);
  update_transform_buffer(&transform);

  bind_material_buffer(object);

  cgGLBindProgram(myCgVertexProgram);
  checkForCgError("binding vertex program");

  glColor3f(1,0,0);
  glutSolidSphere(2.0, 50, 50);
  cgGLUnbindProgram(myCgVertexProfile);
}

static void drawLitSpheres(const float projectionMatrix[16], const float viewMatrix[16])
{
  int i;

  cgGLEnableProfile(myCgVertexProfile);
  checkForCgError("enabling vertex profile");

  // For each light, convert its world-space position to eye-space...
  for (i=0; i<2; i++) {
    // Le[i] = V * Lw[i]
    transformVector(lightSetPerView_eye.source[i].position, viewMatrix,
      lightSetPerView_world.source[i].position);
  }

  // Update light set per-view buffer
  glBindBuffer(GL_UNIFORM_BUFFER, lightSetPerView_bufferGL);
  glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(lightSetPerView_eye), &lightSetPerView_eye);
  glBindBuffer(GL_UNIFORM_BUFFER, 0);

  // Draw two sphers
  drawLitSphere(projectionMatrix, viewMatrix, 0, 3.2);
  drawLitSphere(projectionMatrix, viewMatrix, 1, -3.2);

  cgGLDisableProfile(myCgVertexProfile);
  checkForCgError("disabling vertex profile");
}

static void drawScene(void)
{
  float eyePosition[4];
  float viewMatrix[16];

  // Update latest eye position.
  eyePosition[0] = 8*cos(eyeAngle);
  eyePosition[1] = 0;
  eyePosition[2] = 8*sin(eyeAngle);
  eyePosition[3] = 1;

  // Compute current view matrix.
  makeLookAtMatrix(eyePosition[0], eyePosition[1], eyePosition[2],  /* eye position */
                   0, 0, 0, /* view center */
                   0, 1, 0, /* up vector */
                   viewMatrix);

  drawLitSpheres(myProjectionMatrix, viewMatrix);
  renderLightPositions(myProjectionMatrix, viewMatrix);
}

static void display(void)
{
  if (myAnimating) {
    glutTimerFunc(10, advance, 0);
  }

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  drawScene();
  glutSwapBuffers();
}

static int currentLight = 0;

static void keyboard(unsigned char c, int x, int y)
{
  int i = 0;
  switch (c) {
  case 27:  /* Esc key */
    /* Demonstrate proper deallocation of Cg runtime data structures.
       Not strictly necessary if we are simply going to exit. */
    for( ; i < materialInfoCount; ++i ) {
        cgDestroyBuffer( material_buffer[i] );
    }
    cgDestroyBuffer( transform_buffer );
    cgDestroyBuffer( lightSetStatic_buffer );
    cgDestroyBuffer( lightSetPerView_buffer );

    glDeleteBuffers( materialInfoCount, material_bufferGL );
    glDeleteBuffers( 1, &transform_bufferGL );
    glDeleteBuffers( 1, &lightSetStatic_bufferGL );
    glDeleteBuffers( 1, &lightSetPerView_bufferGL );
    
    cgDestroyProgram(myCgVertexProgram);
    cgDestroyContext(myCgContext);
    
    free(material_buffer);
    free(material_bufferGL);
    
    exit(0);
    break;
  case ' ':
    myAnimating = !myAnimating; /* Toggle */
    if (myAnimating)
      advance(0);
    break;
  case '1':
    currentLight = 0;
    break;
  case '2':
    currentLight = 1;
    break;
  case 'k':
    lightSetPerView_world.source[currentLight].position[1] += 0.1;
    glutPostRedisplay();
    break;
  case 'j':
    lightSetPerView_world.source[currentLight].position[1] -= 0.1;
    glutPostRedisplay();
    break;
  case 'a':
    lightSetPerView_world.source[currentLight].position[2] += 0.1;
    glutPostRedisplay();
    break;
  case 'z':
    lightSetPerView_world.source[currentLight].position[2] -= 0.1;
    glutPostRedisplay();
    break;
  case 'h':
    lightSetPerView_world.source[currentLight].position[0] -= 0.1;
    glutPostRedisplay();
    break;
  case 'l':
    lightSetPerView_world.source[currentLight].position[0] += 0.1;
    glutPostRedisplay();
    break;
  case '3':
    object_material[0]++;
    if (object_material[0] >= materialInfoCount) {
      object_material[0] = 0;
    }
    glutPostRedisplay();
    break;
  case '4':
    object_material[1]++;
    if (object_material[1] >= materialInfoCount) {
      object_material[1] = 0;
    }
    glutPostRedisplay();
    break;
  }
}

static void menu(int item)
{
  /* Pass menu item character code to keyboard callback. */
  keyboard((unsigned char)item, 0, 0);
}
