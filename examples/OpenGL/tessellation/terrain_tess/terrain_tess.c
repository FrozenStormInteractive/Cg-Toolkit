/* Terrain Tessellation
  Two different kinds of tessellation are performed: displacement and B-spline evaluation.

  In displacement, a texture is used which contains the height compontents and the tangent components
  of the terrain.  Tessellation is performed to sample the texture and displace the points.

  The other method is to displace only the control points (patch corners / support points ) and
  then evaluate a cubic b-spline curve smoothly over the entire domain.  This is useful for creating
  smooth terrain, such as a desert.  It is also useful for displacement mapping on top of
  the b-spline surface
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <GL/glew.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifdef _WIN32
#include <windows.h>
#endif

#include <Cg/cg.h>    /* Can't include this?  Is Cg Toolkit installed? */
#include <Cg/cgGL.h>

/* World manipulation */
#include "zpr.h"

/* Terrain texture */
#include "terrain.h"

/* Affects the size of the tessellated triangles in LOD dynamic mode. */
static int lodScalingFactor = 5;

/* Maximum tessellation level allowed -- Will be set in initialization to
 * the OpenGL implementation-specific value.  Default to 16.
 */
static GLfloat maxTessLevel = 32;

/* Minimum tessellation level allowed */
static GLfloat minTessLevel = 1.0f;

/* Wireframe mode (wireframe of tessellated triangles */
static int doWire = 0;

/* Draw patches different colors in a checker board pattern */
static int doPatchColor = 0;

/* Do level of detail determined by screenspace triangle size,
or determined by texcoord set (fixed) values. */
static int doLod = 0;

/* Textures used for displacement mapping */
static GLuint myDisplacementTexture = 0;

/* GLUT menu */
static unsigned int myGlutMenu;

/* Defaults for outer/inner tessellation parameters */
static float outer[4] = {16.0,16.0,16.0,16.0};
static float inner[2] = {16.0,16.0};

/* These parameters represent how many parametric / fixed patches are used in
    either the u patch axis or the v patch axis
    Default is 32,32.
*/
static int numPatchesU = 32;
static int numPatchesV = 32;

/* Draw the height data as a B-spline */
static int doBspline = 0;

/*  Corners of a quad which will be where tessellation lives.
    This treats the x-y plane as the plane for the terrain
*/
float myGroundVerts[4][3] =
{
  {-2.0,-2.0,0.0},
  {2.0,-2.0,0.0},
  {2.0,2.0,0.0},
  {-2.0,2.0,0.0}
};

const char * myProgramName = "Terrain Tessellation";

/* CgFX */

static CGcontext  myCgContext;

static CGeffect   myCgEffect;

static CGtechnique myCgTechnique;

static CGpass     myCgPass;

static CGparameter  myCgParameterModelView,
                    myCgParameterProjection,
                    myCgParameterInnerTess,
                    myCgParameterOuterTess,
                    myCgParameterDispTexture,
                    myCgParameterWH,
                    myCgParameterDoLod,
                    myCgParameterGroundWH;

static void checkForCgError(const char *situation)
{
  CGerror error;
  const char *string = cgGetLastErrorString(&error);

  if (error != CG_NO_ERROR) {
    printf("%s: %s: %s\n", myProgramName, situation, string);
    if (error == CG_COMPILER_ERROR) {
      printf("%s\n", cgGetLastListing(myCgContext));
    }
    exit(1);
  }
}

/* Forward declared GLUT callbacks registered by main. */
void displayfunc(void);
void menufunc(int val);
void keyboardfunc(unsigned char c, int x, int y);
void reshapefunc(int width, int height);

