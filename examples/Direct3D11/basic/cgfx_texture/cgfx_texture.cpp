/* cgfx_texture.cpp */

#include <windows.h>
#include <stdio.h>
#include <assert.h>
#include <d3d11.h>       /* Direct3D10 API: Can't include this?  Is DirectX SDK installed? */
#include <Cg/cg.h>       /* Can't include this?  Is Cg Toolkit installed? */
#include <Cg/cgD3D11.h>  /* Can't include this?  Is Cg Toolkit installed? */

#include <d3dx11.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")

#ifndef SAFE_RELEASE
#define SAFE_RELEASE( p ) { if( p ) { ( p )->Release(); ( p ) = NULL; } }
#endif


//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------
struct Vertex3
{
    float x, y, z, s, t;
};

//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------
HINSTANCE                   g_hInst             = NULL;  
HWND                        g_hWnd              = NULL;
D3D_DRIVER_TYPE             g_driverType        = D3D_DRIVER_TYPE_NULL;
ID3D11Device *              g_pDevice           = NULL;
ID3D11DeviceContext *       g_pDeviceContext    = NULL;
IDXGISwapChain *            g_pSwapChain        = NULL;
ID3D11RenderTargetView *    g_pRenderTargetView = NULL;

ID3D11InputLayout *         g_pVertexLayout = NULL;
ID3D11Buffer *              g_pVB           = NULL;

const int Width  = 400;
const int Height = 400;

float ClearColor[4] = { 0.0f, 0.0f, 1.0f, 1.0f }; // RGBA

/* Cg global variables */
CGcontext    myCgContext;
CGeffect     myCgEffect;
CGtechnique  myCgTechnique;

CGparameter myCgEffect_decal;

const TCHAR * myProgramName  = L"cgfx_texture";
const char *  myCgFXFileName = "cgfx_texture.cgfx"; // Use char here since that's what the Cg runtime expects
const TCHAR * myTextureName  = L"NVIDIA.png";

//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
HRESULT             InitWindow( HINSTANCE, int );
HRESULT             InitDevice();
void                CleanupDevice();
LRESULT CALLBACK    WndProc( HWND, UINT, WPARAM, LPARAM );
void                Render();
HRESULT             InitCg();
void                CleanupCg();

HRESULT             CreateVertexBuffer();

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
    MSG msg = { 0 };

    if( FAILED( InitWindow( hInstance, nCmdShow ) ) )
        return 0;

    if( FAILED( InitDevice() ) )
    {
        CleanupDevice();
        return 0;
    }

    if( FAILED( InitCg() ) || FAILED( CreateVertexBuffer() ) )
    {
        CleanupDevice();
        CleanupCg();
        return 0;
    }
    
    // Main message loop    
    while( WM_QUIT != msg.message )
    {
        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
        {
            Render();  
        }
    }

    CleanupDevice();
    CleanupCg();

    return (int)msg.wParam;
}

//--------------------------------------------------------------------------------------
// Register class and create window
//--------------------------------------------------------------------------------------
HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow )
{
    g_hInst = hInstance; 
    RECT rc = { 0, 0, Width, Height };

    // Register class
    WNDCLASSEX wcex;
    wcex.cbSize         = sizeof(WNDCLASSEX); 
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = NULL;
    wcex.hCursor        = LoadCursor( NULL, IDC_ARROW );
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = myProgramName;
    wcex.hIconSm        = NULL;

    if( !RegisterClassEx( &wcex ) )
        return E_FAIL;

    // Create window    
    AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );
    g_hWnd = CreateWindow( myProgramName,          // Class name
                           myProgramName,          // Window name
                           WS_OVERLAPPEDWINDOW,    // Style
                           CW_USEDEFAULT,          // X position
                           CW_USEDEFAULT,          // Y position
                           rc.right - rc.left,     // Width
                           rc.bottom - rc.top,     // Height
                           NULL,                   // Parent HWND
                           NULL,                   // Menu
                           hInstance,              // Instance
                           NULL                    // Param
                         );
    if( !g_hWnd )
        return E_FAIL;

    ShowWindow( g_hWnd, nCmdShow );
   
    return S_OK;
}


