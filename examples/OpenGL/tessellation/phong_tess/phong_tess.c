/* Implents Phong tessellation
 * Please see ReadMe.txt for information on how to use this program.
 * Please see the below reference about algorithmic details.
 */

/* Phong tessellation reference:

    Phong tessellation,
    Tamy Boubekeur and Marc Alexa
    ACM ToG, Vol. 27, No. 5, 2008.
*/

#include <GL/glew.h>

# ifdef _WIN32
# include <GL/wglew.h>
#else
# ifndef __APPLE__
#  include <GL/glxew.h>
# endif
#endif

#ifdef __APPLE__
# include <GLUT/glut.h>
#else
# include <GL/glut.h>
#endif

#include <Cg/cg.h>
#include <Cg/cgGL.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Baked-in monkey_head model */
#include "monkey_head.h"

/* Bunny and armadilloman taken and modified from
    The Stanford 3D Scanning Repository
    http://graphics.stanford.edu/data/3Dscanrep/
*/

/* Baked-in bunny model */
#include "bunny_1k.h"

/* Baked-in armadilloman model */
#include "armadillo_500.h"

/* Model manipulation */
#include "zpr.h"

/* Application specific state flags */

/* Maximum tessellation level allowed -- Will be set in initialization to
 * the OpenGL implementation-specific value.
 */
static GLfloat maxTessLevel;

/* Minimum tessellation level allowed */
static GLfloat minTessLevel = 1.0f;

/* Wireframe mode (wireframe of tessellated triangles */
static int doWire = 0;

/* Do level of detail determined by screenspace triangle size,
or determined by texcoord set (fixed) values. */
static int doLod = 0;

/* Whether to draw the control cage wires */
static int doDrawControlCage = 0;

/* Whether or not to draw the control cage wires which are behind the model */
static int doDrawHiddenControlCage = 1;

/* Show specular component */
static int doSpecular = 1;

/* Whether to outline patches of the model */
static int doPatchOutline = 0;

/* OpenGL Globals */

/* Menu for GLUT */
static unsigned int myGlutMenu;

/* Light position */
static float myLightPos[3] = { 1.5f, 2.0f, 2.0f };

/* Curve parameter for Phong tessellation (0 is linear interpolation)*/
static float myCurveParam = 0.75f;

/* Affects the size of the tessellated triangles in LOD dynamic mode. */
static int lodScalingFactor = 10;

/* The current model vertices we are working on */
GLfloat * myVerts;

/* The current model normals we are working with */
GLfloat * myNorms;

/* The current face index values we are working with */
const GLint * myFaces;

/* The number of vertices */
int myNumVerts;

/* The number of faces */
int myNumFaces;

/* Cg Globals */
static CGcontext  myCgContext;              /* CG context */

static CGprofile  myCgVertexProfile,        /* CG profile */
                  myCgTessControlProfile,
                  myCgTessEvalProfile,
                  myCgFragmentProfile;

static CGprogram  myCgVertexProgram,        /* CG program */
                  myCgTessControlProgram,
                  myCgTessEvalProgram,
                  myCgFragmentProgram;

/* CG uniform parameters */
static CGparameter myCgModelViewProjection,
                   myCgModelView,
                   myCgProjectionTE,
                   myCgWH,
                   myCgLodFlag,
                   myCgOuterLOD,
                   myCgInnerLOD,
                   myCgLightPos,
                   myCgDoPatchOutline,
                   myCgCurveParam,
                   myCgDoSpecular,
                   myCgScale;


/* Entry points and filenames. */
static const char *myProgramName = "Phong Tessellation",
                  *myVertexProgramFileName = "phong_tess_vp.cg",
                  *myVertexProgramName = "main",
                  *myTessControlProgramFileName = "phong_tess_tcp.cg",
                  *myTessControlProgramName = "main",
                  *myTessEvalProgramFileName = "phong_tess_tep.cg",
                  *myTessEvalProgramName = "main",
                  *myFragmentProgramFileName = "phong_tess_fp.cg",
                  *myFragmentProgramName = "main";