void initCgUniforms()
{
  myCgParameterModelView = cgGetNamedEffectParameter(myCgEffect, "modelView");
  checkForCgError("Getting the named parameter modelView from CgFX file");

  myCgParameterProjection = cgGetNamedEffectParameter(myCgEffect, "projection");
  checkForCgError("Getting the named parameter projection from CgFX file");

  myCgParameterInnerTess = cgGetNamedEffectParameter(myCgEffect, "innerTess");
  checkForCgError("Getting the named parameter innerTess from CgFX file");

  myCgParameterOuterTess = cgGetNamedEffectParameter(myCgEffect, "outerTess");
  checkForCgError("Getting the named parameter outerTess from CgFX file");

  myCgParameterDispTexture = cgGetNamedEffectParameter(myCgEffect, "displacementTexture");
  checkForCgError("Getting the named parameter displacementTexture from CgFX file");

  myCgParameterWH = cgGetNamedEffectParameter(myCgEffect, "wh");
  checkForCgError("Getting the named parameter wh from CgFX file");

  myCgParameterDoLod = cgGetNamedEffectParameter(myCgEffect, "doLod");
  checkForCgError("Getting the named parameter doLod from CgFX file");

  myCgParameterGroundWH = cgGetNamedEffectParameter(myCgEffect, "groundWH");
  checkForCgError("Getting the named parameter groundWH from CgFX file");
}

void initTexture()
{
  glGenTextures(1, &myDisplacementTexture);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, myDisplacementTexture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 512, 512, 0, GL_RGB, GL_FLOAT, terraintex);

  cgGLSetTextureParameter(myCgParameterDispTexture, myDisplacementTexture);
  checkForCgError("setting source displacement texture");

  cgSetSamplerState(myCgParameterDispTexture);
  checkForCgError("setting source displacement image texture state");
}

int main(int argc, char **argv)
{
  /* Cg version information */
  const char *versionStr = NULL;
  int versionMajor = 0, versionMinor = 0;

  glutInitWindowSize(500, 500);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInit(&argc, argv);
  glutCreateWindow(myProgramName);

  /* Create GLUT menu */
  myGlutMenu = glutCreateMenu(menufunc);

  glutAddMenuEntry("[b] Toggle between b-spline and regular displacement", (int) 'b');
  glutAddMenuEntry("[c] Toggle draw checker pattern exposing patches.", (int) 'c');
  glutAddMenuEntry("[ ] Pause the rotation", (int) ' ');
  glutAddMenuEntry("[9] Decrease speed (can go negative).", (int)'9');
  glutAddMenuEntry("[0] Increase speed.", (int)'0');
  glutAddMenuEntry("[w] Toggle wireframe mode.", (int) 'w');
  glutAddMenuEntry("[x] Toggle explicit and adaptive LOD", (int) 'x');
  glutAddMenuEntry("[8] Increase number of patches along the x direction.", (int) '8');
  glutAddMenuEntry("[i] Decrease number of patches along the x direction.", (int) 'i');
  glutAddMenuEntry("[7] Increase number of patches along the y direction.", (int) '7');
  glutAddMenuEntry("[u] Decrease number of patches along the y direction.", (int) 'u');
  glutAddMenuEntry("[]] Increase explicit outer tessellation level.", (int) ']');
  glutAddMenuEntry("[[] Decrease explicit outer tessellation level.", (int) '[');
  glutAddMenuEntry("[+] Increase explicit inner tessellation level.", (int) '+');
  glutAddMenuEntry("[-] Decrease explicit inner tessellation level.", (int) '-');
  glutAddMenuEntry("['] Increase adaptive LOD scaling factor.", (int) '\'');
  glutAddMenuEntry("[;] Decrease adaptive LOD scaling factor.", (int) ';');
  glutAddMenuEntry("[esc] Exit application.", 27 );

  glutAttachMenu(GLUT_RIGHT_BUTTON);

  glutReshapeFunc(reshapefunc);
  glutDisplayFunc(displayfunc);
  glutKeyboardFunc(keyboardfunc);

  /* Make sure at least OpenGL version 2.0 is being used */
  if (glewInit()!=GLEW_OK || !GLEW_VERSION_2_0) {
    fprintf(stderr, "%s: Failed to initialize GLEW. OpenGL 2.0 required.\n", myProgramName);
    exit(0);
  }

  /* Make sure gp5 is availible */
  if (!GLEW_NV_gpu_program5) {
    fprintf(stderr, "%s: NV_gpu_program5 not available.\n", myProgramName);
    exit(0);
  }

  /* Cg 3.0 is required for tessellation support */
  versionStr = cgGetString(CG_VERSION);
  if (!versionStr || sscanf(versionStr, "%d.%d", &versionMajor, &versionMinor)!=2 || versionMajor<3) {
    fprintf(stderr, "%s: Cg 3.0 required, %s detected.\n", myProgramName, versionStr);
    exit(0);
  }

  /* Camera */
  glMatrixMode(GL_MODELVIEW);

  gluLookAt(0.0,-3.0,1.0, 0.0,0.0,0.4, 0.0,1.0,0.0);

  zprInit(); /* Init the Zoom-Pan-Rotate class for camera control */

  zprSpinInit(20.0, 0.0, 0.0, 1.0); /* Init the spinner */

  /* Create CG context */
  myCgContext = cgCreateContext();
  checkForCgError("creating CG context");

  /* CgFX */
  cgGLRegisterStates(myCgContext);
  checkForCgError("Registering standard CgFX states");

  /* Let CG manage the texture parameters */
  cgGLSetManageTextureParameters(myCgContext, CG_TRUE);
  checkForCgError("Manage texture paranmeters");

  /* Create our CG effect from file */
  myCgEffect = cgCreateEffectFromFile( myCgContext, "terrain_tess.cgfx", NULL);
  checkForCgError("Creating terrainBezier.cgfx effect from file");

  /* Bind all parameters with CG effect uniforms */
  initCgUniforms();

  /* Initializes our dislpacement texture and sets the appropriate CG texture parameter/state */
  initTexture();

  glClearColor(0.8, 0.8, 0.8, 0.0);  /* Gray background */
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  /* Query GL for edge tessellation limit */
  glGetFloatv(GL_MAX_TESS_GEN_LEVEL, &maxTessLevel);

  glutMainLoop();
  return 0;
}

