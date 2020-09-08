#if defined(_WIN32) && defined(_MSC_VER) && _MSC_VER>=1400 /* D3D10 requires VC8 */

#ifndef LCGD3D10_LOADER_H
#define LCGD3D10_LOADER_H

#include <stdio.h>
#include <sal.h>
#include <rpcsal.h>
#define CGD3D10_EXPLICIT
#include <Cg/cgD3D10.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Loader API */

extern int         lcgD3D10Init(const char *filename);
extern void        lcgD3D10List(const char *prefix, FILE *out);
extern void        lcgD3D10Destroy(void);
extern const char *lcgD3D10GetProcName(void **function);
extern int         lcgD3D10HasVersion(void ***version);

extern void ***lcgD3D10Version2_1_0000();
extern void ***lcgD3D10Version3_0_0000();
extern void ***lcgD3D10Version3_1_0000();

/* Internals */

typedef struct _LcgD3D10Handle *LcgD3D10Handle;

extern LcgD3D10Handle lcgD3D10Handle;

extern LcgD3D10Handle   lcgD3D10LoadLibrary(const char *filename);
extern int         lcgD3D10FreeLibrary(LcgD3D10Handle handle);
extern void *      lcgD3D10GetProcAddress(LcgD3D10Handle handle, const char *name);
extern const char *lcgD3D10GetModuleFileName(LcgD3D10Handle handle, void *function);

/* Typedefs */

typedef HRESULT (*PFNCGD3D10BINDPROGRAMPROC)(CGprogram);
typedef CGbuffer (*PFNCGD3D10CREATEBUFFERPROC)(CGcontext, int, const void *, D3D10_USAGE);
typedef CGbuffer (*PFNCGD3D10CREATEBUFFERFROMOBJECTPROC)(CGcontext, ID3D10Buffer *, CGbool);
typedef ID3D10Buffer *(*PFNCGD3D10GETBUFFERBYINDEXPROC)(CGprogram, UINT);
typedef ID3D10Buffer *(*PFNCGD3D10GETBUFFEROBJECTPROC)(CGbuffer);
typedef ID3D10Blob *(*PFNCGD3D10GETCOMPILEDPROGRAMPROC)(CGprogram);
typedef ID3D10Device *(*PFNCGD3D10GETDEVICEPROC)(CGcontext);
typedef ID3D10Blob *(*PFNCGD3D10GETIASIGNATUREBYPASSPROC)(CGpass);
typedef HRESULT (*PFNCGD3D10GETLASTERRORPROC)();
typedef CGprofile (*PFNCGD3D10GETLATESTGEOMETRYPROFILEPROC)();
typedef CGprofile (*PFNCGD3D10GETLATESTPIXELPROFILEPROC)();
typedef CGprofile (*PFNCGD3D10GETLATESTVERTEXPROFILEPROC)();
typedef CGbool (*PFNCGD3D10GETMANAGETEXTUREPARAMETERSPROC)(CGcontext);
typedef const char **(*PFNCGD3D10GETOPTIMALOPTIONSPROC)(CGprofile);
typedef ID3D10Blob *(*PFNCGD3D10GETPROGRAMERRORSPROC)(CGprogram);
typedef CGbool (*PFNCGD3D10ISPROFILESUPPORTEDPROC)(CGprofile);
typedef CGbool (*PFNCGD3D10ISPROGRAMLOADEDPROC)(CGprogram);
typedef HRESULT (*PFNCGD3D10LOADPROGRAMPROC)(CGprogram, UINT);
typedef void (*PFNCGD3D10REGISTERSTATESPROC)(CGcontext);
typedef HRESULT (*PFNCGD3D10SETDEVICEPROC)(CGcontext, ID3D10Device *);
typedef void (*PFNCGD3D10SETMANAGETEXTUREPARAMETERSPROC)(CGcontext, CGbool);
typedef void (*PFNCGD3D10SETSAMPLERSTATEPARAMETERPROC)(CGparameter, ID3D10SamplerState *);
typedef void (*PFNCGD3D10SETTEXTUREPARAMETERPROC)(CGparameter, ID3D10Resource *);
typedef void (*PFNCGD3D10SETTEXTURESAMPLERSTATEPARAMETERPROC)(CGparameter, ID3D10Resource *, ID3D10SamplerState *);
typedef const char *(*PFNCGD3D10TRANSLATECGERRORPROC)(CGerror);
typedef const char *(*PFNCGD3D10TRANSLATEHRESULTPROC)(HRESULT);
typedef DWORD (*PFNCGD3D10TYPETOSIZEPROC)(CGtype);
typedef void (*PFNCGD3D10UNBINDPROGRAMPROC)(CGprogram);
typedef void (*PFNCGD3D10UNLOADPROGRAMPROC)(CGprogram);