/* Forward declared callbacks for GLUT. */
void displayfunc( void );
void menuFunc( int );
void keyboardfunc(unsigned char, int, int);

/* Checks for CG errors and if a shader compile error, will return
 * the compiler string
 */
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

/* Defaults for outer/inner tessellation parameters */
float outer[3] = {16.0,16.0,16.0};
float inner[1] = {16.0};

/* Switches to the next model */
void nextModel()
{
  static int currModel = -1;
  currModel = (currModel + 1) % 3;

  /* 0 = monkey head
     1 = bunny
     2 = armadilloman
  */
  switch( currModel )
  {
    case 0:
      myVerts = &(MonkeyVerts[0][0]);
      myNorms = &(MonkeyNormals[0][0]);
      myFaces = &(MonkeyFaces[0][0]);
      myNumVerts = NUM_MONKEY_VERTS;
      myNumFaces = NUM_MONKEY_FACES;
      break;
    case 1:
      myVerts = &(BunnyVerts[0][0]);
      myNorms = &(BunnyNormals[0][0]);
      myFaces = &(BunnyFaces[0][0]);
      myNumVerts = NUM_BUNNY_VERTS;
      myNumFaces = NUM_BUNNY_FACES;
      break;
    case 2:
      myVerts = &(ArmadilloVerts[0][0]);
      myNorms = &(ArmadilloNormals[0][0]);
      myFaces = &(ArmadilloFaces[0][0]);
      myNumVerts = NUM_ARMADILLO_VERTS;
      myNumFaces = NUM_ARMADILLO_FACES;
      break;
    default:
      return;
      break;
  };

}

/* Draws the control triangles of the model.
    Should only be used between glBegin() and glEnd() statements.
*/
void drawControlPatches()
{
  int faceNum;
  for (faceNum = 0; faceNum < myNumFaces; ++faceNum){
    glNormal3fv(&(myNorms[myFaces[faceNum * 3 + 0]*3]));
    glVertex3fv(&(myVerts[myFaces[faceNum * 3 + 0]*3]));

    glNormal3fv(&(myNorms[myFaces[faceNum*3 + 1]*3]));
    glVertex3fv(&(myVerts[myFaces[faceNum*3 + 1]*3]));

    glNormal3fv(&(myNorms[myFaces[faceNum*3 + 2]*3]));
    glVertex3fv(&(myVerts[myFaces[faceNum*3 + 2]*3]));
  }
}

/* Draws the model patches in immediate mode, including the per-vertex
   normals. */
void drawModel()
{
  /* Sets the amount of vertices per patch (3 for triangles) */
  glPatchParameteri(GL_PATCH_VERTICES, 3);

  /* Immediate mode. */

  glBegin(GL_PATCHES);

  drawControlPatches();

  glEnd();
}

/* Returns the length of a vector consisting of (x, y, z) components */
float GetLength( float x, float y, float z )
{
  return sqrt(x*x + y*y + z*z);
}