//--------------------------------------------------------------------------------------
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------
HRESULT InitDevice()
{
    HRESULT hr = S_OK;

    RECT rc;
    GetClientRect( g_hWnd, &rc );
    UINT width  = rc.right  - rc.left;
    UINT height = rc.bottom - rc.top;

    UINT createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_DRIVER_TYPE driverTypes[] = 
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_REFERENCE,
    };

    UINT numDriverTypes = sizeof( driverTypes ) / sizeof( driverTypes[0] );

    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory( &sd, sizeof( sd ) );
    sd.BufferCount                        = 1;
    sd.BufferDesc.Width                   = width;
    sd.BufferDesc.Height                  = height;
    sd.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator   = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow                       = g_hWnd;
    sd.SampleDesc.Count                   = 1;
    sd.SampleDesc.Quality                 = 0;
    sd.Windowed                           = TRUE;

    D3D_FEATURE_LEVEL FeatureLevels     = D3D_FEATURE_LEVEL_11_0;
    D3D_FEATURE_LEVEL *pFeatureLevel    = NULL;

    for( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ )
    {
        g_driverType = driverTypes[driverTypeIndex];
        hr = D3D11CreateDeviceAndSwapChain( NULL,                  // Adapter
                                            g_driverType,          // Driver Type
                                            NULL,                  // Software
                                            createDeviceFlags,     // Flags
                                            &FeatureLevels,        // Feature Levels
                                            1,                     // Num Feature Levels
                                            D3D11_SDK_VERSION,     // SDK Version
                                            &sd,                   // Swap Chain Desc
                                            &g_pSwapChain,         // Swap Chain
                                            &g_pDevice,            // Device
                                            pFeatureLevel,         // Feature Level
                                            &g_pDeviceContext );   // Device Context

        if( SUCCEEDED( hr ) )
            break;
    }

    if( FAILED(hr) )
        return hr;

    // Create a render target view
    ID3D11Texture2D *pBuffer;
    hr = g_pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), (LPVOID*)&pBuffer );

    if( FAILED(hr) )
        return hr;

    hr = g_pDevice->CreateRenderTargetView( pBuffer, NULL, &g_pRenderTargetView );
    pBuffer->Release();

    if( FAILED(hr) )
        return hr;

    g_pDeviceContext->OMSetRenderTargets( 1, &g_pRenderTargetView, NULL );

    // Setup the viewport
    D3D11_VIEWPORT vp;
    vp.Width    = static_cast<FLOAT>(width);
    vp.Height   = static_cast<FLOAT>(height);
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    g_pDeviceContext->RSSetViewports( 1, &vp );      

    return S_OK;
}

//--------------------------------------------------------------------------------------
// Utility function for reporting Cg errors
//--------------------------------------------------------------------------------------
static void checkForCgError( const char * situation, bool _exit = true )
{
    CGerror error;
    const char *string = cgGetLastErrorString(&error);

    if( error != CG_NO_ERROR ) 
    {
        if( error == CG_COMPILER_ERROR ) 
        {
            fprintf(stderr,
                "Program: %s\n"
                "Situation: %s\n"
                "Error: %s\n\n"
                "Cg compiler output...\n%s",
                myProgramName, situation, string,
                cgGetLastListing(myCgContext));
        } 
        else 
        {
            fprintf(stderr,
                "Program: %s\n"
                "Situation: %s\n"
                "Error: %s",
                myProgramName, situation, string);
        }

        if( _exit )
            exit(1);
    }
}

//--------------------------------------------------------------------------------------
// Create Cg objects
//--------------------------------------------------------------------------------------
HRESULT InitCg()
{
    HRESULT hr = S_OK;

    myCgContext = cgCreateContext();
    checkForCgError( "creating context" );

    hr = cgD3D11SetDevice( myCgContext, g_pDevice );
    checkForCgError( "setting Direct3D device", false );
    if( hr != S_OK )
        return hr;

    cgD3D11RegisterStates( myCgContext );
    checkForCgError( "registering standard CgFX states" );
    
    cgD3D11SetManageTextureParameters( myCgContext, CG_TRUE );
    checkForCgError( "manage texture parameters" );


    myCgEffect = cgCreateEffectFromFile( myCgContext, myCgFXFileName, NULL );
    checkForCgError( "creating cgfx_texture.cgfx effect" );
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
  
    const D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },     
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    CGpass myPass = cgGetFirstPass( myCgTechnique );

    ID3D10Blob * pVSBuf = cgD3D11GetIASignatureByPass( myPass );

    hr = g_pDevice->CreateInputLayout( layout, 2, pVSBuf->GetBufferPointer(), pVSBuf->GetBufferSize(), &g_pVertexLayout ); 
    if( hr != S_OK )
        return E_FAIL;

    myCgEffect_decal = cgGetNamedEffectParameter( myCgEffect, "Decal" );
        
    D3DX11_IMAGE_INFO fileInfo;
    D3DX11GetImageInfoFromFile( myTextureName, NULL, &fileInfo, NULL );

    D3DX11_IMAGE_LOAD_INFO loadInfo;
    loadInfo.Width          = fileInfo.Width;
    loadInfo.Height         = fileInfo.Height;
    loadInfo.FirstMipLevel  = 0;
    loadInfo.MipLevels      = fileInfo.MipLevels;
    loadInfo.Usage          = D3D11_USAGE_DEFAULT;
    loadInfo.BindFlags      = D3D11_BIND_SHADER_RESOURCE;
    loadInfo.CpuAccessFlags = 0;
    loadInfo.MiscFlags      = 0;
    loadInfo.Format         = fileInfo.Format;    
    loadInfo.Filter         = D3DX11_FILTER_NONE;
    loadInfo.MipFilter      = D3DX11_FILTER_NONE;
    loadInfo.pSrcInfo       = &fileInfo;
    
    ID3D11Resource * texture = NULL;
    hr = D3DX11CreateTextureFromFile( g_pDevice, myTextureName, &loadInfo, NULL, &texture, NULL );
    if( hr != S_OK )
        return hr;  

    cgD3D11SetTextureParameter( myCgEffect_decal, texture );
    cgSetSamplerState( myCgEffect_decal );

    return S_OK;
}

