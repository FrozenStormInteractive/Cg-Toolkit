/* Implements Bezier Patch Example
 * Evaluates a model composed of bezier and triangle patches using tessellation
 * shaders.
 *
 * Please see ReadMe.txt for information on how to use this program.
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

#include "gumbo.h"

/* Model manipulation */
#include "zpr.h"

/* Application specific state flags */

/* Maximum tessellation level allowed -- Will be set in initialization to
 * the OpenGL implementation-specific value.
 */
static GLfloat maxTessLevel;

/* Minimum tessellation level allowed */
static GLfloat minTessLevel = 1.0f;

/* Display the outlines of the patches */
static int doDisplayPatches = 0;

/* Wireframe mode (wireframe of tessellated triangles */
static int doWire = 0;

/* Do level of detail determined by screenspace triangle size,
or determined by texcoord set (fixed) values. */
static int doLod = 0;

/* Whether to draw the control cage wires */
static int doDrawControlCage = 0;

/* Whether or not to draw the control cage wires which are behind the model */
static int doDrawHiddenControlCage = 1;

/* Whether or not to do Bezier algorithm */
static int doBezier = 1;

/* OpenGL Globals */

/* Menu for glut */
static unsigned int myGlutMenu;

/* Light position */
static float myLightPos [3] = {1.5f, 2.0f, 6.0f};

/* Affects the size of the tessellated triangles in LOD dynamic mode. */
static int lodScalingFactor = 10;

/* Defaults for outer/inner tessellation parameters */
float outer[4] = {16.0,16.0,16.0, 16.0};
float inner[2] = {16.0, 16.0};

/* Cg Globals */
static CGcontext   myCgContext;               /* CG Context */

static CGprofile   myCgVertexProfile,         /* CG Profile */
                   myCgTessControlProfile,
                   myCgTessEvalProfile,
                   myCgFragmentProfile;

static CGprogram   myCgVertexProgram,
                   myCgTessQuadControlProgram,
                   myCgTessQuadEvalProgram,
                   myCgTessTriControlProgram,
                   myCgTessTriEvalProgram,
                   myCgFragmentProgram;


/* CG uniform parameters */
static CGparameter myCgModelViewProjection,   /* CG program */
                   myCgModelView,
                   myCgProjectionQuadTE,
                   myCgProjectionTriTE,
                   myCgWH,
                   myCgLodFlagQuad,
                   myCgLodFlagTri,
                   myCgDisplayPatchesQuad,
                   myCgDisplayPatchesTri,
                   myCgLightPos,
                   myCgDoBezierTri,
                   myCgDoBezierQuad,
                   myCgScale;

/* Entry points and filenames. */
static const char *myProgramName = "Bezier Patches",
                  *myCGFileName = "quad_tri_bezier.cg",
                  *myVertexProgramName = "mainV",
                  *myTessQuadControlProgramName = "mainQuadTC",
                  *myTessQuadEvalControlProgramName = "mainQuadTE",
                  *myTessTriControlProgramName = "mainTriTC",
                  *myTessTriEvalProgramName = "mainTriTE",
                  *myFragmentProgramName = "mainF";

/* Forward declared callbacks for glut. */
void displayfunc(void);
void menufunc(int val);
void keyboardfunc(unsigned char key, int x, int y);

/* Checks for CG errors and if a shader compile error, will return
 * the compiler string
 */
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

void printInstructions(void)
{
  printf("Bezier Patches Example\n\n");
  printf("Left mouse   - Rotate model\n");
  printf("Middle mouse - Zoom in/out\n");
  printf("Right mouse  - Menu (shows all other options with keyboard "
          "shortcut)\n\n");
  printf("See ReadMe.txt for a list of instructions\n");
}

/* Draw a single triangle patch */
void DrawTriPatch( unsigned int faceNum )
{
  int i;
  for (i = 0; i < 10; ++i)
    glVertex3fv(gumboVerts[gumboTriPatches[faceNum][i]]);
}

