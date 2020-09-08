#ifndef LCGGL_LOADER_H
#define LCGGL_LOADER_H

#include <stdio.h>
#define CGGL_EXPLICIT
#include <Cg/cgGL.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Loader API */

extern int         lcgGLInit(const char *filename);
extern void        lcgGLList(const char *prefix, FILE *out);
extern void        lcgGLDestroy(void);
extern const char *lcgGLGetProcName(void **function);
extern int         lcgGLHasVersion(void ***version);

extern void ***lcgGLVersion1_1_0000();
extern void ***lcgGLVersion1_2_0000();
extern void ***lcgGLVersion1_4_0000();
extern void ***lcgGLVersion1_5_0000();
extern void ***lcgGLVersion2_0_0000();
extern void ***lcgGLVersion2_1_0000();
extern void ***lcgGLVersion2_2_0000();
extern void ***lcgGLVersion3_1_0000();

/* Internals */

typedef struct _LcgGLHandle *LcgGLHandle;

extern LcgGLHandle lcgGLHandle;

extern LcgGLHandle   lcgGLLoadLibrary(const char *filename);
extern int         lcgGLFreeLibrary(LcgGLHandle handle);
extern void *      lcgGLGetProcAddress(LcgGLHandle handle, const char *name);
extern const char *lcgGLGetModuleFileName(LcgGLHandle handle, void *function);

/* Typedefs */