//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------
void CleanupDevice()
{
    SAFE_RELEASE( g_pVertexLayout );
    SAFE_RELEASE( g_pVB );

    if( g_pDeviceContext )      g_pDeviceContext->ClearState();

    if( g_pRenderTargetView )   g_pRenderTargetView->Release();
    if( g_pSwapChain )          g_pSwapChain->Release();
    if( g_pDevice )             g_pDevice->Release();

    SAFE_RELEASE( g_pDevice );
    SAFE_RELEASE( g_pDeviceContext );
}

//--------------------------------------------------------------------------------------
// Clean up the cg objects we've created
//--------------------------------------------------------------------------------------
void CleanupCg()
{
    cgDestroyEffect( myCgEffect );
    checkForCgError( "destroying effect" );
  
    cgD3D11SetDevice( myCgContext, NULL );

    cgDestroyContext( myCgContext );  
}

//--------------------------------------------------------------------------------------
// Create vertex buffer for triangle
//--------------------------------------------------------------------------------------
HRESULT CreateVertexBuffer()
{
    HRESULT hr = S_OK;

    static const Vertex3 triangleVertices[3] = 
    {
        { -0.8f,  0.8f, 0.0f, 0.0f, 0.0f },
        {  0.8f,  0.8f, 0.0f, 1.0f, 0.0f },
        {  0.0f, -0.8f, 0.0f, 0.5f, 1.0f }
    };

    D3D11_BUFFER_DESC vbDesc;
    vbDesc.ByteWidth      = 3 * sizeof( Vertex3 );
    vbDesc.Usage          = D3D11_USAGE_DEFAULT;
    vbDesc.BindFlags      = D3D11_BIND_VERTEX_BUFFER;
    vbDesc.CPUAccessFlags = 0;
    vbDesc.MiscFlags      = 0;

    D3D11_SUBRESOURCE_DATA vbInitData;
    ZeroMemory( &vbInitData, sizeof( D3D11_SUBRESOURCE_DATA ) );

    vbInitData.pSysMem = triangleVertices;

    hr = g_pDevice->CreateBuffer( &vbDesc, &vbInitData, &g_pVB );
    if( hr != S_OK )
        return hr;

    return S_OK;
}

//--------------------------------------------------------------------------------------
// Render a frame
//--------------------------------------------------------------------------------------
void Render()
{   
    CGpass pass;
    UINT strides[1] = { sizeof( Vertex3 ) };
    UINT offsets[1] = { 0 };
    ID3D11Buffer * pBuffers[1] = { g_pVB };

    // Clear the back buffer        
    g_pDeviceContext->ClearRenderTargetView( g_pRenderTargetView, ClearColor );
    
    g_pDeviceContext->IASetVertexBuffers( 0, 1, pBuffers, strides, offsets );
    g_pDeviceContext->IASetInputLayout( g_pVertexLayout );    
    g_pDeviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );   

    pass = cgGetFirstPass( myCgTechnique );
    while( pass ) 
    {
        cgSetPassState( pass );
    
        g_pDeviceContext->Draw( 3, 0 );
    
        cgResetPassState( pass );
        pass = cgGetNextPass( pass );
    }
     
    g_pSwapChain->Present( 0, 0 );
}

//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    switch( message ) 
    {
        case WM_KEYDOWN:
            switch( wParam )
            {
                case VK_ESCAPE:
                    PostQuitMessage( 0 );
                    break;
            }
            break;

        case WM_DESTROY:
            PostQuitMessage( 0 );
            break;

        default:
            return DefWindowProc( hWnd, message, wParam, lParam );
    }

    return 0;
}
