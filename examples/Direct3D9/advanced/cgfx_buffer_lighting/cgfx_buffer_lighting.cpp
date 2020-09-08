
/* cgfx_bumpdemo.c - a Direct3D9-based Cg 3.1 demo */

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <windows.h>
#include <vector>
using namespace std;

#include <d3d9.h>      /* Direct3D9 API: Can't include this?  Is DirectX SDK installed? */
#include "DXUT.h"      /* DirectX Utility Toolkit (part of the DirectX SDK) */
#include "matrix.h"
#include "materials.h"

#include <Cg/cg.h>     /* Cg Core API: Can't include this?  Is Cg Toolkit installed! */
#include <Cg/cgD3D9.h> /* Cg Direct3D9 API (part of Cg Toolkit) */

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "miniDXUT.lib")


static const char *myProgramName = "cgfx_buffer_lighting"; /* Program name for messages. */
const char * myCgFXFileName = "buffer_lighting.cgfx";
float myProjectionMatrix[16];

/* Cg global variables */
CGcontext    myCgContext;
CGeffect     myCgEffect;
CGtechnique  myCgTechnique;
CGbuffer     transform_buffer, * material_buffer, lightSet_buffer, lightSetPerView_buffer;

/* Initial scene state */
static int myAnimating = 0;
int currentLight = 0;
float eyeAngle = 1.6f;
int object_material[2] = { 0, 3 };

int material_buffer_index;
int transform_buffer_offset;
int lightSetPerView_offset;

struct MY_V3F
{
  FLOAT x, y, z;
};

static PDIRECT3DVERTEXBUFFER9 myVertexBuffer = NULL;
vector< MY_V3F > vertexList;

const double myPi = 3.14159265358979323846;

typedef float float4x4[16];
typedef struct 
{
  float4x4 modelview;
  float4x4 inverse_modelview;
  float4x4 modelview_projection;
} Transform;

#define MAX_LIGHTS 8

// D3D9 uses OpenGL's GP4 profile float4 alignment
typedef struct 
{
  float enabled[4];
  float ambient[4];
  float diffuse[4];
  float specular[4];
  float k0[4];  
  float k1[4];
  float k2[4];
} LightSourceStatic;

typedef struct 
{
  float global_ambient[4];
  LightSourceStatic source[MAX_LIGHTS];
} LightSet;

typedef struct 
{
  float position[4];
} LightSourcePerView;

typedef struct 
{
  LightSourcePerView source[MAX_LIGHTS];
} LightSetPerView;

LightSet lightSet;
LightSetPerView lightSetPerView_world, lightSetPerView_eye;



/* Forward declare helper functions and callbacks registered by main. */
void checkForCgError(const char *situation);

HRESULT CALLBACK OnResetDevice(IDirect3DDevice9*, const D3DSURFACE_DESC*, void*);
void CALLBACK OnFrameRender(IDirect3DDevice9*, double, float, void*);
void CALLBACK OnLostDevice(void*);
void CALLBACK OnFrameMove(IDirect3DDevice9*, double, float, void*);
void CALLBACK KeyboardProc(UINT, bool, bool, void*);

void InitBuffers();
void InitLight( LightSet * lightSet, int index );
void DrawLitSphere( const float projectionMatrix[16], const float viewMatrix[16], int object, float xTranslate, IDirect3DDevice9* pDev, IDirect3DVertexBuffer9 *vb );

int main(int argc, char **argv)
{
  /* Parse command line, handle default hotkeys, and show messages. */
  DXUTInit();

  DXUTSetCallbackDeviceReset(OnResetDevice);
  DXUTSetCallbackDeviceLost(OnLostDevice);
  DXUTSetCallbackFrameRender(OnFrameRender);
  DXUTSetCallbackFrameMove(OnFrameMove);
  DXUTSetCallbackKeyboard(KeyboardProc);
  DXUTCreateWindow(L"cgfx_buffer_lighting");

  bool windowed = true;
  DXUTCreateDevice(D3DADAPTER_DEFAULT, windowed, 640, 480);
  DXUTMainLoop();

  /* Demonstrate proper deallocation of Cg runtime data structures.
     Not strictly necessary if we are simply going to exit. */
  cgDestroyEffect(myCgEffect);
  checkForCgError("destroying effect");
  cgDestroyContext(myCgContext);
  cgD3D9SetDevice(NULL);

  return DXUTGetExitCode();
}