void updateCGUniforms()
{
  GLfloat mv[16];
  float scale;

  /* Get the width/height of the viewport to pass to the CG shader */
  GLint viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);

  /* Update vertex shader uniforms */
  cgGLSetStateMatrixParameter(myCgModelViewProjection,
    CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);
  checkForCgError("Setting uniform parameter myCgModelViewProjection");
  cgGLSetStateMatrixParameter(myCgModelView, CG_GL_MODELVIEW_MATRIX,
    CG_GL_MATRIX_IDENTITY);
  checkForCgError("Setting uniform parameter myCgModelView");
  cgSetParameter2f(myCgWH, viewport[2]/2.0/lodScalingFactor,
    viewport[3]/2.0/lodScalingFactor);
  checkForCgError("Setting uniform parameter WH");

  /* Update tessellation control uniforms */
  cgSetParameter1i(myCgLodFlag, doLod);
  checkForCgError("Setting uniform parameter myCgLodFlag");
  cgSetParameter3fv(myCgOuterLOD, outer);
  checkForCgError("Setting uniform parameter myCgOuterLOD");
  cgSetParameter3fv(myCgInnerLOD, inner);
  checkForCgError("Setting uniform parameter myCgInnerLOD");

  /* Update tessellation evaluation uniforms */
  cgGLSetStateMatrixParameter(myCgProjectionTE, CG_GL_PROJECTION_MATRIX,
    CG_GL_MATRIX_IDENTITY);
  checkForCgError("Setting uniform parameter myCgProjectionTE");
  cgSetParameter1f(myCgDoPatchOutline, doPatchOutline);
  checkForCgError("Setting uniform parameter myCgDoPatchOutline");
  cgSetParameter1f(myCgCurveParam, myCurveParam);
  checkForCgError("Setting uniform parameter myCgCurveParam");

  /* Update fragment program uniform */
  glGetFloatv(GL_MODELVIEW_MATRIX, mv);
  /* Gets the scaling factor from the matrix.
     All axes are scaled by the same amount.
  */
  scale = GetLength(mv[0], mv[4], mv[8]);

  cgSetParameter1fv(myCgScale, &scale);
  checkForCgError("Setting uniform parameter myCgScale");

  /* Update fragment light position uniform */
  cgSetParameter3fv(myCgLightPos, myLightPos);
  checkForCgError("Setting uniform parameter myCgLightPos");

  /* Update the specular component toggle */
  cgSetParameter1i(myCgDoSpecular, doSpecular);
  checkForCgError("Setting uniform parameter myCgDoSpecular");

  /* Update the programs */
  cgUpdateProgramParameters(myCgVertexProgram);
  checkForCgError("Updating vertex program uniforms via the CG Runtime");
  cgUpdateProgramParameters(myCgTessControlProgram);
  checkForCgError("Updating tessellation control params via the CG Runtime");
  cgUpdateProgramParameters(myCgTessEvalProgram);
  checkForCgError("Updating tessellation eval params via the CG Runtime");
}

/* Vertex shader */
void initVertexCG()
{
  myCgVertexProfile = cgGLGetLatestProfile(CG_GL_VERTEX);
  cgGLSetOptimalOptions(myCgVertexProfile);
  checkForCgError("selecting vertex profile");

  myCgVertexProgram =
    cgCreateProgramFromFile(
      myCgContext,              /* Cg runtime context */
      CG_SOURCE,                /* Program in human-readable form */
      myVertexProgramFileName,  /* Name of file containing program */
      myCgVertexProfile,        /* Profile: OpenGL vertex shader profile */
      myVertexProgramName,      /* Entry function name */
      NULL);                    /* No extra compiler options */

  checkForCgError("creating vertex program from file");
  cgGLLoadProgram(myCgVertexProgram);
  checkForCgError("loading vertex program");

  /* Vertex program uniform parameters */

  /* ModelviewProjection Matrix parameter for transforming verts. */
  myCgModelViewProjection = cgGetNamedParameter(myCgVertexProgram,
    "uModelviewProjectionMatrix");
  checkForCgError("Getting uniform parameter ModelviewProjectionMatrix");
  /* Modelview Matrix parameter for transforming verts. */
  myCgModelView = cgGetNamedParameter(myCgVertexProgram, "uModelviewMatrix");
  checkForCgError("Getting uniform parameter ModelviewMatrix");
  /* width/height For computing screen-space positions. */
  myCgWH = cgGetNamedParameter(myCgVertexProgram, "uWh");
  checkForCgError("Getting uniform parameter wh (width/height parameter)");
}