/* Draw a single quad patch */
void DrawQuadPatch( unsigned int faceNum )
{
  int i;
  for (i = 0; i < 16; ++i)
    glVertex3fv(gumboVerts[gumboQuadPatches[faceNum][i]]);
}

/* Binds the triangle tessellation control and evaluation shaders */
void bindTriangleCGPrograms(void)
{
  cgGLBindProgram(myCgTessTriControlProgram);
  checkForCgError("binding triangle tessellation control program");
  cgGLBindProgram(myCgTessTriEvalProgram);
  checkForCgError("binding triangle tessellation evaluation program");
}

/* Binds the quad tessellation control and evaluation shaders */
void bindQuadCGPrograms(void)
{
  cgGLBindProgram(myCgTessQuadControlProgram);
  checkForCgError("binding quad tessellation control program");
  cgGLBindProgram(myCgTessQuadEvalProgram);
  checkForCgError("binding quad tessellation evaluation program");
}

/* Returns the length of a vector consisting of (x, y, z) components */
float GetLength( float x, float y, float z )
{
  return sqrt(x*x + y*y + z*z);
}

void updateCGUniforms(void)
{
  GLfloat mv[16];
  float scale; /* Used to prevent specular fall-off when zooming in/out */

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

  /* Update tessellation control uniform */
  cgSetParameter1i(myCgLodFlagQuad, doLod);
  checkForCgError("Setting uniform parameter myCgLodFlagQuad");
  cgSetParameter1i(myCgLodFlagTri, doLod);
  checkForCgError("Setting uniform parameter myCgLodFlagTri");

  /* Update the CG parameter for drawing Bezier triangle patches */
  cgSetParameter1i(myCgDoBezierTri, doBezier);
  checkForCgError("Setting uniform parameter myCgDoBezierTri");

  /* Update the CG parameter for drawing bezier quad patches */
  cgSetParameter1i(myCgDoBezierQuad, doBezier);
  checkForCgError("Setting uniform parameter myCgDoBezierQuad");

  /* Update tessellation evaluation uniform */
  cgGLSetStateMatrixParameter(myCgProjectionQuadTE, CG_GL_PROJECTION_MATRIX,
    CG_GL_MATRIX_IDENTITY);
  checkForCgError("Setting uniform parameter myCgProjectionQuadTE");
  cgGLSetStateMatrixParameter(myCgProjectionTriTE, CG_GL_PROJECTION_MATRIX,
    CG_GL_MATRIX_IDENTITY);
  checkForCgError("Setting uniform parameter myCgProjectionTriTE");

  cgSetParameter1i(myCgDisplayPatchesQuad, doDisplayPatches);
  checkForCgError("Setting uniform parameter myCgDisplayPatchesQuad");
  cgSetParameter1i(myCgDisplayPatchesTri, doDisplayPatches);
  checkForCgError("Setting uniform parameter myCgDisplayPatchesTri");

  /* Update fragment program uniform */
  glGetFloatv(GL_MODELVIEW_MATRIX, mv);
  /* Gets the scaling factor from the matrix.
     All axes are scaled by the same amount.
  */
  scale = GetLength(mv[0], mv[4], mv[8]);

  cgSetParameter1fv(myCgScale, &scale);
  checkForCgError("Setting uniform parameter myCgScale");

  cgSetParameter3fv(myCgLightPos, myLightPos);
  checkForCgError("Setting uniform parameter myCgLightPos");

  /* Update the program */
  cgUpdateProgramParameters(myCgVertexProgram);
  checkForCgError("Updating vertex program uniforms via the CG Runtime");
  cgUpdateProgramParameters(myCgTessQuadControlProgram);
  checkForCgError("Updating tessellation control params via the CG Runtime");
  cgUpdateProgramParameters(myCgTessQuadEvalProgram);
  checkForCgError("Updating tessellation eval params via the CG Runtime");
  cgUpdateProgramParameters(myCgTessTriControlProgram);
  checkForCgError("Updating tess control triangle params via the CG Runtime");
  cgUpdateProgramParameters(myCgTessTriEvalProgram);
  checkForCgError("Updating tess eval triangle params via the CG Runtime");
}