void checkForCgError(const char *situation)
{
  CGerror error;
  const char *string = cgGetLastErrorString(&error);
  
  if (error != CG_NO_ERROR) {
    if (error == CG_COMPILER_ERROR) {
      fprintf(stderr,
             "Program: %s\n"
             "Situation: %s\n"
             "Error: %s\n\n"
             "Cg compiler output...\n%s",
             myProgramName, situation, string,
             cgGetLastListing(myCgContext));
    } else {
      fprintf(stderr,
              "Program: %s\n"
              "Situation: %s\n"
              "Error: %s",
              myProgramName, situation, string);
    }
    exit(1);
  }
}

HRESULT initCg(void)
{
    HRESULT hr = S_OK;

    myCgContext = cgCreateContext();
    checkForCgError( "creating context" );

	cgD3D9RegisterStates( myCgContext );
    checkForCgError( "registering standard CgFX states" );
    
    cgD3D9SetManageTextureParameters( myCgContext, CG_TRUE );
    checkForCgError( "manage texture parameters" );


    char buffer[128];
    myCgEffect = cgCreateEffectFromFile( myCgContext, myCgFXFileName, NULL );
    sprintf_s( buffer, "creating %s effect", myCgFXFileName );
    checkForCgError( buffer );
    assert( myCgEffect );

    myCgTechnique = cgGetFirstTechnique( myCgEffect );
    while( myCgTechnique && cgValidateTechnique( myCgTechnique ) == CG_FALSE ) 
    {
        fprintf( stderr, "%s: Technique %s did not validate.  Skipping.\n", myProgramName, cgGetTechniqueName( myCgTechnique ) );
        myCgTechnique = cgGetNextTechnique( myCgTechnique );
    }
  
    if( myCgTechnique ) 
    {
        fprintf( stderr, "%s: Use technique %s.\n", myProgramName, cgGetTechniqueName( myCgTechnique ) );
    } 
    else 
    {
        fprintf( stderr, "%s: No valid technique\n", myProgramName );
        return E_FAIL;
    }
  
    InitBuffers();

    CGprogram myCgVertexProgram = cgGetPassProgram( cgGetFirstPass( myCgTechnique ), CG_VERTEX_DOMAIN );

    material_buffer_index   = cgGetParameterBufferIndex(  cgGetNamedParameter( myCgVertexProgram, "cbuffer0_Material"        ) );
    transform_buffer_offset = cgGetParameterBufferOffset( cgGetNamedParameter( myCgVertexProgram, "cbuffer1_Transform"       ) );
    lightSetPerView_offset  = cgGetParameterBufferOffset( cgGetNamedParameter( myCgVertexProgram, "cbuffer3_LightSetPerView" ) );
      
    return S_OK;
}