void updateCGUniforms( void )
{
  /* Get the width/height of the viewport to pass to the CG shader */
  GLint viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);

  cgSetParameter2f(myCgParameterWH, (viewport[2]*0.5)/lodScalingFactor, (viewport[3]*0.5)/lodScalingFactor);
  checkForCgError("Setting myCgParameterWH");

  /* Set modelview and projection, and inner/outer tessellation parameters. */
  cgSetParameter2fv(myCgParameterInnerTess, inner);
  checkForCgError("Setting myCgParameterInnerTess");

  cgSetParameter4fv(myCgParameterOuterTess, outer);
  checkForCgError("Setting myCgParameterOuterTess");

  cgSetParameter1i(myCgParameterDoLod, doLod);
  checkForCgError("Setting myCgParameterDoLod");

  cgSetParameter2f(myCgParameterGroundWH, myGroundVerts[1][0]-myGroundVerts[0][0],
                    myGroundVerts[3][1]-myGroundVerts[0][1]);
  checkForCgError("Setting myCgParameterGroundWH");

  cgGLSetStateMatrixParameter(myCgParameterModelView, CG_GL_MODELVIEW_MATRIX, CG_GL_MATRIX_IDENTITY);
  checkForCgError("Setting myCgParameterModelView");

  cgGLSetStateMatrixParameter(myCgParameterProjection, CG_GL_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);
  checkForCgError("Setting myCgParameterProjection");

  cgGLSetTextureParameter(myCgParameterDispTexture, myDisplacementTexture);
  checkForCgError("Setting myCgParameterDispTexture");

  if (doBspline)
    myCgTechnique = cgGetNamedTechnique(myCgEffect, "AdaptiveBspline");
  else
    myCgTechnique = cgGetNamedTechnique(myCgEffect, "AdaptiveTexcoord");
  checkForCgError("Setting myCgTechnique");

  myCgPass = cgGetNamedPass(myCgTechnique, "DoHeightColor");
  checkForCgError("Getting named pass from CgFX");

  cgSetPassState(myCgPass);
  checkForCgError("Setting pass state");
}

void disablePass()
{
  cgResetPassState(myCgPass);
  checkForCgError("Disabling CG pass");
}