/* Tessellation control shader */
void initTessControlCG()
{
  myCgTessControlProfile = cgGLGetLatestProfile(CG_GL_TESSELLATION_CONTROL);

  if (myCgTessControlProfile == CG_PROFILE_UNKNOWN){
    printf("gp5 tessellation control profile is not availible\n");
    exit(0);
  }

  cgGLSetOptimalOptions(myCgTessControlProfile);
  checkForCgError("selecting tessellation Control profile");

  myCgTessControlProgram =
  cgCreateProgramFromFile(
      myCgContext,                   /* Cg runtime context */
      CG_SOURCE,                     /* Program in human-readable form */
      myTessControlProgramFileName,  /* Name of file containing program */
      myCgTessControlProfile,        /* Profile: OpenGL GP5 tessellation
                                          control program */
      myTessControlProgramName,      /* Entry function name */
      NULL);                         /* No extra compiler options */

  checkForCgError("creating tessellation control program from file");
  cgGLLoadProgram(myCgTessControlProgram);
  checkForCgError("loading tessellation control program");

  /* Tessellation control program uniform parameters */
  myCgLodFlag = cgGetNamedParameter(myCgTessControlProgram, "uDoLOD");
  checkForCgError("Getting uniform parameter doLod (lod flag)");

  /* Uniform parameters specifying the inner/outer tessellation parameters */
  myCgOuterLOD = cgGetNamedParameter(myCgTessControlProgram, "uOuterLOD");
  checkForCgError("Getting uniform parameter uOuterLOD");
  myCgInnerLOD = cgGetNamedParameter(myCgTessControlProgram, "uInnerLOD");
  checkForCgError("Getting uniform parameter uInnerLOD");
}

/* Tessellation Evaluation shader */
void initTessEvalCG()
{
  myCgTessEvalProfile = cgGLGetLatestProfile(CG_GL_TESSELLATION_EVALUATION);

  if (myCgTessEvalProfile == CG_PROFILE_UNKNOWN){
    printf("gp5 tessellation evaluation profile is not availible\n");
    exit(0);
  }

  cgGLSetOptimalOptions(myCgTessEvalProfile);
  checkForCgError("selecting tessellation evaluation profile");

  myCgTessEvalProgram =
  cgCreateProgramFromFile(
    myCgContext,                /* Cg runtime context */
    CG_SOURCE,                  /* Program in human-readable form */
    myTessEvalProgramFileName,  /* Name of file containing program */
    myCgTessEvalProfile,        /* Profile: OpenGL gp5 tessellation evaluation
                                     program */
    myTessEvalProgramName,      /* Entry function name */
    NULL);                      /* No extra compiler options */
  checkForCgError("creating tessellation evaluation program from file");
  cgGLLoadProgram(myCgTessEvalProgram);
  checkForCgError("loading tessellation evaluation program");

  /* Projection Matrix parameter for transforming verts. */
  myCgProjectionTE = cgGetNamedParameter(myCgTessEvalProgram,
    "uProjectionMatrix");
  checkForCgError("Getting uniform parameter ProjectionMatrix for tessellation"
    " evaluation program");

  myCgDoPatchOutline = cgGetNamedParameter(myCgTessEvalProgram,
    "uDoPatchOutline");
  checkForCgError("Getting uniform parameter uDoPatchOutline for tessellation"
    " evaluation program");

  myCgCurveParam = cgGetNamedParameter(myCgTessEvalProgram,
    "uCurveParam");
  checkForCgError("Getting uniform parameter uCurveParam for tessellation"
    " evaluation program");
}