HRESULT initSphereVertexBuffer(IDirect3DDevice9* pDev, float radius, int slices, int stacks)
{
    const float PI = 3.1415926f;
	float phiStep = PI / stacks;
	int rings = stacks - 1;
    for( int i = 1; i <= rings; ++i )
    {
        float phi = i * phiStep;
        float phi2 = (i - 1) * phiStep;

        float thetaStep = 2.0f * PI / slices;
        for( int j = 0; j <= slices; ++j )
        {
            MY_V3F vert;
            float theta = j * thetaStep;
            float theta2 = (j-1) * thetaStep;

            vert.x = radius * sinf( phi ) * cosf( theta );
            vert.y = radius * cosf( phi );
            vert.z = radius * sinf( phi ) * sinf( theta );
		    vertexList.push_back( vert );

            vert.x = radius * sinf( phi2 ) * cosf( theta );
            vert.y = radius * cosf( phi2 );
            vert.z = radius * sinf( phi2 ) * sinf( theta );
		    vertexList.push_back( vert );

            vert.x = radius * sinf( phi2 ) * cosf( theta2 );
            vert.y = radius * cosf( phi2 );
            vert.z = radius * sinf( phi2 ) * sinf( theta2 );
		    vertexList.push_back( vert );

            vert.x = radius * sinf( phi ) * cosf( theta );
            vert.y = radius * cosf( phi );
            vert.z = radius * sinf( phi ) * sinf( theta );
		    vertexList.push_back( vert );

            vert.x = radius * sinf( phi ) * cosf( theta2 );
            vert.y = radius * cosf( phi );
            vert.z = radius * sinf( phi ) * sinf( theta2 );
		    vertexList.push_back( vert );

            vert.x = radius * sinf( phi2 ) * cosf( theta2 );
            vert.y = radius * cosf( phi2 );
            vert.z = radius * sinf( phi2 ) * sinf( theta2 );
			vertexList.push_back( vert );		
		}
    }

	if( FAILED( pDev->CreateVertexBuffer( (UINT)vertexList.size() * sizeof(MY_V3F), 0, D3DFVF_XYZ, D3DPOOL_DEFAULT, &myVertexBuffer, NULL ) ) )
    {
        return E_FAIL;
    }

    MY_V3F* pVertices;
    if( FAILED( myVertexBuffer->Lock( 0, 0, /* map entire buffer */
                                      (VOID**)&pVertices, 0) ) )
    {
        return E_FAIL;
    }

	memcpy( pVertices, &vertexList[0], vertexList.size() * sizeof(MY_V3F) );

    myVertexBuffer->Unlock();
    return S_OK;
}

HRESULT CALLBACK OnResetDevice( IDirect3DDevice9* pDev, const D3DSURFACE_DESC* backBuf, void* userContext )
{
	cgD3D9SetDevice(pDev);
	checkForCgError("setting Direct3D device");

	static int firstTime = 1;
    if (firstTime) {
      /* Cg runtime resources such as CGprogram and CGparameter handles
         survive a device reset so we just need to compile a Cg program
         just once.  We do however need to unload Cg programs with
         cgD3DUnloadProgram upon when a Direct3D device is lost and load
         Cg programs every Direct3D device reset with cgD3D9UnloadProgram. */
      initCg();
      firstTime = 0;
    }

    if (FAILED(initSphereVertexBuffer(pDev, 2, 20, 20)))
      return E_FAIL;

	double fieldOfView = 70.0;  // In degrees
    double width = backBuf->Width;
    double height = backBuf->Height;
    double aspectRatio = width / height;
    makePerspectiveMatrix( fieldOfView, aspectRatio,
                           1.0, 20.0,  /* Znear and Zfar */
                           myProjectionMatrix );

  return S_OK;
}

void CALLBACK OnLostDevice( void * userContext )
{
  myVertexBuffer->Release();
  cgD3D9SetDevice(NULL);
}


void CALLBACK OnFrameRender( IDirect3DDevice9* pDev, double time, float elapsedTime, void * userContext )
{
    float eyePosition[4];
    float viewMatrix[16];

    // Clear the back buffer        
	pDev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DXCOLOR( 0.1f, 0.3f, 0.6f, 1.0f ), 1.0f, 0);
	pDev->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	pDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    
    if (FAILED(pDev->BeginScene())) 
      return;

    // Update latest eye position.
    eyePosition[0] = 8.0f * cos( eyeAngle );
    eyePosition[1] = 0.0f;
    eyePosition[2] = -8.0f * sin( eyeAngle );
    eyePosition[3] = 1.0f;

    // Compute current view matrix.
    makeLookAtMatrix( eyePosition[0], eyePosition[1], eyePosition[2],   /* eye position */
                      0, 0, 0,                                          /* view center */
                      0, 1, 0,                                          /* up vector */
                      viewMatrix );

    // For each light, convert its world-space position to eye-space
    for( int i = 0; i < 2; ++i ) 
    {
        // Le[i] = V * Lw[i]
        transformVector( lightSetPerView_eye.source[i].position, viewMatrix, lightSetPerView_world.source[i].position );
    }
  
    // Update light set per-view buffer
    cgSetBufferSubData( lightSetPerView_buffer, lightSetPerView_offset, sizeof( lightSetPerView_eye ), &lightSetPerView_eye );
    
    DrawLitSphere( myProjectionMatrix, viewMatrix, 0, 3.2f, pDev, myVertexBuffer );
    DrawLitSphere( myProjectionMatrix, viewMatrix, 1, -3.2f, pDev, myVertexBuffer );

	pDev->EndScene();
}