/* Declarations */

extern PFNCGD3D10BINDPROGRAMPROC cgD3D10BindProgram;
extern PFNCGD3D10CREATEBUFFERPROC cgD3D10CreateBuffer;
extern PFNCGD3D10CREATEBUFFERFROMOBJECTPROC cgD3D10CreateBufferFromObject;
extern PFNCGD3D10GETBUFFERBYINDEXPROC cgD3D10GetBufferByIndex;
extern PFNCGD3D10GETBUFFEROBJECTPROC cgD3D10GetBufferObject;
extern PFNCGD3D10GETCOMPILEDPROGRAMPROC cgD3D10GetCompiledProgram;
extern PFNCGD3D10GETDEVICEPROC cgD3D10GetDevice;
extern PFNCGD3D10GETIASIGNATUREBYPASSPROC cgD3D10GetIASignatureByPass;
extern PFNCGD3D10GETLASTERRORPROC cgD3D10GetLastError;
extern PFNCGD3D10GETLATESTGEOMETRYPROFILEPROC cgD3D10GetLatestGeometryProfile;
extern PFNCGD3D10GETLATESTPIXELPROFILEPROC cgD3D10GetLatestPixelProfile;
extern PFNCGD3D10GETLATESTVERTEXPROFILEPROC cgD3D10GetLatestVertexProfile;
extern PFNCGD3D10GETMANAGETEXTUREPARAMETERSPROC cgD3D10GetManageTextureParameters;
extern PFNCGD3D10GETOPTIMALOPTIONSPROC cgD3D10GetOptimalOptions;
extern PFNCGD3D10GETPROGRAMERRORSPROC cgD3D10GetProgramErrors;
extern PFNCGD3D10ISPROFILESUPPORTEDPROC cgD3D10IsProfileSupported;
extern PFNCGD3D10ISPROGRAMLOADEDPROC cgD3D10IsProgramLoaded;
extern PFNCGD3D10LOADPROGRAMPROC cgD3D10LoadProgram;
extern PFNCGD3D10REGISTERSTATESPROC cgD3D10RegisterStates;
extern PFNCGD3D10SETDEVICEPROC cgD3D10SetDevice;
extern PFNCGD3D10SETMANAGETEXTUREPARAMETERSPROC cgD3D10SetManageTextureParameters;
extern PFNCGD3D10SETSAMPLERSTATEPARAMETERPROC cgD3D10SetSamplerStateParameter;
extern PFNCGD3D10SETTEXTUREPARAMETERPROC cgD3D10SetTextureParameter;
extern PFNCGD3D10SETTEXTURESAMPLERSTATEPARAMETERPROC cgD3D10SetTextureSamplerStateParameter;
extern PFNCGD3D10TRANSLATECGERRORPROC cgD3D10TranslateCGerror;
extern PFNCGD3D10TRANSLATEHRESULTPROC cgD3D10TranslateHRESULT;
extern PFNCGD3D10TYPETOSIZEPROC cgD3D10TypeToSize;
extern PFNCGD3D10UNBINDPROGRAMPROC cgD3D10UnbindProgram;
extern PFNCGD3D10UNLOADPROGRAMPROC cgD3D10UnloadProgram;

#ifdef __cplusplus
}
#endif

#endif
#endif
