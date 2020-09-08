
/* md2render.cpp -- OpenGL code for rendering Quake2 MD2 models */

#if defined(_MSC_VER) // If Microsoft compilers...
// Visual C++ 6.0: identifier was truncated to '255' characters in the debug information
#pragma warning(disable:4786)
#endif

#include <assert.h>
#include <map>
using namespace std;

#include "md2.h"
#include "gli.h"
#include "loadtex.h"
#include "md2render.h"

struct TexCoord {
  GLshort s;
  GLshort t;
};

struct VertexNormal {
  GLfloat x, y, z;
  GLfloat nx, ny, nz;
};

struct VertexData {
  GLushort ndx;
  GLushort newndx;
  TexCoord tc;
};

struct ModelRenderInfo {
  struct {
    GLuint texCoordArray;
    GLuint vertexNormalArray;   
    GLuint elementArray;
  } bufferObject;
  struct {
    GLuint decal;
    GLuint normalMap;
    GLuint heightMap;
  } textureObject;

  int arrayIndicesPerFrame;
  int frameCount;
  int arrayElementsPerObject;
  int refcnt;

  ModelRenderInfo(const Md2Model *model);
  ~ModelRenderInfo();

  void bindArrayElementsForGL();
  void bindTexCoordsForGL(int texunit);
  void bindPositionsAndNormalsForGL(int frameA, int frameB, int normals);
  void bindTexCoordsForGenericAttribs(int texunit);
  void bindPositionsAndNormalsForGenericAttribs(int frameA, int frameB, int normals);
  void drawModel();

  void addDecalImage(gliGenericImage* &image);

  void ref() { refcnt++; }
  void deref() { refcnt--; if (refcnt == 0) { delete this; } }
};

// MD2 files have a separate position/normal index and texture
// coordinate set index per vertex.  This routine re-indexes the
// vertex set so every vertex has a unique index to its 
// position/normal and texture for easy rendering with vertex
// arrays stored in vertex buffer objects.
//
// Once this re-indexing is performed, three buffer objects
// are created: a per-model texture coordinate set buffer object,
// a buffer object with all the position/normal pairs for the
// full sequence of frames, and finally an element arrays for
// all of the model's independent triangles.
ModelRenderInfo::ModelRenderInfo(const Md2Model *model)
{
  typedef pair<int,int> PosTexIndex;
  typedef map<PosTexIndex, VertexData, less<PosTexIndex> > vertexMapType;

  vertexMapType vertexMap;

  const int numFrames = model->header.numFrames;
  const int numTriangles = model->header.numTriangles;

  int i;
  vertexMapType::iterator m;

  refcnt = 1;
  frameCount = numFrames;
  arrayElementsPerObject = 3*numTriangles;

  // Make a map from each unique <vertexIndex,textureIndex> pair.
  for (i=0; i<numTriangles; i++) {
    const Md2Triangle *tri = &model->triangles[i];

    for (int j=0; j<3; j++) {
      PosTexIndex pti(tri->vertexIndices[j], tri->textureIndices[j]);
      VertexData vd;
      vd.ndx = tri->vertexIndices[j];
      vd.tc.s = model->texCoords[tri->textureIndices[j]].s;
      vd.tc.t = model->texCoords[tri->textureIndices[j]].t;
      vd.newndx = 0;  /* Satisfy gcc's desire to see this initialized. */
      vertexMap[pti] = vd;
    }
  }
  // Assign "new" indices to each unique <vertexIndex,textureIndex> pair
  // and count unique arrayIndicesPerFrame.
  arrayIndicesPerFrame = 0;
  for (m = vertexMap.begin(); m != vertexMap.end(); ++m) {
      m->second.newndx = arrayIndicesPerFrame;
      arrayIndicesPerFrame++;
  }

  // Generate unused buffer object names for three buffer objects.
  GLuint bufferObjs[3];
  glGenBuffers(3, bufferObjs);
  bufferObject.texCoordArray = bufferObjs[0];
  bufferObject.vertexNormalArray = bufferObjs[1];
  bufferObject.elementArray = bufferObjs[2];

  GLuint texObjs[3];
  glGenTextures(3, texObjs);
  textureObject.decal = texObjs[0];
  textureObject.normalMap = texObjs[1];
  textureObject.heightMap = texObjs[2];

  // Allocate a single texture coordinate array for model and load into buffer object.
  TexCoord *texArray = new TexCoord[arrayIndicesPerFrame];
  int newndx = 0;
  for (m = vertexMap.begin(); m != vertexMap.end(); ++m) {
    texArray[newndx] = m->second.tc;
    newndx++;
  }
  glBindBuffer(GL_ARRAY_BUFFER, bufferObject.texCoordArray);
  glBufferData(GL_ARRAY_BUFFER, sizeof(TexCoord)*arrayIndicesPerFrame, texArray, GL_STATIC_DRAW);
  delete texArray;

  // Allocate a vertex/normal array for model's frames and load into buffer object.
  VertexNormal *vertexNormalArray = new VertexNormal[arrayIndicesPerFrame*numFrames];
  newndx = 0;
  for (int f = 0; f < model->header.numFrames; f++) {
    Md2Frame *frame = &model->frames[f];

    for (vertexMapType::iterator m = vertexMap.begin(); m != vertexMap.end(); ++m) {
      assert(m->second.newndx == newndx % arrayIndicesPerFrame);
      assert(m->second.newndx < arrayIndicesPerFrame);
      int oldndx = m->second.ndx;
      vertexNormalArray[newndx].x = frame->vertices[oldndx].vertex[0];
      vertexNormalArray[newndx].y = frame->vertices[oldndx].vertex[1];
      vertexNormalArray[newndx].z = frame->vertices[oldndx].vertex[2];
      vertexNormalArray[newndx].nx = frame->vertices[oldndx].normal[0];
      vertexNormalArray[newndx].ny = frame->vertices[oldndx].normal[1];
      vertexNormalArray[newndx].nz = frame->vertices[oldndx].normal[2];
      newndx++;
    }
  }
  glBindBuffer(GL_ARRAY_BUFFER, bufferObject.vertexNormalArray);
  glBufferData(GL_ARRAY_BUFFER, sizeof(VertexNormal)*arrayIndicesPerFrame*numFrames, vertexNormalArray, GL_STATIC_DRAW);
  delete vertexNormalArray;

  // Allocate a element array for model and load into buffer object.
  int ndx = 0;
  GLushort *elementArray = new GLushort[arrayElementsPerObject];
  for (i=0; i<numTriangles; i++) {
    const Md2Triangle *tri = &model->triangles[i];

    // MD2 models have clockwise front-facing triangles so reverse
    // index order to match OpenGL's default counter-clockwise default for glFrontFace
    for (int j=2; j>=0; j--, ndx++) {
      PosTexIndex pti(tri->vertexIndices[j], tri->textureIndices[j]);

      VertexData vd = vertexMap[pti];
      elementArray[ndx] = vd.newndx;
    }
  }
  assert(arrayElementsPerObject == ndx);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObject.elementArray);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort)*arrayElementsPerObject, elementArray, GL_STATIC_DRAW);
  delete elementArray;
}