typedef void (*PFNCGGLBINDPROGRAMPROC)(CGprogram);
typedef CGbuffer (*PFNCGGLCREATEBUFFERPROC)(CGcontext, int, const void *, GLenum);
typedef CGbuffer (*PFNCGGLCREATEBUFFERFROMOBJECTPROC)(CGcontext, GLuint, CGbool);
typedef CGGLglslversion (*PFNCGGLDETECTGLSLVERSIONPROC)();
typedef void (*PFNCGGLDISABLECLIENTSTATEPROC)(CGparameter);
typedef void (*PFNCGGLDISABLEPROFILEPROC)(CGprofile);
typedef void (*PFNCGGLDISABLEPROGRAMPROFILESPROC)(CGprogram);
typedef void (*PFNCGGLDISABLETEXTUREPARAMETERPROC)(CGparameter);
typedef void (*PFNCGGLENABLECLIENTSTATEPROC)(CGparameter);
typedef void (*PFNCGGLENABLEPROFILEPROC)(CGprofile);
typedef void (*PFNCGGLENABLEPROGRAMPROFILESPROC)(CGprogram);
typedef void (*PFNCGGLENABLETEXTUREPARAMETERPROC)(CGparameter);
typedef GLuint (*PFNCGGLGETBUFFEROBJECTPROC)(CGbuffer);
typedef CGGLglslversion (*PFNCGGLGETCONTEXTGLSLVERSIONPROC)(CGcontext);
typedef char const **(*PFNCGGLGETCONTEXTOPTIMALOPTIONSPROC)(CGcontext, CGprofile);
typedef CGGLglslversion (*PFNCGGLGETGLSLVERSIONPROC)(const char *);
typedef const char *(*PFNCGGLGETGLSLVERSIONSTRINGPROC)(CGGLglslversion);
typedef CGprofile (*PFNCGGLGETLATESTPROFILEPROC)(CGGLenum);
typedef CGbool (*PFNCGGLGETMANAGETEXTUREPARAMETERSPROC)(CGcontext);
typedef void (*PFNCGGLGETMATRIXPARAMETERARRAYDCPROC)(CGparameter, long, long, double *);
typedef void (*PFNCGGLGETMATRIXPARAMETERARRAYDRPROC)(CGparameter, long, long, double *);
typedef void (*PFNCGGLGETMATRIXPARAMETERARRAYFCPROC)(CGparameter, long, long, float *);
typedef void (*PFNCGGLGETMATRIXPARAMETERARRAYFRPROC)(CGparameter, long, long, float *);
typedef void (*PFNCGGLGETMATRIXPARAMETERDCPROC)(CGparameter, double *);
typedef void (*PFNCGGLGETMATRIXPARAMETERDRPROC)(CGparameter, double *);
typedef void (*PFNCGGLGETMATRIXPARAMETERFCPROC)(CGparameter, float *);
typedef void (*PFNCGGLGETMATRIXPARAMETERFRPROC)(CGparameter, float *);
typedef char const **(*PFNCGGLGETOPTIMALOPTIONSPROC)(CGprofile);
typedef void (*PFNCGGLGETPARAMETER1DPROC)(CGparameter, double *);
typedef void (*PFNCGGLGETPARAMETER1FPROC)(CGparameter, float *);
typedef void (*PFNCGGLGETPARAMETER2DPROC)(CGparameter, double *);
typedef void (*PFNCGGLGETPARAMETER2FPROC)(CGparameter, float *);
typedef void (*PFNCGGLGETPARAMETER3DPROC)(CGparameter, double *);
typedef void (*PFNCGGLGETPARAMETER3FPROC)(CGparameter, float *);
typedef void (*PFNCGGLGETPARAMETER4DPROC)(CGparameter, double *);
typedef void (*PFNCGGLGETPARAMETER4FPROC)(CGparameter, float *);
typedef void (*PFNCGGLGETPARAMETERARRAY1DPROC)(CGparameter, long, long, double *);
typedef void (*PFNCGGLGETPARAMETERARRAY1FPROC)(CGparameter, long, long, float *);
typedef void (*PFNCGGLGETPARAMETERARRAY2DPROC)(CGparameter, long, long, double *);
typedef void (*PFNCGGLGETPARAMETERARRAY2FPROC)(CGparameter, long, long, float *);
typedef void (*PFNCGGLGETPARAMETERARRAY3DPROC)(CGparameter, long, long, double *);
typedef void (*PFNCGGLGETPARAMETERARRAY3FPROC)(CGparameter, long, long, float *);
typedef void (*PFNCGGLGETPARAMETERARRAY4DPROC)(CGparameter, long, long, double *);
typedef void (*PFNCGGLGETPARAMETERARRAY4FPROC)(CGparameter, long, long, float *);
typedef GLuint (*PFNCGGLGETPROGRAMIDPROC)(CGprogram);
typedef GLenum (*PFNCGGLGETTEXTUREENUMPROC)(CGparameter);
typedef GLuint (*PFNCGGLGETTEXTUREPARAMETERPROC)(CGparameter);
typedef CGbool (*PFNCGGLISPROFILESUPPORTEDPROC)(CGprofile);
typedef CGbool (*PFNCGGLISPROGRAMLOADEDPROC)(CGprogram);
typedef void (*PFNCGGLLOADPROGRAMPROC)(CGprogram);
typedef void (*PFNCGGLREGISTERSTATESPROC)(CGcontext);
typedef void (*PFNCGGLSETCONTEXTGLSLVERSIONPROC)(CGcontext, CGGLglslversion);
typedef void (*PFNCGGLSETCONTEXTOPTIMALOPTIONSPROC)(CGcontext, CGprofile);
typedef void (*PFNCGGLSETDEBUGMODEPROC)(CGbool);
typedef void (*PFNCGGLSETMANAGETEXTUREPARAMETERSPROC)(CGcontext, CGbool);
typedef void (*PFNCGGLSETMATRIXPARAMETERARRAYDCPROC)(CGparameter, long, long, const double *);
typedef void (*PFNCGGLSETMATRIXPARAMETERARRAYDRPROC)(CGparameter, long, long, const double *);
typedef void (*PFNCGGLSETMATRIXPARAMETERARRAYFCPROC)(CGparameter, long, long, const float *);
typedef void (*PFNCGGLSETMATRIXPARAMETERARRAYFRPROC)(CGparameter, long, long, const float *);
typedef void (*PFNCGGLSETMATRIXPARAMETERDCPROC)(CGparameter, const double *);
typedef void (*PFNCGGLSETMATRIXPARAMETERDRPROC)(CGparameter, const double *);
typedef void (*PFNCGGLSETMATRIXPARAMETERFCPROC)(CGparameter, const float *);
typedef void (*PFNCGGLSETMATRIXPARAMETERFRPROC)(CGparameter, const float *);
typedef void (*PFNCGGLSETOPTIMALOPTIONSPROC)(CGprofile);
typedef void (*PFNCGGLSETPARAMETER1DPROC)(CGparameter, double);
typedef void (*PFNCGGLSETPARAMETER1DVPROC)(CGparameter, const double *);
typedef void (*PFNCGGLSETPARAMETER1FPROC)(CGparameter, float);
typedef void (*PFNCGGLSETPARAMETER1FVPROC)(CGparameter, const float *);
typedef void (*PFNCGGLSETPARAMETER2DPROC)(CGparameter, double, double);
typedef void (*PFNCGGLSETPARAMETER2DVPROC)(CGparameter, const double *);
typedef void (*PFNCGGLSETPARAMETER2FPROC)(CGparameter, float, float);
typedef void (*PFNCGGLSETPARAMETER2FVPROC)(CGparameter, const float *);
typedef void (*PFNCGGLSETPARAMETER3DPROC)(CGparameter, double, double, double);
typedef void (*PFNCGGLSETPARAMETER3DVPROC)(CGparameter, const double *);
typedef void (*PFNCGGLSETPARAMETER3FPROC)(CGparameter, float, float, float);
typedef void (*PFNCGGLSETPARAMETER3FVPROC)(CGparameter, const float *);
typedef void (*PFNCGGLSETPARAMETER4DPROC)(CGparameter, double, double, double, double);
typedef void (*PFNCGGLSETPARAMETER4DVPROC)(CGparameter, const double *);
typedef void (*PFNCGGLSETPARAMETER4FPROC)(CGparameter, float, float, float, float);
typedef void (*PFNCGGLSETPARAMETER4FVPROC)(CGparameter, const float *);
typedef void (*PFNCGGLSETPARAMETERARRAY1DPROC)(CGparameter, long, long, const double *);
typedef void (*PFNCGGLSETPARAMETERARRAY1FPROC)(CGparameter, long, long, const float *);
typedef void (*PFNCGGLSETPARAMETERARRAY2DPROC)(CGparameter, long, long, const double *);
typedef void (*PFNCGGLSETPARAMETERARRAY2FPROC)(CGparameter, long, long, const float *);
typedef void (*PFNCGGLSETPARAMETERARRAY3DPROC)(CGparameter, long, long, const double *);
typedef void (*PFNCGGLSETPARAMETERARRAY3FPROC)(CGparameter, long, long, const float *);
typedef void (*PFNCGGLSETPARAMETERARRAY4DPROC)(CGparameter, long, long, const double *);
typedef void (*PFNCGGLSETPARAMETERARRAY4FPROC)(CGparameter, long, long, const float *);
typedef void (*PFNCGGLSETPARAMETERPOINTERPROC)(CGparameter, GLint, GLenum, GLsizei, const GLvoid *);
typedef void (*PFNCGGLSETSTATEMATRIXPARAMETERPROC)(CGparameter, CGGLenum, CGGLenum);
typedef void (*PFNCGGLSETTEXTUREPARAMETERPROC)(CGparameter, GLuint);
typedef void (*PFNCGGLSETUPSAMPLERPROC)(CGparameter, GLuint);
typedef void (*PFNCGGLUNBINDPROGRAMPROC)(CGprofile);
typedef void (*PFNCGGLUNLOADPROGRAMPROC)(CGprogram);