void advanceAnimation()
{
    eyeAngle += 0.01f;

    if( eyeAngle > 2 * myPi )
        eyeAngle -= 2 * myPi;
}

void CALLBACK OnFrameMove( IDirect3DDevice9* pDev, double time, float elapsedTime, void* userContext )
{
    if( myAnimating )
        advanceAnimation();
}


//--------------------------------------------------------------------------------------
// Create the CGbuffers
//--------------------------------------------------------------------------------------
void InitBuffers()
{
    memset( &lightSet, 0, sizeof( lightSet ) );
    lightSet.global_ambient[0] = 0.15f;
    lightSet.global_ambient[1] = 0.15f;
    lightSet.global_ambient[2] = 0.15f;
   
    InitLight( &lightSet, 0 );
    InitLight( &lightSet, 1 );

    lightSetPerView_world.source[0].position[0] = 0.0f;
    lightSetPerView_world.source[0].position[1] = 2.0f;
    lightSetPerView_world.source[0].position[2] = 4.0f;
    lightSetPerView_world.source[0].position[3] = -1.0f;

    lightSetPerView_world.source[1].position[0] = 0.0f;
    lightSetPerView_world.source[1].position[1] = -2.0f;
    lightSetPerView_world.source[1].position[2] = 4.0f;
    lightSetPerView_world.source[1].position[3] = -1.0f;

    CGprogram myCgVertexProgram   = cgGetPassProgram( cgGetFirstPass( myCgTechnique ), CG_VERTEX_DOMAIN );
    CGprogram myCgFragmentProgram = cgGetPassProgram( cgGetFirstPass( myCgTechnique ), CG_FRAGMENT_DOMAIN );

    CGparameter bufferParam = (CGparameter)0;
    int bufferParamIndex    = -1;

    transform_buffer = cgCreateBuffer( myCgContext, 3 * 16 * sizeof( float ), NULL, CG_BUFFER_USAGE_DYNAMIC_DRAW );
    bufferParam      = cgGetNamedParameter( myCgVertexProgram, "cbuffer1_Transform" );
    bufferParamIndex = cgGetParameterBufferIndex( bufferParam );
      
    cgSetProgramBuffer( myCgVertexProgram, bufferParamIndex, transform_buffer );

    lightSet_buffer  = cgCreateBuffer( myCgContext, sizeof( lightSet ), &lightSet, CG_BUFFER_USAGE_STATIC_DRAW );  
    bufferParam      = cgGetNamedParameter( myCgFragmentProgram, "cbuffer2_LightSetStatic" );
    bufferParamIndex = cgGetParameterBufferIndex( bufferParam );
  
    cgSetProgramBuffer( myCgFragmentProgram, bufferParamIndex, lightSet_buffer );

    lightSetPerView_buffer = cgCreateBuffer( myCgContext, sizeof( LightSetPerView ), NULL, CG_BUFFER_USAGE_DYNAMIC_DRAW );
    bufferParam            = cgGetNamedParameter( myCgFragmentProgram, "cbuffer3_LightSetPerView" );
    bufferParamIndex       = cgGetParameterBufferIndex( bufferParam );

    cgSetProgramBuffer( myCgFragmentProgram, bufferParamIndex, lightSetPerView_buffer );

    // Create a set of material buffers.
    material_buffer = (CGbuffer*)malloc( sizeof( CGbuffer ) * materialInfoCount );    
    for( int i = 0; i < materialInfoCount; ++i )
        material_buffer[i] = cgCreateBuffer( myCgContext, sizeof( MaterialData ), &materialInfo[i].data, CG_BUFFER_USAGE_STATIC_DRAW );  

    checkForCgError( "InitBuffers" );
}