/* Vertex shader */
void initVertexCG(void)
{
  myCgVertexProfile = cgGLGetLatestProfile(CG_GL_VERTEX);
  cgGLSetOptimalOptions(myCgVertexProfile);
  checkForCgError("selecting vertex profile");

  myCgVertexProgram =
    cgCreateProgramFromFile(
      myCgContext,              /* Cg runtime context */
      CG_SOURCE,                /* Program in human-readable form */
      myCGFileName,             /* Name of file containing program */
      myCgVertexProfile,        /* Profile: OpenGL vertex program */
      myVertexProgramName,      /* Entry function name */
      NULL);                    /* No extra compiler options */

  checkForCgError("creating vertex program from file");
  cgGLLoadProgram(myCgVertexProgram);
  checkForCgError("loading vertex program");

  /* Vertex program uniform parameters */

  /* ModelviewProjection Matrix parameter for transforming verts. */
  myCgModelViewProjection = cgGetNamedParameter(myCgVertexProgram,
    "ModelviewProjectionMatrix");
  checkForCgError("Getting uniform parameter ModelviewProjectionMatrix");
  /* Modelview Matrix parameter for transforming verts. */
  myCgModelView = cgGetNamedParameter(myCgVertexProgram, "ModelviewMatrix");
  checkForCgError("Getting uniform parameter ModelviewMatrix");
  /* width/height For computing screen-space positions. */
  myCgWH = cgGetNamedParameter(myCgVertexProgram, "wh");
  checkForCgError("Getting uniform parameter wh (width/height parameter)");
}

/* Tessellation control shader */
void initTessControlCG(void)
{
  /*** Quad patches ***/

  myCgTessControlProfile = cgGLGetLatestProfile(CG_GL_TESSELLATION_CONTROL);


  if (myCgTessControlProfile == CG_PROFILE_UNKNOWN){
    printf("gp5 tessellation control profile is not availible\n");
    exit(0);
  }

  cgGLSetOptimalOptions(myCgTessControlProfile);
  checkForCgError("selecting tessellation Controluation profile");

  myCgTessQuadControlProgram =
  cgCreateProgramFromFile(
      myCgContext,                    /* Cg runtime context */
      CG_SOURCE,                      /* Program in human-readable form */
      myCGFileName,                   /* Name of file containing program */
      myCgTessControlProfile,         /* Profile: OpenGL GP5 Tessellation
                                           control program */
      myTessQuadControlProgramName,   /* Entry function name */
      NULL);                          /* No extra compiler options */
  checkForCgError("creating tessellation control program from file");
  cgGLLoadProgram(myCgTessQuadControlProgram);
  checkForCgError("loading tessellation control program");

  /* Tessellation control program uniform parameters */
  myCgLodFlagQuad = cgGetNamedParameter(myCgTessQuadControlProgram, "doLod");
  checkForCgError("Getting uniform parameter doLod (lod flag)");

 /*** Triangle Patches ***/

  myCgTessTriControlProgram =
  cgCreateProgramFromFile(
      myCgContext,                   /* Cg runtime context */
      CG_SOURCE,                     /* Program in human-readable form */
      myCGFileName,                  /* Name of file containing program */
      myCgTessControlProfile,        /* Profile: OpenGL GP5 Tessellation
                                          control program */
      myTessTriControlProgramName,   /* Entry function name */
      NULL);                         /* No extra compiler options */
  checkForCgError("creating tessellation control triangle program from file");
  cgGLLoadProgram(myCgTessTriControlProgram);
  checkForCgError("loading tessellation control triangle program");

  /* Tessellation control program uniform parameters */
  myCgLodFlagTri = cgGetNamedParameter(myCgTessTriControlProgram, "doLod");
  checkForCgError("Getting uniform parameter doLod (lod flag)");
}