/* Declarations */

extern PFNCGGLBINDPROGRAMPROC cgGLBindProgram;
extern PFNCGGLCREATEBUFFERPROC cgGLCreateBuffer;
extern PFNCGGLCREATEBUFFERFROMOBJECTPROC cgGLCreateBufferFromObject;
extern PFNCGGLDETECTGLSLVERSIONPROC cgGLDetectGLSLVersion;
extern PFNCGGLDISABLECLIENTSTATEPROC cgGLDisableClientState;
extern PFNCGGLDISABLEPROFILEPROC cgGLDisableProfile;
extern PFNCGGLDISABLEPROGRAMPROFILESPROC cgGLDisableProgramProfiles;
extern PFNCGGLDISABLETEXTUREPARAMETERPROC cgGLDisableTextureParameter;
extern PFNCGGLENABLECLIENTSTATEPROC cgGLEnableClientState;
extern PFNCGGLENABLEPROFILEPROC cgGLEnableProfile;
extern PFNCGGLENABLEPROGRAMPROFILESPROC cgGLEnableProgramProfiles;
extern PFNCGGLENABLETEXTUREPARAMETERPROC cgGLEnableTextureParameter;
extern PFNCGGLGETBUFFEROBJECTPROC cgGLGetBufferObject;
extern PFNCGGLGETCONTEXTGLSLVERSIONPROC cgGLGetContextGLSLVersion;
extern PFNCGGLGETCONTEXTOPTIMALOPTIONSPROC cgGLGetContextOptimalOptions;
extern PFNCGGLGETGLSLVERSIONPROC cgGLGetGLSLVersion;
extern PFNCGGLGETGLSLVERSIONSTRINGPROC cgGLGetGLSLVersionString;
extern PFNCGGLGETLATESTPROFILEPROC cgGLGetLatestProfile;
extern PFNCGGLGETMANAGETEXTUREPARAMETERSPROC cgGLGetManageTextureParameters;
extern PFNCGGLGETMATRIXPARAMETERARRAYDCPROC cgGLGetMatrixParameterArraydc;
extern PFNCGGLGETMATRIXPARAMETERARRAYDRPROC cgGLGetMatrixParameterArraydr;
extern PFNCGGLGETMATRIXPARAMETERARRAYFCPROC cgGLGetMatrixParameterArrayfc;
extern PFNCGGLGETMATRIXPARAMETERARRAYFRPROC cgGLGetMatrixParameterArrayfr;
extern PFNCGGLGETMATRIXPARAMETERDCPROC cgGLGetMatrixParameterdc;
extern PFNCGGLGETMATRIXPARAMETERDRPROC cgGLGetMatrixParameterdr;
extern PFNCGGLGETMATRIXPARAMETERFCPROC cgGLGetMatrixParameterfc;
extern PFNCGGLGETMATRIXPARAMETERFRPROC cgGLGetMatrixParameterfr;
extern PFNCGGLGETOPTIMALOPTIONSPROC cgGLGetOptimalOptions;
extern PFNCGGLGETPARAMETER1DPROC cgGLGetParameter1d;
extern PFNCGGLGETPARAMETER1FPROC cgGLGetParameter1f;
extern PFNCGGLGETPARAMETER2DPROC cgGLGetParameter2d;
extern PFNCGGLGETPARAMETER2FPROC cgGLGetParameter2f;
extern PFNCGGLGETPARAMETER3DPROC cgGLGetParameter3d;
extern PFNCGGLGETPARAMETER3FPROC cgGLGetParameter3f;
extern PFNCGGLGETPARAMETER4DPROC cgGLGetParameter4d;
extern PFNCGGLGETPARAMETER4FPROC cgGLGetParameter4f;
extern PFNCGGLGETPARAMETERARRAY1DPROC cgGLGetParameterArray1d;
extern PFNCGGLGETPARAMETERARRAY1FPROC cgGLGetParameterArray1f;
extern PFNCGGLGETPARAMETERARRAY2DPROC cgGLGetParameterArray2d;
extern PFNCGGLGETPARAMETERARRAY2FPROC cgGLGetParameterArray2f;
extern PFNCGGLGETPARAMETERARRAY3DPROC cgGLGetParameterArray3d;
extern PFNCGGLGETPARAMETERARRAY3FPROC cgGLGetParameterArray3f;
extern PFNCGGLGETPARAMETERARRAY4DPROC cgGLGetParameterArray4d;
extern PFNCGGLGETPARAMETERARRAY4FPROC cgGLGetParameterArray4f;
extern PFNCGGLGETPROGRAMIDPROC cgGLGetProgramID;
extern PFNCGGLGETTEXTUREENUMPROC cgGLGetTextureEnum;
extern PFNCGGLGETTEXTUREPARAMETERPROC cgGLGetTextureParameter;
extern PFNCGGLISPROFILESUPPORTEDPROC cgGLIsProfileSupported;
extern PFNCGGLISPROGRAMLOADEDPROC cgGLIsProgramLoaded;
extern PFNCGGLLOADPROGRAMPROC cgGLLoadProgram;
extern PFNCGGLREGISTERSTATESPROC cgGLRegisterStates;
extern PFNCGGLSETCONTEXTGLSLVERSIONPROC cgGLSetContextGLSLVersion;
extern PFNCGGLSETCONTEXTOPTIMALOPTIONSPROC cgGLSetContextOptimalOptions;
extern PFNCGGLSETDEBUGMODEPROC cgGLSetDebugMode;
extern PFNCGGLSETMANAGETEXTUREPARAMETERSPROC cgGLSetManageTextureParameters;
extern PFNCGGLSETMATRIXPARAMETERARRAYDCPROC cgGLSetMatrixParameterArraydc;
extern PFNCGGLSETMATRIXPARAMETERARRAYDRPROC cgGLSetMatrixParameterArraydr;
extern PFNCGGLSETMATRIXPARAMETERARRAYFCPROC cgGLSetMatrixParameterArrayfc;
extern PFNCGGLSETMATRIXPARAMETERARRAYFRPROC cgGLSetMatrixParameterArrayfr;
extern PFNCGGLSETMATRIXPARAMETERDCPROC cgGLSetMatrixParameterdc;
extern PFNCGGLSETMATRIXPARAMETERDRPROC cgGLSetMatrixParameterdr;
extern PFNCGGLSETMATRIXPARAMETERFCPROC cgGLSetMatrixParameterfc;
extern PFNCGGLSETMATRIXPARAMETERFRPROC cgGLSetMatrixParameterfr;
extern PFNCGGLSETOPTIMALOPTIONSPROC cgGLSetOptimalOptions;
extern PFNCGGLSETPARAMETER1DPROC cgGLSetParameter1d;
extern PFNCGGLSETPARAMETER1DVPROC cgGLSetParameter1dv;
extern PFNCGGLSETPARAMETER1FPROC cgGLSetParameter1f;
extern PFNCGGLSETPARAMETER1FVPROC cgGLSetParameter1fv;
extern PFNCGGLSETPARAMETER2DPROC cgGLSetParameter2d;
extern PFNCGGLSETPARAMETER2DVPROC cgGLSetParameter2dv;
extern PFNCGGLSETPARAMETER2FPROC cgGLSetParameter2f;
extern PFNCGGLSETPARAMETER2FVPROC cgGLSetParameter2fv;
extern PFNCGGLSETPARAMETER3DPROC cgGLSetParameter3d;
extern PFNCGGLSETPARAMETER3DVPROC cgGLSetParameter3dv;
extern PFNCGGLSETPARAMETER3FPROC cgGLSetParameter3f;
extern PFNCGGLSETPARAMETER3FVPROC cgGLSetParameter3fv;
extern PFNCGGLSETPARAMETER4DPROC cgGLSetParameter4d;
extern PFNCGGLSETPARAMETER4DVPROC cgGLSetParameter4dv;
extern PFNCGGLSETPARAMETER4FPROC cgGLSetParameter4f;
extern PFNCGGLSETPARAMETER4FVPROC cgGLSetParameter4fv;
extern PFNCGGLSETPARAMETERARRAY1DPROC cgGLSetParameterArray1d;
extern PFNCGGLSETPARAMETERARRAY1FPROC cgGLSetParameterArray1f;
extern PFNCGGLSETPARAMETERARRAY2DPROC cgGLSetParameterArray2d;
extern PFNCGGLSETPARAMETERARRAY2FPROC cgGLSetParameterArray2f;
extern PFNCGGLSETPARAMETERARRAY3DPROC cgGLSetParameterArray3d;
extern PFNCGGLSETPARAMETERARRAY3FPROC cgGLSetParameterArray3f;
extern PFNCGGLSETPARAMETERARRAY4DPROC cgGLSetParameterArray4d;
extern PFNCGGLSETPARAMETERARRAY4FPROC cgGLSetParameterArray4f;
extern PFNCGGLSETPARAMETERPOINTERPROC cgGLSetParameterPointer;
extern PFNCGGLSETSTATEMATRIXPARAMETERPROC cgGLSetStateMatrixParameter;
extern PFNCGGLSETTEXTUREPARAMETERPROC cgGLSetTextureParameter;
extern PFNCGGLSETUPSAMPLERPROC cgGLSetupSampler;
extern PFNCGGLUNBINDPROGRAMPROC cgGLUnbindProgram;
extern PFNCGGLUNLOADPROGRAMPROC cgGLUnloadProgram;

#ifdef __cplusplus
}
#endif

#endif