void drawBsplinePatch( unsigned int patchu, unsigned int patchv, float elen[2] )
{
  static float coordx, coordy, texcoordx, texcoordy;
  int i, j;
  for (i = 0; i < 4; ++i)
  {
    for (j = 0; j < 4; ++j)
    {
      coordx = (myGroundVerts[0][0] - elen[0]) + elen[0]*patchu + j*elen[0];
      coordy = (myGroundVerts[0][1] - elen[1]) + elen[1]*patchv + i*elen[1];
      texcoordx = (coordx - myGroundVerts[0][0]) / fabs(myGroundVerts[1][0] - myGroundVerts[0][0]);
      texcoordy = (coordy - myGroundVerts[0][1]) / fabs(myGroundVerts[3][1] - myGroundVerts[0][1]);

      glTexCoord2f(texcoordx, texcoordy);
      glVertex3f(coordx, coordy, myGroundVerts[0][2]);
    }
  }
}

void drawPatch( unsigned int patchu, unsigned int patchv, float elen[2] )
{
  static float coordx, coordy, texcoordx, texcoordy;
  int i, j, cntrPnt;

  for (cntrPnt = 0; cntrPnt < 4; ++cntrPnt)
  {
    i = cntrPnt % 2;
    j = cntrPnt / 2;
    coordx = myGroundVerts[0][0] + elen[0]*patchu + i*elen[0];
    coordy = myGroundVerts[0][1] + elen[1]*patchv + j*elen[1];
    texcoordx = (coordx - myGroundVerts[0][0]) / fabs(myGroundVerts[1][0] - myGroundVerts[0][0]);
    texcoordy = (coordy - myGroundVerts[0][1]) / fabs(myGroundVerts[3][1] - myGroundVerts[0][1]);

    glTexCoord2f(texcoordx, texcoordy);
    glVertex3f(coordx, coordy, myGroundVerts[0][2]);
  }
}

void DrawGroundTexcoord()
{
  int udir, vdir;
  /* Length of each patch edge */
  float elen[2];

  elen[0] = fabs(myGroundVerts[1][0] - myGroundVerts[0][0]) / (float)numPatchesU;
  elen[1] = fabs(myGroundVerts[3][1] - myGroundVerts[0][1]) / (float)numPatchesV;

  glPatchParameteri(GL_PATCH_VERTICES, 4);
  glPatchParameterfv(GL_PATCH_DEFAULT_OUTER_LEVEL, outer);
  glPatchParameterfv(GL_PATCH_DEFAULT_INNER_LEVEL, inner);

  glBegin(GL_PATCHES);
  for (udir = 0; udir < numPatchesU; ++udir)
  {
    for (vdir = 0; vdir < numPatchesV; ++vdir)
    {
       if (doPatchColor)
       {
         if ( (udir-(vdir%2)) % 2)
           glColor3f(0.8,0.2,0.0);
         else
           glColor3f(0.2,0.8,0.0);
       }
       else
          glColor3f(1.0,1.0,1.0);

       drawPatch(udir, vdir, elen);
    }
  }
  glEnd();
}

void DrawGroundBspline()
{
  int udir, vdir;
  /* Length of each patch edge */
  float elen[2];

  elen[0] = fabs(myGroundVerts[1][0] - myGroundVerts[0][0]) / (float)numPatchesU;
  elen[1] = fabs(myGroundVerts[3][1] - myGroundVerts[0][1]) / (float)numPatchesV;

  glPatchParameteri(GL_PATCH_VERTICES, 16);
  glPatchParameterfv(GL_PATCH_DEFAULT_OUTER_LEVEL, outer);
  glPatchParameterfv(GL_PATCH_DEFAULT_INNER_LEVEL, inner);

  glBegin(GL_PATCHES);
  for (udir = 0; udir < numPatchesU; ++udir)
  {
    for (vdir = 0; vdir < numPatchesV; ++vdir)
    {
      if (doPatchColor)
       {
         if ( (udir-(vdir%2)) % 2)
           glColor3f(1.0,0.0,0.0);
         else
           glColor3f(0.0,1.0,0.0);
       }
       else
          glColor3f(1.0,1.0,1.0);

       drawBsplinePatch(udir, vdir, elen);
    }
  }
  glEnd();
}