/* Tessellation Evaluation shader */
void initTessEvalCG(void)
{
  myCgTessEvalProfile = cgGLGetLatestProfile(CG_GL_TESSELLATION_EVALUATION);

  if (myCgTessEvalProfile == CG_PROFILE_UNKNOWN){
    printf("gp5 tessellation evaluation profile is not availible\n");
    exit(0);
  }

  cgGLSetOptimalOptions(myCgTessEvalProfile);
  checkForCgError("selecting tessellation evaluation profile");

  /* Quad Patches */
  myCgTessQuadEvalProgram =
  cgCreateProgramFromFile(
    myCgContext,                      /* Cg runtime context */
    CG_SOURCE,                        /* Program in human-readable form */
    myCGFileName,                     /* Name of file containing program */
    myCgTessEvalProfile,              /* Profile: OpenGL gp5 Tessellation
                                           evaluation program */
    myTessQuadEvalControlProgramName, /* Entry function name */
    NULL);                            /* No extra compiler options */
  checkForCgError("creating tessellation evaluation program from file");
  cgGLLoadProgram(myCgTessQuadEvalProgram);
  checkForCgError("loading tessellation evaluation program");

  /* Projection Matrix parameter for transforming verts. */
  myCgProjectionQuadTE = cgGetNamedParameter(myCgTessQuadEvalProgram,
    "ProjectionMatrix");
  checkForCgError("Getting uniform parameter ProjectionMatrix for quad "
    "tessellation evaluation program");

  myCgDisplayPatchesQuad = cgGetNamedParameter(myCgTessQuadEvalProgram,
    "uDisplayPatches");
  checkForCgError("Getting uniform parameter uDisplayPatches for quad "
    "tessellation evaluation program");

  /* Whether or not to do patches or Draw the coarse control mesh */
  myCgDoBezierQuad = cgGetNamedParameter(myCgTessQuadEvalProgram, "uDoBezier");
  checkForCgError("Getting uniform parameter uDoBezier in quad program");


  /* Tri Patches */
  myCgTessTriEvalProgram =
  cgCreateProgramFromFile(
    myCgContext,                    /* Cg runtime context */
    CG_SOURCE,                      /* Program in human-readable form */
    myCGFileName,                   /* Name of file containing program */
    myCgTessEvalProfile,            /* Profile: OpenGL gp5 Tessellation
                                         evaluation program */
    myTessTriEvalProgramName,       /* Entry function name */
    NULL);                          /* No extra compiler options */
  checkForCgError("creating tessellation evaluation triangle program from "
    "file");
  cgGLLoadProgram(myCgTessTriEvalProgram);
  checkForCgError("loading tessellation evaluation triangle program");

  /* Whether or not to do triangle patches or Draw the coarse control mesh */
  myCgDoBezierTri = cgGetNamedParameter(myCgTessTriEvalProgram, "uDoBezier");
  checkForCgError("Getting uniform parameter uDoBezier in tri program");

  /*Projection Matrix parameter for transforming verts. */
  myCgProjectionTriTE = cgGetNamedParameter(myCgTessTriEvalProgram,
    "ProjectionMatrix");
  checkForCgError("Getting uniform parameter ProjectionMatrix for quad "
    "tessellation evaluation program");

  myCgDisplayPatchesTri = cgGetNamedParameter(myCgTessTriEvalProgram,
    "uDisplayPatches");
  checkForCgError("Getting uniform parameter uDisplayPatches for tri "
    "tessellation evaluation program");
}