//--------------------------------------------------------------------------------------
// Initialize the light's properties
//--------------------------------------------------------------------------------------
void InitLight( LightSet * lightSet, int index )
{
    if( lightSet == NULL )
        return;

    lightSet->source[index].enabled[0]  = 1.0f;
    lightSet->source[index].ambient[0]  = 0.0f;
    lightSet->source[index].ambient[1]  = 0.0f;
    lightSet->source[index].ambient[2]  = 0.0f;
    lightSet->source[index].diffuse[0]  = 0.9f;
    lightSet->source[index].diffuse[1]  = 0.9f;
    lightSet->source[index].diffuse[2]  = 0.9f;
    lightSet->source[index].specular[0] = 0.9f;
    lightSet->source[index].specular[1] = 0.9f;
    lightSet->source[index].specular[2] = 0.9f;
    
    // Inverse square law attenuation    
    lightSet->source[index].k0[0] = 0.7f;
    lightSet->source[index].k1[0] = 0.0f;
    lightSet->source[index].k2[0] = 0.001f;
}

void BindMaterialBuffer( int object )
{
    CGprogram myCgFragmentProgram = cgGetPassProgram( cgGetFirstPass( myCgTechnique ), CG_FRAGMENT_DOMAIN );
    cgSetProgramBuffer( myCgFragmentProgram, material_buffer_index, material_buffer[object_material[object]] );
    checkForCgError( "set material buffer" );
}

void UpdateTransformBuffer( Transform *transform )
{
    cgSetBufferSubData( transform_buffer, transform_buffer_offset, sizeof( Transform ), transform );
	checkForCgError( "update transform buffer" );
}


HRESULT drawSphere( IDirect3DDevice9* pDev, IDirect3DVertexBuffer9 *vb )
{
    HRESULT hr = S_OK;

    hr = pDev->SetStreamSource(0, vb, 0, sizeof(MY_V3F));
    if( FAILED( hr ) )
        return hr;

    hr = pDev->SetFVF( D3DFVF_XYZ );
    if( FAILED( hr ) )
        return hr;

    hr = pDev->DrawPrimitive( D3DPT_TRIANGLELIST, 0, (UINT) vertexList.size() / 3 );
  
    return hr;
}

void DrawLitSphere( const float projectionMatrix[16], const float viewMatrix[16], int object, float xTranslate, IDirect3DDevice9* pDev, IDirect3DVertexBuffer9 *vb )
{
    Transform transform;
    float modelMatrix[16];

    makeTranslateMatrix( xTranslate, 0, 0, modelMatrix );
    multMatrix( transform.modelview, viewMatrix, modelMatrix );
    multMatrix( transform.modelview_projection, projectionMatrix, transform.modelview );
    invertMatrix( transform.inverse_modelview, transform.modelview );
  
    UpdateTransformBuffer( &transform );
    BindMaterialBuffer( object );

    CGpass pass = cgGetFirstPass( myCgTechnique );
    while( pass ) 
    {
        cgSetPassState( pass );
    
           drawSphere( pDev, myVertexBuffer );
    
        cgResetPassState( pass );
        pass = cgGetNextPass( pass );
    }
}


void CALLBACK KeyboardProc( UINT nChar, bool keyDown, bool altDown, void * userContext )
{
    static int wireframe = 0;

    if( !keyDown )
        return;

    switch( nChar )
    {
	    case ' ':
		    myAnimating = !myAnimating;
	    break;

	    case '1':
		    currentLight = 0;
		break;

	    case '2':
		    currentLight = 1;
		break;

	    case '3':
        {
		    ++object_material[0];
		    
            if( object_material[0] >= materialInfoCount )
		        object_material[0] = 0;                                       
        }
		break;

	    case '4':
        {
		    ++object_material[1];
    		
            if( object_material[1] >= materialInfoCount )
			    object_material[1] = 0;
        }
	    break;

        case 27:  /* Esc key */
            // DXUT handles Escape to Exit
        break;
    }
}