/* Fragment shader */
void initFragmentCG()
{
  myCgFragmentProfile = cgGLGetLatestProfile(CG_GL_FRAGMENT);
  cgGLSetOptimalOptions(myCgFragmentProfile);
  checkForCgError("selecting fragment profile");

  myCgFragmentProgram =
    cgCreateProgramFromFile(
      myCgContext,                /* Cg runtime context */
      CG_SOURCE,                  /* Program in human-readable form */
      myFragmentProgramFileName,  /* Name of file containing program */
      myCgFragmentProfile,        /* Profile: OpenGL fragment profile */
      myFragmentProgramName,      /* Entry function name */
      NULL);                      /* No extra compiler options */

  checkForCgError("creating fragment program from file");
  cgGLLoadProgram(myCgFragmentProgram);
  checkForCgError("loading fragment program");

  myCgLightPos = cgGetNamedParameter(myCgFragmentProgram, "uLightPos");
  checkForCgError("Getting uniform paraemter uLightPos for light shading");

  myCgDoSpecular = cgGetNamedParameter(myCgFragmentProgram, "uDoSpecular");
  checkForCgError("Getting uniform paraemter uDoSpecular for light shading");

  myCgScale = cgGetNamedParameter(myCgFragmentProgram, "uScale");
  checkForCgError("Getting scaling variable.");
}

void printInstructions(void)
{
  printf("Phong Tessellation Demo\n\n");
  printf("Left mouse   - Rotate model\n");
  printf("Middle mouse - Zoom in/out\n");
  printf("Right mouse  - Menu (shows all other options with keyboard "
          "shortcut)\n\n");
  printf("See ReadMe.txt for a list of instructions\n");
}

int main(int argc, char **argv)
{
  /* Cg version information */
  const char *versionStr = NULL;
  int versionMajor = 0, versionMinor = 0;

  /* Init GLUT */

  glutInitWindowSize(512, 512);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInit(&argc, argv);
  glutCreateWindow(myProgramName);

  myGlutMenu = glutCreateMenu(menuFunc);  /* Create GLUT menu */

  glutAddMenuEntry("[9] Decrease spin speed (can go negative).", (int)'9');
  glutAddMenuEntry("[0] Increase spin speed.", (int)'0');
  glutAddMenuEntry("[o] Toggle outlining patches.", (int)'o');
  glutAddMenuEntry("[2] Increase Phong curve parameter.", (int)'2');
  glutAddMenuEntry("[1] Decrease Phong curve parameter.", (int)'1');
  glutAddMenuEntry("[ ] Animate.", (int)' ');
  glutAddMenuEntry("[w] Toggle wire frame mode.", (int)'w');
  glutAddMenuEntry("[n] Cycle to next model.", (int)'n');
  glutAddMenuEntry("[d] Draw control cage wires.", (int)'d');
  glutAddMenuEntry("[h] Draw hidden control cage wires.", (int)'h');
  glutAddMenuEntry("[s] Toggle the specular component.", (int)'s');
  glutAddMenuEntry("[x] Toggle dynamic level of detail.", (int)'x');
  glutAddMenuEntry("[]] Increase outer tessellation levels.", (int)'+');
  glutAddMenuEntry("[[] Decrease outer tessellation levels.", (int)'_');
  glutAddMenuEntry("[+] Increase inner tessellation levels.", (int)'=');
  glutAddMenuEntry("[-] Decrease inner tessellation levels.", (int)'-');
  glutAddMenuEntry("[;] Decrease triangle scaling factor in LOD mode."
    "(Min = 1)", (int)';');
  glutAddMenuEntry("[\'] Increase triangle scaling factor in LOD mode.",
    (int)'\'');

  glutAddMenuEntry("[esc] Exit application.", 27);

  glutAttachMenu(GLUT_RIGHT_BUTTON);

  glutDisplayFunc(displayfunc);
  glutKeyboardFunc(keyboardfunc);

  /* Init OpenGL */
  if (glewInit()!=GLEW_OK || !GLEW_VERSION_2_0) {
    fprintf(stderr, "%s: failed to initialize GLEW, OpenGL 2.0 required.\n", myProgramName);
    exit(0);
  }

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

  glClearColor(0.8, 0.8, 0.8, 0);  /* Light background to see outline. */
  glEnable(GL_DEPTH_TEST);         /* Hidden surface removal. */
  glDepthFunc(GL_LESS);
  glEnable(GL_CULL_FACE);          /* Back face removal */

  /* Camera*/
  glMatrixMode(GL_MODELVIEW);
  glScalef(0.65f, 0.65f, 0.65f);
  glTranslatef(0.f, 0.f, -5.f);
  zprInit();                       /* Init Zpr class */

  /* Get the maximum tessellation level parameter from OpenGL */
  glGetFloatv(GL_MAX_TESS_GEN_LEVEL, &maxTessLevel);

  zprSpinInit(20.0f, 0.0, 1.0, 0.0f);

  /* Cg initialization */

  /* Initialize the shaders.
     Init the context, the parameter updating mode,
     the individual programs and connecting the CGparameters
     with their uniform counterparts in the shaders. */

  /* Create the CG context */
  myCgContext = cgCreateContext();
  checkForCgError("creating context");

  cgGLSetDebugMode(CG_FALSE);  /* Set the debug mode*/

  /* Initialize each shader program */
  initVertexCG();
  initFragmentCG();
  initTessEvalCG();
  initTessControlCG();

  /* Initialize the model with the first */
  nextModel();

  /* Set parameter setting mode. */
  cgSetParameterSettingMode(myCgContext, CG_DEFERRED_PARAMETER_SETTING);

  printInstructions();

  glutMainLoop();  /* Main loop */

  return 0;
}