/* Fragment shader */
void initFragmentCG(void)
{
  myCgFragmentProfile = cgGLGetLatestProfile(CG_GL_FRAGMENT);
  cgGLSetOptimalOptions(myCgFragmentProfile);
  checkForCgError("selecting fragment profile");

  myCgFragmentProgram =
    cgCreateProgramFromFile(
      myCgContext,                /* Cg runtime context */
      CG_SOURCE,                  /* Program in human-readable form */
      myCGFileName,               /* Name of file containing program */
      myCgFragmentProfile,        /* Profile: OpenGL fragment program */
      myFragmentProgramName,      /* Entry function name */
      NULL);                      /* No extra compiler options */
  checkForCgError("creating fragment program from file");
  cgGLLoadProgram(myCgFragmentProgram);
  checkForCgError("loading fragment program");

  myCgLightPos = cgGetNamedParameter(myCgFragmentProgram, "uLightPos");
  checkForCgError("Getting lighting position variable");

  myCgScale = cgGetNamedParameter(myCgFragmentProgram, "uScale");
  checkForCgError("Getting scaling variable.");
}

int main(int argc, char **argv)
{

  /* Cg version information */
  const char *versionStr = NULL;
  int versionMajor = 0, versionMinor = 0;

  /* Init GLUT */

  glutInitWindowSize(500, 500);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInit(&argc, argv);
  glutCreateWindow(myProgramName);

  /* Create GLUT menu */
  myGlutMenu = glutCreateMenu(menufunc);

  glutAddMenuEntry("[t] Toggle between patches and coarse mesh.", (int)'t');
  glutAddMenuEntry("[ ] Toggle animation.", (int)' ');
  glutAddMenuEntry("[r] Resets the spinner.", (int)'r');
  glutAddMenuEntry("[9] Decrease speed (can go negative).", (int)'9');
  glutAddMenuEntry("[0] Increase speed.", (int)'0');
  glutAddMenuEntry("[o] Toggle outlining Bezier patches. "
                    "(Triangle patches drawn purple)", (int)'o');
  glutAddMenuEntry("[w] Toggle wire frame mode.", (int)'w');
  glutAddMenuEntry("[d] Draw control cage wires.", (int)'d');
  glutAddMenuEntry("[h] Draw hidden control cage wires.", (int)'h');
  glutAddMenuEntry("[x] Toggle dynamic level of detail.", (int)'x');
  glutAddMenuEntry("[]] Increase outer tessellation levels (static LOD only).", (int)']');
  glutAddMenuEntry("[[] Decrease outer tessellation levels (static LOD only).", (int)'[');
  glutAddMenuEntry("[+] Increase inner tessellation levels (static LOD only).", (int)'+');
  glutAddMenuEntry("[-] Decrease inner tessellation levels (static LOD only).", (int)'-');
  glutAddMenuEntry("[;] Decrease scaling factor (dynamic LOD only) "
                    "(Min = 1)", (int)';');
  glutAddMenuEntry("['] Increase scaling factor (dynamic LOD only) ",
                     (int)'\'');

  glutAddMenuEntry("[esc] Exit application.", 27);

  glutAttachMenu(GLUT_RIGHT_BUTTON);

  glutDisplayFunc(displayfunc);
  glutKeyboardFunc(keyboardfunc);

  /* Init OpenGL */
  if (glewInit()!=GLEW_OK || !GLEW_VERSION_2_0) {
    fprintf(stderr, "%s: failed to initialize GLEW, OpenGL 2.0 required.\n",
      myProgramName);
    exit(0);
  }

  /* Make sure gpu5 is availible */
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

  glClearColor(0.8, 0.8, 0.8, 0);  /* Gray background. */
  glEnable(GL_DEPTH_TEST);         /* Hidden surface removal. */
  glDepthFunc(GL_LESS);

  /* Camera*/
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

  /* Get the maximum tessellation level parameter from OpenGL */
  glGetFloatv(GL_MAX_TESS_GEN_LEVEL, &maxTessLevel);

  zprInit(); /* Init Zpr class */

  zprSpinInit(20.0f, 0.0f, 0.0f, 1.0f);

  /* Cg initialization */

  /* Initialize the shaders.
     Init the context, the parameter updating mode,
     the individual programs and connecting the CGparameters
     with their uniform counterparts in the shaders.
  */

  /* Create the CG context */
  myCgContext = cgCreateContext();
  checkForCgError("creating context");

  /* Set the debug mode*/
  cgGLSetDebugMode(CG_FALSE);

  /* Initialize each shader program */
  initVertexCG();
  initFragmentCG();
  initTessEvalCG();
  initTessControlCG();

  /* Set parameter setting mode.
  Deferred means internal uniform updates are deferred until the program is
    bound again.*/
  cgSetParameterSettingMode(myCgContext, CG_DEFERRED_PARAMETER_SETTING);

  printInstructions();

  /* Main loop */
  glutMainLoop();

  return 0;
}