ModelRenderInfo::~ModelRenderInfo()
{
  GLuint bufferObjs[3];

  bufferObjs[0] = bufferObject.elementArray;
  bufferObjs[1] = bufferObject.texCoordArray;
  bufferObjs[2] = bufferObject.vertexNormalArray;
  glDeleteBuffers(3, bufferObjs);
}

void ModelRenderInfo::bindArrayElementsForGL()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObject.elementArray);
}

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

void ModelRenderInfo::bindTexCoordsForGL(int texunit)
{
  glClientActiveTexture(GL_TEXTURE0_ARB + texunit);
  glBindBuffer(GL_ARRAY_BUFFER, bufferObject.texCoordArray);
  glTexCoordPointer(2, GL_SHORT, sizeof(GLshort)*2, BUFFER_OFFSET(0));
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

void ModelRenderInfo::bindPositionsAndNormalsForGL(int frameA, int frameB, int normals)
{
  // Bind to array buffer with per-frame position/normal arrays.
  glBindBuffer(GL_ARRAY_BUFFER, bufferObject.vertexNormalArray);

  // Frame A positions.
  glVertexPointer(3, GL_FLOAT, 6*sizeof(GLfloat), BUFFER_OFFSET(frameA*arrayIndicesPerFrame*6*sizeof(GLfloat)));
  glEnableClientState(GL_VERTEX_ARRAY);
  // Frame B positions.
  glClientActiveTexture(GL_TEXTURE1);
  glTexCoordPointer(3, GL_FLOAT, 6*sizeof(GLfloat), BUFFER_OFFSET(frameB*arrayIndicesPerFrame*6*sizeof(GLfloat)));
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  if (normals) {
    // Frame A normals.
    glNormalPointer(GL_FLOAT, 6*sizeof(GLfloat), BUFFER_OFFSET(3*sizeof(GLfloat) + frameA*arrayIndicesPerFrame*6*sizeof(GLfloat)));
    glEnableClientState(GL_NORMAL_ARRAY);
    // Frame B normals.
    glClientActiveTexture(GL_TEXTURE2);
    glTexCoordPointer(3, GL_FLOAT, 6*sizeof(GLfloat), BUFFER_OFFSET(3*sizeof(GLfloat) + frameB*arrayIndicesPerFrame*6*sizeof(GLfloat)));
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  }
}

#if 0
static PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = NULL;
static PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = NULL;

/* Cross-platform OpenGL extension proc handling. */
#ifdef _WIN32
#  include <windows.h>
#  define GET_PROC_ADDRESS(p)   wglGetProcAddress(p) 
#elif defined(__APPLE__)
extern void *OSXGetProcAddress(const char *name);
#  define GET_PROC_ADDRESS(p)   OSXGetProcAddress("_" p)
#elif defined(__ADM__)
#  include <GL/adm.h>
#  define GET_PROC_ADDRESS(p)   admGetProcAddress( (const GLubyte *) p)
#else
#  include <string.h>
#  include <GL/glx.h>
#  define GET_PROC_ADDRESS(p)   glXGetProcAddressARB( (const GLubyte *) p) 
#endif

#define LOAD(t,n) \
  if (0 == n) { \
    n = (t) GET_PROC_ADDRESS(#n); \
    if (0 == n) { \
      n = (t) GET_PROC_ADDRESS(#n ## "ARB"); \
      if (0 == n) { \
        fprintf(stderr, "%s: could not GetProcAddress for %s from OpenGL (or ARB version)\n", programName, #n); \
        problems++; \
      } \
    } \
  }

static void loadGenericAttribProcs(void)
{
  static int loaded = 0;
  int problems = 0;

  if (!loaded) {
    LOAD(PFNGLVERTEXATTRIBPOINTERPROC, glVertexAttribPointer);
    LOAD(PFNGLENABLEVERTEXATTRIBARRAYPROC, glEnableVertexAttribArray);
    LOAD(PFNGLDISABLEVERTEXATTRIBARRAYPROC, glDisableVertexAttribArray);
    if (problems) {
      exit(1);
    }
    loaded = 0;
  }
}
#endif

void ModelRenderInfo::bindTexCoordsForGenericAttribs(int texunit)
{
  glClientActiveTexture(GL_TEXTURE0_ARB + texunit);
  glBindBuffer(GL_ARRAY_BUFFER, bufferObject.texCoordArray);
  glVertexAttribPointer(/*attrib*/4, 2, GL_SHORT,
    /*normalize*/GL_FALSE, /*stride*/sizeof(GLshort)*2,
    BUFFER_OFFSET(0));
  glEnableVertexAttribArray(4);
}

void ModelRenderInfo::bindPositionsAndNormalsForGenericAttribs(int frameA, int frameB, int normals)
{
  // Bind to array buffer with per-frame position/normal arrays.
  glBindBuffer(GL_ARRAY_BUFFER, bufferObject.vertexNormalArray);

  // Frame A positions.
  glVertexAttribPointer(/*attr*/0, 3, GL_FLOAT,
    /*normalize*/GL_FALSE, /*stride*/6*sizeof(GLfloat),
    BUFFER_OFFSET(frameA*arrayIndicesPerFrame*6*sizeof(GLfloat)));
  glEnableVertexAttribArray(/*attr*/0);
  // Frame B positions.
  glVertexAttribPointer(/*attr*/1, 3, GL_FLOAT,
    /*normalize*/GL_FALSE, /*stride*/6*sizeof(GLfloat),
    BUFFER_OFFSET(frameB*arrayIndicesPerFrame*6*sizeof(GLfloat)));
  glEnableVertexAttribArray(/*attr*/1);

  if (normals) {
    // Frame A normals.
    glVertexAttribPointer(/*attr*/2, 3, GL_FLOAT,
      /*normalize*/GL_FALSE, /*stride*/6*sizeof(GLfloat),
      BUFFER_OFFSET(3*sizeof(GLfloat) + frameA*arrayIndicesPerFrame*6*sizeof(GLfloat)));
    glEnableVertexAttribArray(/*attr*/2);
    // Frame B normals.
    glVertexAttribPointer(/*attr*/3, 3, GL_FLOAT,
      /*normalize*/GL_FALSE, /*stride*/6*sizeof(GLfloat),
      BUFFER_OFFSET(3*sizeof(GLfloat) + frameB*arrayIndicesPerFrame*6*sizeof(GLfloat)));
    glEnableVertexAttribArray(/*attr*/3);
  }
}

void ModelRenderInfo::drawModel()
{
  glDrawElements(GL_TRIANGLES, arrayElementsPerObject, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));
}

void ModelRenderInfo::addDecalImage(gliGenericImage* &image)
{
  const int makeMipmaps = 1;

  glBindTexture(GL_TEXTURE_2D, textureObject.decal);
  image = loadTextureDecal(image, makeMipmaps);
  gliFree(image);
  image = NULL;
}

extern "C" {

MD2render *createMD2render(Md2Model *model)
{
  ModelRenderInfo *mri = new ModelRenderInfo(model);

  return (MD2render*) mri;
}

void drawMD2render(MD2render *m, int frameA, int frameB)
{
  ModelRenderInfo *mri = reinterpret_cast<ModelRenderInfo *>(m);

  mri->bindArrayElementsForGL();
  mri->bindTexCoordsForGL(0);
  mri->bindPositionsAndNormalsForGL(frameA, frameB, 1);
  mri->drawModel();
}

void drawMD2render_withGenericAttribs(MD2render *m, int frameA, int frameB)
{
  ModelRenderInfo *mri = reinterpret_cast<ModelRenderInfo *>(m);

  mri->bindArrayElementsForGL();
  mri->bindTexCoordsForGenericAttribs(0);
  mri->bindPositionsAndNormalsForGenericAttribs(frameA, frameB, 1);
  mri->drawModel();
}

}