/* Binds all of the CG programs in the current state. */
void enableBindCGPrograms()
{
  cgGLBindProgram(myCgVertexProgram);
  checkForCgError("binding vertex program");
  cgGLEnableProfile(myCgVertexProfile);
  checkForCgError("enabling vertex profile");


  cgGLBindProgram(myCgTessControlProgram);
  checkForCgError("binding tessellation control program");
  cgGLEnableProfile(myCgTessControlProfile);
  checkForCgError("enabling tessellation control profile");

  cgGLBindProgram(myCgTessEvalProgram);
  checkForCgError("binding tessellation evluation program");
  cgGLEnableProfile(myCgTessEvalProfile);
  checkForCgError("enabling tessellation evluation profile");


  cgGLBindProgram(myCgFragmentProgram);
  checkForCgError("binding fragment program");
  cgGLEnableProfile(myCgFragmentProfile);
  checkForCgError("enabling fragment profile");
}

/* Disables the CG programs */
void disableCGPrograms()
{
  cgGLDisableProfile(myCgVertexProfile);
  checkForCgError("disabling vertex profile");

  cgGLDisableProfile(myCgTessControlProfile);
  checkForCgError("disabling tessellation control profile");

  cgGLDisableProfile(myCgTessEvalProfile);
  checkForCgError("disabling tessellation evaluation profile");

  cgGLDisableProfile(myCgFragmentProfile);
  checkForCgError("disabling fragment profile");
}

void displayfunc(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();

  zprSpinDoRotate();

  glColor4f(0.7f,0.4f,0.3f,1.0f);

  if (doWire)
    glPolygonMode(GL_FRONT, GL_LINE);
  else
    glPolygonMode(GL_FRONT, GL_FILL);


  updateCGUniforms();

  enableBindCGPrograms();

  drawModel();

  disableCGPrograms();

  /* To draw the control cage using the fixed function pipeline.*/
  if (doDrawControlCage == 1){
    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    if (doDrawHiddenControlCage == 1){
      glColor4f(1.0,0.2,0.2,1.0f);
      glDisable(GL_DEPTH_TEST);
      glEnable(GL_LINE_STIPPLE);
      glLineStipple(1, (GLushort)0xf000);
      glBegin(GL_TRIANGLES);
      drawControlPatches();
      glEnd();
    }

    glColor4f(0.4f,1.0f,0.0f,1.0f);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_LINE_STIPPLE);
    glDepthFunc(GL_LESS);
    glLineWidth(3.0);
    glBegin(GL_TRIANGLES);
    drawControlPatches();
    glEnd();
    glLineWidth(1.0);

    glPopAttrib();
  }

  glPopMatrix();

  glutSwapBuffers();
}

void reshapeFunc(int width, int height)
{
  glViewport(0, 0, width, height);
  glutPostRedisplay();
}