/* Binds all of the CG programs in the current state. */
void enableBindCGPrograms(void)
{
  cgGLBindProgram(myCgVertexProgram);
  checkForCgError("binding vertex program");
  cgGLEnableProfile(myCgVertexProfile);
  checkForCgError("enabling vertex profile");


  bindQuadCGPrograms(); /* Start with quad */
  cgGLEnableProfile(myCgTessControlProfile);
  checkForCgError("enabling tessellation control profile");
  cgGLEnableProfile(myCgTessEvalProfile);
  checkForCgError("enabling tessellation evaluation profile");

  cgGLBindProgram(myCgFragmentProgram);
  checkForCgError("binding fragment program");
  cgGLEnableProfile(myCgFragmentProfile);
  checkForCgError("enabling fragment profile");
}

/* Disables the CG programs */
void disableCGPrograms(void)
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

/* Draws the model patches */
void drawGumbo(void)
{
  int faceNum;

  /* Immediate mode. */
  glMultiTexCoord4fv(GL_TEXTURE0, outer);
  glMultiTexCoord2fv(GL_TEXTURE1, inner);

  bindQuadCGPrograms();
  /* Draw Bezier Quadrangles */
  glPatchParameteri(GL_PATCH_VERTICES, 16);

  glBegin(GL_PATCHES);
  for (faceNum = 0; faceNum < NUM_GUMBO_QUAD_PATCHES; ++faceNum)
    DrawQuadPatch(faceNum);
  glEnd();

  /* Draw Bezier Triangles */
  bindTriangleCGPrograms();
  glPatchParameteri(GL_PATCH_VERTICES, 10);

  glBegin(GL_PATCHES);
  for (faceNum = 0; faceNum < NUM_GUMBO_TRI_PATCHES; ++faceNum)
    DrawTriPatch(faceNum);
  glEnd();

}

void drawControlPatches(void)
{
  unsigned int facenum;

  glBegin(GL_QUADS);
  for (facenum = 0; facenum < NUM_GUMBO_QUAD_PATCHES; facenum++)
  {
    glVertex3fv(gumboVerts[gumboQuadPatches[facenum][0]]);
    glVertex3fv(gumboVerts[gumboQuadPatches[facenum][3]]);
    glVertex3fv(gumboVerts[gumboQuadPatches[facenum][15]]);
    glVertex3fv(gumboVerts[gumboQuadPatches[facenum][12]]);

    glVertex3fv(gumboVerts[gumboQuadPatches[facenum][5]]);
    glVertex3fv(gumboVerts[gumboQuadPatches[facenum][6]]);
    glVertex3fv(gumboVerts[gumboQuadPatches[facenum][10]]);
    glVertex3fv(gumboVerts[gumboQuadPatches[facenum][9]]);
  }
  glEnd();
  glBegin(GL_TRIANGLES);
  for (facenum = 0; facenum < NUM_GUMBO_TRI_PATCHES; facenum++)
  {
    glVertex3fv(gumboVerts[gumboQuadPatches[facenum][0]]);
    glVertex3fv(gumboVerts[gumboQuadPatches[facenum][3]]);
    glVertex3fv(gumboVerts[gumboQuadPatches[facenum][9]]);
  }
  glEnd();

  glBegin(GL_LINES);
  for (facenum = 0; facenum < NUM_GUMBO_QUAD_PATCHES; facenum++)
  {
    glVertex3fv(gumboVerts[gumboQuadPatches[facenum][0]]);
    glVertex3fv(gumboVerts[gumboQuadPatches[facenum][5]]);

    glVertex3fv(gumboVerts[gumboQuadPatches[facenum][3]]);
    glVertex3fv(gumboVerts[gumboQuadPatches[facenum][6]]);

    glVertex3fv(gumboVerts[gumboQuadPatches[facenum][15]]);
    glVertex3fv(gumboVerts[gumboQuadPatches[facenum][10]]);

    glVertex3fv(gumboVerts[gumboQuadPatches[facenum][12]]);
    glVertex3fv(gumboVerts[gumboQuadPatches[facenum][9]]);
  }
  glEnd();
}