void displayfunc(void)
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  if (doWire)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  glMatrixMode(GL_MODELVIEW);

  glPushMatrix();

  zprSpinDoRotate();

  updateCGUniforms();

  if (doBspline)
    DrawGroundBspline();
  else
    DrawGroundTexcoord();

  glPopMatrix();

  disablePass();

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glutSwapBuffers();
  glutPostRedisplay();
}

void reshapefunc(int width, int height)
{
  glViewport(0, 0, width, height);

  glutPostRedisplay();
}

void menufunc( int val )
{
  keyboardfunc( (unsigned char)val, 0, 0);
}

void keyboardfunc(unsigned char key, int x, int y)
{
    switch(key){
      case 'b' :
        doBspline = !doBspline;
        if (doBspline)
          printf(" Drawing terrain as a B-spline\n");
        else
          printf(" Drawing terrain as pure displacement mapping\n");
        break;

      case 'c' :
        doPatchColor = !doPatchColor;
        if (doPatchColor)
          printf("Drawing patches different colors.\n");
        else
          printf("Drawing based on height color.\n");
        break;

      case ' ':
        if (zprSpinToggle())
          printf("Spinning is toggled\n");
        else
          printf("spinning is untoggled\n");
        break;

      case '0':
        zprSpinOffsetSpeed(10.0f);
        printf("Increasing rotation speed\n");
        break;

      case '9':
        printf("Decreasing rotation speed\n");
        zprSpinOffsetSpeed(-10.0f);
        break;

      case 'w' :
        doWire = !doWire;
        if (doWire == 1)
          printf("Wireframe mode ON\n");
        else
          printf("Wireframe mode OFF\n");
        break;

      case 'x':
        doLod = !doLod;
        if (doLod)
          printf("Dynamic level of detail mode ON\n");
        else
          printf("Dynamic level of detail mode is OFF\n");
        break;

      case 'i' :
        numPatchesU -= numPatchesU <= 1 ? 0 : 1;
        printf("Number of patches in the x direction : %d\n", numPatchesU);
        break;

      case 'u' :
        numPatchesV -= numPatchesV <= 1 ? 0 : 1;
        printf("Number of patches in the y direction : %d\n", numPatchesV);
        break;

      case '8' :
        numPatchesU += 1;
        printf("Number of patches in the x direction : %d\n", numPatchesU);
        break;

      case '7' :
        numPatchesV += 1;
        printf("Number of patches in the y direction : %d\n", numPatchesV);
        break;

       case ']':
        outer[0] = outer[1] = outer[2] = outer[3] = ((outer[0] > maxTessLevel - 1)?
        maxTessLevel : (outer[0] + 1.0f));
        printf("Outer LOD levels increased to %f. (Max = %f)\n", outer[0],
        maxTessLevel);
        break;

      case '[':
        outer[0] = outer[1] = outer[2] = outer[3] = ((outer[0] < minTessLevel+1 )?
        minTessLevel : (outer[0] - 1.0f));
        printf("Outer LOD levels decreased to %f. (Min = 1.0)\n", outer[0]);
        break;

      case '+':
        inner[0] = inner[1] = (inner[0] > maxTessLevel - 1 ? maxTessLevel :
        (inner[0] + 1.0f));
        printf("Inner LOD levels increased to %f. (Max = %f)\n", inner[0],
        maxTessLevel);
        break;

      case '-':
        inner[0] = inner[1] = (inner[0] < minTessLevel+1 ? minTessLevel :
        (inner[0] - 1.0f));
        printf("Inner LOD levels decreased to %f. (Min = 1.0)\n", inner[0]);
        break;

      case '\'':
        lodScalingFactor+= 1;
        printf("Lod scaling factor: %d\n", lodScalingFactor);
        break;

      case ';':
        lodScalingFactor -= 1;
        if (lodScalingFactor <= 0)
          lodScalingFactor = 1;
        printf("Lod scaling factor: %d\n", lodScalingFactor);
        break;

      case 27:  /* Esc key */
        /* Demonstrate proper deallocation of Cg runtime data structures.
          Not strictly necessary if we are simply going to exit. */
        cgDestroyContext(myCgContext);
        exit(0);
        break;


    }; /* End switch */

  glutPostRedisplay();
}