void menuFunc( int val )
{
  keyboardfunc( (unsigned char)val, 0, 0);
}

void keyboardfunc(unsigned char key, int x, int y)
{
  switch( key )
  {
    case ' ':
      if (zprSpinToggle())
        printf("Spinning is toggled\n");
      else
        printf("Spinning is untoggled\n");
      break;

    case '0':
      zprSpinOffsetSpeed(10.0f);
      printf("Increasing rotation speed\n");
      break;

    case '9':
      printf("Decreasing rotation speed\n");
      zprSpinOffsetSpeed(-10.0f);
      break;

    case '2':
      myCurveParam += 0.05;
      if (myCurveParam > 1.0f)
        myCurveParam = 1.0f;
      printf("Curve parameter now %f\n", myCurveParam);
      break;

    case '1':
      myCurveParam -= 0.05;
      if (myCurveParam < 0.0f)
        myCurveParam = 0.0f;
      printf("Curve parameter now %f\n", myCurveParam);
      break;

    case 'w':
      doWire = !doWire;
      if (doWire == 1)
        printf("Wireframe mode ON\n");
      else
        printf("Wireframe mode OFF\n");
      break;

     case 's':
      doSpecular = !doSpecular;
      if (doSpecular == 1)
        printf("Specular component ON\n");
      else
        printf("Specular component OFF\n");
      break;

    case 'x':
      doLod = !doLod;
      if (doLod)
        printf("Dynamic level of detail mode ON\n");
      else
        printf("Dynamic level of detail mode is OFF\n");
      break;

    case 'o':
      doPatchOutline = !doPatchOutline;
      if (doPatchOutline)
        printf("Drawing outlines of patches\n");
      else
        printf("Not drawing outliens of patches\n");
      break;

    case ']':
      outer[0] = outer[1] = outer[2] = outer[0] > maxTessLevel - 1 ?
        maxTessLevel : (outer[0] + 1.0f);
      printf("Outer tessellation levels increased to %f. (Max = %f)\n",
        outer[0], maxTessLevel);
      break;

    case '[':
      outer[0] = outer[1] = outer[2] = outer[0] < minTessLevel+1 ?
        minTessLevel : (outer[0] - 1.0f);
      printf("Outer tessellation levels decreased to %f. (Min = 1.0)\n",
        outer[0]);
      break;

    case '+':
      inner[0] = inner[0] > maxTessLevel - 1 ? maxTessLevel : inner[0] + 1.0f;
      printf("Inner tessellation levels increased to %f. (Max = %f)\n",
        inner[0], maxTessLevel);
      break;

    case '-':
      inner[0] = inner[0] < minTessLevel+1 ? minTessLevel : inner[0] - 1.0f;
      printf("Inner tessellation levels decreased to %f. (Min = 1.0)\n",
        inner[0]);
      break;

    case 'd':
      doDrawControlCage = !doDrawControlCage;
      printf("Toggled drawing of the control cage\n");
      break;

    case 'h':
      doDrawHiddenControlCage = !doDrawHiddenControlCage;
      printf("Toggled drawing of the control hidden wires\n");
      break;

    case '\'':
      lodScalingFactor = lodScalingFactor + 1;
      printf("Increasing desired edge length for dynamic LOD mode to %d\n",
        lodScalingFactor);
      break;

    case ';':
      lodScalingFactor = lodScalingFactor < 2 ? 1 : lodScalingFactor - 1;
      printf("Decreasing desired edge length for dynamic LOD mode to %d\n",
        lodScalingFactor);
      break;

    case 'n':
      nextModel();
      printf("Switching the next model.\n");
      break;

    case 27:  /* Esc key */
      /* Demonstrate proper deallocation of Cg runtime data structures.
         Not strictly necessary if we are simply going to exit. */
      cgDestroyContext(myCgContext);
      exit(0);
      break;

    default:
      break;
  }

  glutPostRedisplay();
}