void displayfunc(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glEnable(GL_LIGHTING);

  glMatrixMode( GL_MODELVIEW );

  glPushMatrix();

  zprSpinDoRotate(); /* Updates the rotation of the spinner if active */

  /*Update light position */
  glLightfv(GL_LIGHT0, GL_POSITION, myLightPos);

  updateCGUniforms();

  enableBindCGPrograms();

  glColor4f(0.7f,0.4f,0.3f,1.0f);

  if (doWire)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  else
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glLineWidth(1.0f);

  drawGumbo();

  disableCGPrograms();

  /* To draw the control cage using the fixed function pipeline.*/
  if (doDrawControlCage == 1)
  {
    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    if (doDrawHiddenControlCage == 1)
    {
      glColor3f(1.0,0.2,0.2);
      glDisable(GL_DEPTH_TEST);
      glEnable(GL_LINE_STIPPLE);
      glLineStipple(1, (short)0xf000);
      glLineWidth(1);
      drawControlPatches();
    }

    glLineWidth(3.0);
    glColor3f(0.4,1.0,0.0);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_LINE_STIPPLE);
    glDepthFunc(GL_LESS);
    drawControlPatches();

    glPopAttrib();
  }

  glPopMatrix();
  glutSwapBuffers();
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
  switch (key )
  {
    case '0':
      zprSpinOffsetSpeed(10.0f);
      printf("Increasing rotation speed\n");
      break;

    case '9':
      printf("Decreasing rotation speed\n");
      zprSpinOffsetSpeed(-10.0f);
      break;

    case 'w':
      doWire = !doWire;
        if (doWire == 1)
          printf("Wireframe mode ON\n");
        else
          printf("Wireframe mode OFF\n");
      break;

    case ' ':
      if ( zprSpinToggle() )
        printf("Rotation toggled on\n");
      else
        printf("Rotation toggled off\n");
      break;

    case 'r':
      zprSpinInit(20.0f, 0.0f, 0.0f, 1.0f);
      break;

    case 'x':
      doLod = !doLod;
      if (doLod)
        printf("Dynamic level of detail mode ON\n");
      else
        printf("Dynamic level of detail mode is OFF\n");
      break;

    case 't':
      doBezier = !doBezier;
      printf("Toggling the drawing of the control mesh and the Bezier mesh\n");
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

    case 'o':
      doDisplayPatches = !doDisplayPatches;
      printf("Toggled drawing outline the patches. (Triangles in blue)\n");
      break;

    case 'd':
      doDrawControlCage = !doDrawControlCage;
      printf("Toggled drawing control cage. (Triangles in blue)\n");
      break;

    case 'h':
      doDrawHiddenControlCage = !doDrawHiddenControlCage;
      printf("Toggled drawing of the control hidden wires\n");
      break;

    case '\'':
      lodScalingFactor = lodScalingFactor + 1;
      printf("Increasing desired pixels per triangle edge to %d\n",
      lodScalingFactor);
      break;

    case ';':
      lodScalingFactor = lodScalingFactor < 2 ? 1 : lodScalingFactor - 1;
      printf("Decreasing desired pixels per triangle edge to %d\n",
      lodScalingFactor);
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

