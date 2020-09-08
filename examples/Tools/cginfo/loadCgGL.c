#include "loadCgGL.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
# ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN 1
# endif
# ifndef NOGDI
#   define NOGDI 1
# endif
# include <windows.h>
#elif defined(__APPLE__)
# include <AvailabilityMacros.h>
# ifndef MAC_OS_X_VERSION_10_3
#   include <mach-o/dyld.h>
# else
#   include <dlfcn.h>
# endif
#else
# define __USE_GNU 1
# define _GNU_SOURCE
# include <dlfcn.h>
#endif

LcgGLHandle
lcgGLLoadLibrary(const char *filename)
{
#ifdef __APPLE__
  char *framework = NULL;

  /* 1. Try loading bare framework name */

# if defined(MAC_OS_X_VERSION_10_3)
  LcgGLHandle ret = (LcgGLHandle) dlopen(filename, RTLD_LAZY);
# else
  LcgGLHandle ret = (LcgGLHandle) NSAddImage(filename, NSADDIMAGE_OPTION_NONE);
# endif
  if (ret)
    return ret;

  /* 2. Try loading framework in Name.framework/Name */

  framework = (char *) malloc(strlen(filename)*2+12);
  sprintf(framework,"%s.framework/%s",filename,filename);

# if defined(MAC_OS_X_VERSION_10_3)
  ret = (LcgGLHandle) dlopen(framework, RTLD_LAZY);
# else
  ret = (LcgGLHandle) NSAddImage(framework, NSADDIMAGE_OPTION_NONE);
# endif

  free(framework);
  return ret;

#elif _WIN32
  return (LcgGLHandle) LoadLibraryA(filename);
#else
  return (LcgGLHandle) dlopen(filename, RTLD_LAZY);
#endif
}

int
lcgGLFreeLibrary(LcgGLHandle handle)
{
#ifdef _WIN32
  return FreeLibrary((HMODULE)handle) ? 1 : 0;
#elif defined(__APPLE__) && !defined(MAC_OS_X_VERSION_10_3)
  return 1;
#else
  return dlclose(handle) ? 0 : 1;
#endif
}

void *
lcgGLGetProcAddress(LcgGLHandle handle, const char *name)
{
#ifdef _WIN32
  return handle ? GetProcAddress((HMODULE)handle, name) : NULL;
#elif defined(__APPLE__) && !defined(MAC_OS_X_VERSION_10_3)
  return NSIsSymbolNameDefined(name) ? NSAddressOfSymbol(NSLookupAndBindSymbol(name)) : NULL;
#else
  return dlsym(handle, name);
#endif
}

const char *
lcgGLGetProcName(void **function)
{
  if (!function || !*function) return NULL;
  if (function==(void **) &cgGLBindProgram)                                             return "cgGLBindProgram";
  if (function==(void **) &cgGLCreateBuffer)                                            return "cgGLCreateBuffer";
  if (function==(void **) &cgGLCreateBufferFromObject)                                  return "cgGLCreateBufferFromObject";
  if (function==(void **) &cgGLDetectGLSLVersion)                                       return "cgGLDetectGLSLVersion";
  if (function==(void **) &cgGLDisableClientState)                                      return "cgGLDisableClientState";
  if (function==(void **) &cgGLDisableProfile)                                          return "cgGLDisableProfile";
  if (function==(void **) &cgGLDisableProgramProfiles)                                  return "cgGLDisableProgramProfiles";
  if (function==(void **) &cgGLDisableTextureParameter)                                 return "cgGLDisableTextureParameter";
  if (function==(void **) &cgGLEnableClientState)                                       return "cgGLEnableClientState";
  if (function==(void **) &cgGLEnableProfile)                                           return "cgGLEnableProfile";
  if (function==(void **) &cgGLEnableProgramProfiles)                                   return "cgGLEnableProgramProfiles";
  if (function==(void **) &cgGLEnableTextureParameter)                                  return "cgGLEnableTextureParameter";
  if (function==(void **) &cgGLGetBufferObject)                                         return "cgGLGetBufferObject";
  if (function==(void **) &cgGLGetContextGLSLVersion)                                   return "cgGLGetContextGLSLVersion";
  if (function==(void **) &cgGLGetContextOptimalOptions)                                return "cgGLGetContextOptimalOptions";
  if (function==(void **) &cgGLGetGLSLVersion)                                          return "cgGLGetGLSLVersion";
  if (function==(void **) &cgGLGetGLSLVersionString)                                    return "cgGLGetGLSLVersionString";
  if (function==(void **) &cgGLGetLatestProfile)                                        return "cgGLGetLatestProfile";
  if (function==(void **) &cgGLGetManageTextureParameters)                              return "cgGLGetManageTextureParameters";
  if (function==(void **) &cgGLGetMatrixParameterArraydc)                               return "cgGLGetMatrixParameterArraydc";
  if (function==(void **) &cgGLGetMatrixParameterArraydr)                               return "cgGLGetMatrixParameterArraydr";
  if (function==(void **) &cgGLGetMatrixParameterArrayfc)                               return "cgGLGetMatrixParameterArrayfc";
  if (function==(void **) &cgGLGetMatrixParameterArrayfr)                               return "cgGLGetMatrixParameterArrayfr";
  if (function==(void **) &cgGLGetMatrixParameterdc)                                    return "cgGLGetMatrixParameterdc";
  if (function==(void **) &cgGLGetMatrixParameterdr)                                    return "cgGLGetMatrixParameterdr";
  if (function==(void **) &cgGLGetMatrixParameterfc)                                    return "cgGLGetMatrixParameterfc";
  if (function==(void **) &cgGLGetMatrixParameterfr)                                    return "cgGLGetMatrixParameterfr";
  if (function==(void **) &cgGLGetOptimalOptions)                                       return "cgGLGetOptimalOptions";
  if (function==(void **) &cgGLGetParameter1d)                                          return "cgGLGetParameter1d";
  if (function==(void **) &cgGLGetParameter1f)                                          return "cgGLGetParameter1f";
  if (function==(void **) &cgGLGetParameter2d)                                          return "cgGLGetParameter2d";
  if (function==(void **) &cgGLGetParameter2f)                                          return "cgGLGetParameter2f";
  if (function==(void **) &cgGLGetParameter3d)                                          return "cgGLGetParameter3d";
  if (function==(void **) &cgGLGetParameter3f)                                          return "cgGLGetParameter3f";
  if (function==(void **) &cgGLGetParameter4d)                                          return "cgGLGetParameter4d";
  if (function==(void **) &cgGLGetParameter4f)                                          return "cgGLGetParameter4f";
  if (function==(void **) &cgGLGetParameterArray1d)                                     return "cgGLGetParameterArray1d";
  if (function==(void **) &cgGLGetParameterArray1f)                                     return "cgGLGetParameterArray1f";
  if (function==(void **) &cgGLGetParameterArray2d)                                     return "cgGLGetParameterArray2d";
  if (function==(void **) &cgGLGetParameterArray2f)                                     return "cgGLGetParameterArray2f";
  if (function==(void **) &cgGLGetParameterArray3d)                                     return "cgGLGetParameterArray3d";
  if (function==(void **) &cgGLGetParameterArray3f)                                     return "cgGLGetParameterArray3f";
  if (function==(void **) &cgGLGetParameterArray4d)                                     return "cgGLGetParameterArray4d";
  if (function==(void **) &cgGLGetParameterArray4f)                                     return "cgGLGetParameterArray4f";
  if (function==(void **) &cgGLGetProgramID)                                            return "cgGLGetProgramID";
  if (function==(void **) &cgGLGetTextureEnum)                                          return "cgGLGetTextureEnum";
  if (function==(void **) &cgGLGetTextureParameter)                                     return "cgGLGetTextureParameter";
  if (function==(void **) &cgGLIsProfileSupported)                                      return "cgGLIsProfileSupported";
  if (function==(void **) &cgGLIsProgramLoaded)                                         return "cgGLIsProgramLoaded";
  if (function==(void **) &cgGLLoadProgram)                                             return "cgGLLoadProgram";
  if (function==(void **) &cgGLRegisterStates)                                          return "cgGLRegisterStates";
  if (function==(void **) &cgGLSetContextGLSLVersion)                                   return "cgGLSetContextGLSLVersion";
  if (function==(void **) &cgGLSetContextOptimalOptions)                                return "cgGLSetContextOptimalOptions";
  if (function==(void **) &cgGLSetDebugMode)                                            return "cgGLSetDebugMode";
  if (function==(void **) &cgGLSetManageTextureParameters)                              return "cgGLSetManageTextureParameters";
  if (function==(void **) &cgGLSetMatrixParameterArraydc)                               return "cgGLSetMatrixParameterArraydc";
  if (function==(void **) &cgGLSetMatrixParameterArraydr)                               return "cgGLSetMatrixParameterArraydr";
  if (function==(void **) &cgGLSetMatrixParameterArrayfc)                               return "cgGLSetMatrixParameterArrayfc";
  if (function==(void **) &cgGLSetMatrixParameterArrayfr)                               return "cgGLSetMatrixParameterArrayfr";
  if (function==(void **) &cgGLSetMatrixParameterdc)                                    return "cgGLSetMatrixParameterdc";
  if (function==(void **) &cgGLSetMatrixParameterdr)                                    return "cgGLSetMatrixParameterdr";
  if (function==(void **) &cgGLSetMatrixParameterfc)                                    return "cgGLSetMatrixParameterfc";
  if (function==(void **) &cgGLSetMatrixParameterfr)                                    return "cgGLSetMatrixParameterfr";
  if (function==(void **) &cgGLSetOptimalOptions)                                       return "cgGLSetOptimalOptions";
  if (function==(void **) &cgGLSetParameter1d)                                          return "cgGLSetParameter1d";
  if (function==(void **) &cgGLSetParameter1dv)                                         return "cgGLSetParameter1dv";
  if (function==(void **) &cgGLSetParameter1f)                                          return "cgGLSetParameter1f";
  if (function==(void **) &cgGLSetParameter1fv)                                         return "cgGLSetParameter1fv";
  if (function==(void **) &cgGLSetParameter2d)                                          return "cgGLSetParameter2d";
  if (function==(void **) &cgGLSetParameter2dv)                                         return "cgGLSetParameter2dv";
  if (function==(void **) &cgGLSetParameter2f)                                          return "cgGLSetParameter2f";
  if (function==(void **) &cgGLSetParameter2fv)                                         return "cgGLSetParameter2fv";
  if (function==(void **) &cgGLSetParameter3d)                                          return "cgGLSetParameter3d";
  if (function==(void **) &cgGLSetParameter3dv)                                         return "cgGLSetParameter3dv";
  if (function==(void **) &cgGLSetParameter3f)                                          return "cgGLSetParameter3f";
  if (function==(void **) &cgGLSetParameter3fv)                                         return "cgGLSetParameter3fv";
  if (function==(void **) &cgGLSetParameter4d)                                          return "cgGLSetParameter4d";
  if (function==(void **) &cgGLSetParameter4dv)                                         return "cgGLSetParameter4dv";
  if (function==(void **) &cgGLSetParameter4f)                                          return "cgGLSetParameter4f";
  if (function==(void **) &cgGLSetParameter4fv)                                         return "cgGLSetParameter4fv";
  if (function==(void **) &cgGLSetParameterArray1d)                                     return "cgGLSetParameterArray1d";
  if (function==(void **) &cgGLSetParameterArray1f)                                     return "cgGLSetParameterArray1f";
  if (function==(void **) &cgGLSetParameterArray2d)                                     return "cgGLSetParameterArray2d";
  if (function==(void **) &cgGLSetParameterArray2f)                                     return "cgGLSetParameterArray2f";
  if (function==(void **) &cgGLSetParameterArray3d)                                     return "cgGLSetParameterArray3d";
  if (function==(void **) &cgGLSetParameterArray3f)                                     return "cgGLSetParameterArray3f";
  if (function==(void **) &cgGLSetParameterArray4d)                                     return "cgGLSetParameterArray4d";
  if (function==(void **) &cgGLSetParameterArray4f)                                     return "cgGLSetParameterArray4f";
  if (function==(void **) &cgGLSetParameterPointer)                                     return "cgGLSetParameterPointer";
  if (function==(void **) &cgGLSetStateMatrixParameter)                                 return "cgGLSetStateMatrixParameter";
  if (function==(void **) &cgGLSetTextureParameter)                                     return "cgGLSetTextureParameter";
  if (function==(void **) &cgGLSetupSampler)                                            return "cgGLSetupSampler";
  if (function==(void **) &cgGLUnbindProgram)                                           return "cgGLUnbindProgram";
  if (function==(void **) &cgGLUnloadProgram)                                           return "cgGLUnloadProgram";

  return NULL;
}

extern int
lcgGLHasVersion(void ***version)
{
  void ***i = version;

  if (!i)
    return 0;

  /* Check if any of the function pointers are NULL */

  for (; *i; ++i)
  {
    if (!**i)
      return 0;
  }

  return 1;
}

const char *
lcgGLGetModuleFileName(LcgGLHandle handle, void *function)
{
#ifdef _WIN32
  static char buffer[4096];
  if (GetModuleFileNameA((HMODULE)handle, buffer, 4095))
  {
    buffer[4095] = '\0';
    return buffer;
  }
#elif defined(__APPLE__) && !defined(MAC_OS_X_VERSION_10_3)
#else
  Dl_info info;
  if (dladdr(function,&info))
    return info.dli_fname;
#endif
  return NULL;
}

/* Entry Points */

PFNCGGLBINDPROGRAMPROC cgGLBindProgram = NULL;
PFNCGGLCREATEBUFFERPROC cgGLCreateBuffer = NULL;
PFNCGGLCREATEBUFFERFROMOBJECTPROC cgGLCreateBufferFromObject = NULL;
PFNCGGLDETECTGLSLVERSIONPROC cgGLDetectGLSLVersion = NULL;
PFNCGGLDISABLECLIENTSTATEPROC cgGLDisableClientState = NULL;
PFNCGGLDISABLEPROFILEPROC cgGLDisableProfile = NULL;
PFNCGGLDISABLEPROGRAMPROFILESPROC cgGLDisableProgramProfiles = NULL;
PFNCGGLDISABLETEXTUREPARAMETERPROC cgGLDisableTextureParameter = NULL;
PFNCGGLENABLECLIENTSTATEPROC cgGLEnableClientState = NULL;
PFNCGGLENABLEPROFILEPROC cgGLEnableProfile = NULL;
PFNCGGLENABLEPROGRAMPROFILESPROC cgGLEnableProgramProfiles = NULL;
PFNCGGLENABLETEXTUREPARAMETERPROC cgGLEnableTextureParameter = NULL;
PFNCGGLGETBUFFEROBJECTPROC cgGLGetBufferObject = NULL;
PFNCGGLGETCONTEXTGLSLVERSIONPROC cgGLGetContextGLSLVersion = NULL;
PFNCGGLGETCONTEXTOPTIMALOPTIONSPROC cgGLGetContextOptimalOptions = NULL;
PFNCGGLGETGLSLVERSIONPROC cgGLGetGLSLVersion = NULL;
PFNCGGLGETGLSLVERSIONSTRINGPROC cgGLGetGLSLVersionString = NULL;
PFNCGGLGETLATESTPROFILEPROC cgGLGetLatestProfile = NULL;
PFNCGGLGETMANAGETEXTUREPARAMETERSPROC cgGLGetManageTextureParameters = NULL;
PFNCGGLGETMATRIXPARAMETERARRAYDCPROC cgGLGetMatrixParameterArraydc = NULL;
PFNCGGLGETMATRIXPARAMETERARRAYDRPROC cgGLGetMatrixParameterArraydr = NULL;
PFNCGGLGETMATRIXPARAMETERARRAYFCPROC cgGLGetMatrixParameterArrayfc = NULL;
PFNCGGLGETMATRIXPARAMETERARRAYFRPROC cgGLGetMatrixParameterArrayfr = NULL;
PFNCGGLGETMATRIXPARAMETERDCPROC cgGLGetMatrixParameterdc = NULL;
PFNCGGLGETMATRIXPARAMETERDRPROC cgGLGetMatrixParameterdr = NULL;
PFNCGGLGETMATRIXPARAMETERFCPROC cgGLGetMatrixParameterfc = NULL;
PFNCGGLGETMATRIXPARAMETERFRPROC cgGLGetMatrixParameterfr = NULL;
PFNCGGLGETOPTIMALOPTIONSPROC cgGLGetOptimalOptions = NULL;
PFNCGGLGETPARAMETER1DPROC cgGLGetParameter1d = NULL;
PFNCGGLGETPARAMETER1FPROC cgGLGetParameter1f = NULL;
PFNCGGLGETPARAMETER2DPROC cgGLGetParameter2d = NULL;
PFNCGGLGETPARAMETER2FPROC cgGLGetParameter2f = NULL;
PFNCGGLGETPARAMETER3DPROC cgGLGetParameter3d = NULL;
PFNCGGLGETPARAMETER3FPROC cgGLGetParameter3f = NULL;
PFNCGGLGETPARAMETER4DPROC cgGLGetParameter4d = NULL;
PFNCGGLGETPARAMETER4FPROC cgGLGetParameter4f = NULL;
PFNCGGLGETPARAMETERARRAY1DPROC cgGLGetParameterArray1d = NULL;
PFNCGGLGETPARAMETERARRAY1FPROC cgGLGetParameterArray1f = NULL;
PFNCGGLGETPARAMETERARRAY2DPROC cgGLGetParameterArray2d = NULL;
PFNCGGLGETPARAMETERARRAY2FPROC cgGLGetParameterArray2f = NULL;
PFNCGGLGETPARAMETERARRAY3DPROC cgGLGetParameterArray3d = NULL;
PFNCGGLGETPARAMETERARRAY3FPROC cgGLGetParameterArray3f = NULL;
PFNCGGLGETPARAMETERARRAY4DPROC cgGLGetParameterArray4d = NULL;
PFNCGGLGETPARAMETERARRAY4FPROC cgGLGetParameterArray4f = NULL;
PFNCGGLGETPROGRAMIDPROC cgGLGetProgramID = NULL;
PFNCGGLGETTEXTUREENUMPROC cgGLGetTextureEnum = NULL;
PFNCGGLGETTEXTUREPARAMETERPROC cgGLGetTextureParameter = NULL;
PFNCGGLISPROFILESUPPORTEDPROC cgGLIsProfileSupported = NULL;
PFNCGGLISPROGRAMLOADEDPROC cgGLIsProgramLoaded = NULL;
PFNCGGLLOADPROGRAMPROC cgGLLoadProgram = NULL;
PFNCGGLREGISTERSTATESPROC cgGLRegisterStates = NULL;
PFNCGGLSETCONTEXTGLSLVERSIONPROC cgGLSetContextGLSLVersion = NULL;
PFNCGGLSETCONTEXTOPTIMALOPTIONSPROC cgGLSetContextOptimalOptions = NULL;
PFNCGGLSETDEBUGMODEPROC cgGLSetDebugMode = NULL;
PFNCGGLSETMANAGETEXTUREPARAMETERSPROC cgGLSetManageTextureParameters = NULL;
PFNCGGLSETMATRIXPARAMETERARRAYDCPROC cgGLSetMatrixParameterArraydc = NULL;
PFNCGGLSETMATRIXPARAMETERARRAYDRPROC cgGLSetMatrixParameterArraydr = NULL;
PFNCGGLSETMATRIXPARAMETERARRAYFCPROC cgGLSetMatrixParameterArrayfc = NULL;
PFNCGGLSETMATRIXPARAMETERARRAYFRPROC cgGLSetMatrixParameterArrayfr = NULL;
PFNCGGLSETMATRIXPARAMETERDCPROC cgGLSetMatrixParameterdc = NULL;
PFNCGGLSETMATRIXPARAMETERDRPROC cgGLSetMatrixParameterdr = NULL;
PFNCGGLSETMATRIXPARAMETERFCPROC cgGLSetMatrixParameterfc = NULL;
PFNCGGLSETMATRIXPARAMETERFRPROC cgGLSetMatrixParameterfr = NULL;
PFNCGGLSETOPTIMALOPTIONSPROC cgGLSetOptimalOptions = NULL;
PFNCGGLSETPARAMETER1DPROC cgGLSetParameter1d = NULL;
PFNCGGLSETPARAMETER1DVPROC cgGLSetParameter1dv = NULL;
PFNCGGLSETPARAMETER1FPROC cgGLSetParameter1f = NULL;
PFNCGGLSETPARAMETER1FVPROC cgGLSetParameter1fv = NULL;
PFNCGGLSETPARAMETER2DPROC cgGLSetParameter2d = NULL;
PFNCGGLSETPARAMETER2DVPROC cgGLSetParameter2dv = NULL;
PFNCGGLSETPARAMETER2FPROC cgGLSetParameter2f = NULL;
PFNCGGLSETPARAMETER2FVPROC cgGLSetParameter2fv = NULL;
PFNCGGLSETPARAMETER3DPROC cgGLSetParameter3d = NULL;
PFNCGGLSETPARAMETER3DVPROC cgGLSetParameter3dv = NULL;
PFNCGGLSETPARAMETER3FPROC cgGLSetParameter3f = NULL;
PFNCGGLSETPARAMETER3FVPROC cgGLSetParameter3fv = NULL;
PFNCGGLSETPARAMETER4DPROC cgGLSetParameter4d = NULL;
PFNCGGLSETPARAMETER4DVPROC cgGLSetParameter4dv = NULL;
PFNCGGLSETPARAMETER4FPROC cgGLSetParameter4f = NULL;
PFNCGGLSETPARAMETER4FVPROC cgGLSetParameter4fv = NULL;
PFNCGGLSETPARAMETERARRAY1DPROC cgGLSetParameterArray1d = NULL;
PFNCGGLSETPARAMETERARRAY1FPROC cgGLSetParameterArray1f = NULL;
PFNCGGLSETPARAMETERARRAY2DPROC cgGLSetParameterArray2d = NULL;
PFNCGGLSETPARAMETERARRAY2FPROC cgGLSetParameterArray2f = NULL;
PFNCGGLSETPARAMETERARRAY3DPROC cgGLSetParameterArray3d = NULL;
PFNCGGLSETPARAMETERARRAY3FPROC cgGLSetParameterArray3f = NULL;
PFNCGGLSETPARAMETERARRAY4DPROC cgGLSetParameterArray4d = NULL;
PFNCGGLSETPARAMETERARRAY4FPROC cgGLSetParameterArray4f = NULL;
PFNCGGLSETPARAMETERPOINTERPROC cgGLSetParameterPointer = NULL;
PFNCGGLSETSTATEMATRIXPARAMETERPROC cgGLSetStateMatrixParameter = NULL;
PFNCGGLSETTEXTUREPARAMETERPROC cgGLSetTextureParameter = NULL;
PFNCGGLSETUPSAMPLERPROC cgGLSetupSampler = NULL;
PFNCGGLUNBINDPROGRAMPROC cgGLUnbindProgram = NULL;
PFNCGGLUNLOADPROGRAMPROC cgGLUnloadProgram = NULL;

/* Implementation */

void ***
lcgGLVersion1_1_0000()
{
  static void **list[73] =
  {
    (void **) &cgGLBindProgram,
    (void **) &cgGLDisableClientState,
    (void **) &cgGLDisableProfile,
    (void **) &cgGLDisableTextureParameter,
    (void **) &cgGLEnableClientState,
    (void **) &cgGLEnableProfile,
    (void **) &cgGLEnableTextureParameter,
    (void **) &cgGLGetLatestProfile,
    (void **) &cgGLGetMatrixParameterArraydc,
    (void **) &cgGLGetMatrixParameterArraydr,
    (void **) &cgGLGetMatrixParameterArrayfc,
    (void **) &cgGLGetMatrixParameterArrayfr,
    (void **) &cgGLGetMatrixParameterdc,
    (void **) &cgGLGetMatrixParameterdr,
    (void **) &cgGLGetMatrixParameterfc,
    (void **) &cgGLGetMatrixParameterfr,
    (void **) &cgGLGetParameter1d,
    (void **) &cgGLGetParameter1f,
    (void **) &cgGLGetParameter2d,
    (void **) &cgGLGetParameter2f,
    (void **) &cgGLGetParameter3d,
    (void **) &cgGLGetParameter3f,
    (void **) &cgGLGetParameter4d,
    (void **) &cgGLGetParameter4f,
    (void **) &cgGLGetParameterArray1d,
    (void **) &cgGLGetParameterArray1f,
    (void **) &cgGLGetParameterArray2d,
    (void **) &cgGLGetParameterArray2f,
    (void **) &cgGLGetParameterArray3d,
    (void **) &cgGLGetParameterArray3f,
    (void **) &cgGLGetParameterArray4d,
    (void **) &cgGLGetParameterArray4f,
    (void **) &cgGLGetTextureEnum,
    (void **) &cgGLGetTextureParameter,
    (void **) &cgGLIsProfileSupported,
    (void **) &cgGLLoadProgram,
    (void **) &cgGLSetMatrixParameterArraydc,
    (void **) &cgGLSetMatrixParameterArraydr,
    (void **) &cgGLSetMatrixParameterArrayfc,
    (void **) &cgGLSetMatrixParameterArrayfr,
    (void **) &cgGLSetMatrixParameterdc,
    (void **) &cgGLSetMatrixParameterdr,
    (void **) &cgGLSetMatrixParameterfc,
    (void **) &cgGLSetMatrixParameterfr,
    (void **) &cgGLSetOptimalOptions,
    (void **) &cgGLSetParameter1d,
    (void **) &cgGLSetParameter1dv,
    (void **) &cgGLSetParameter1f,
    (void **) &cgGLSetParameter1fv,
    (void **) &cgGLSetParameter2d,
    (void **) &cgGLSetParameter2dv,
    (void **) &cgGLSetParameter2f,
    (void **) &cgGLSetParameter2fv,
    (void **) &cgGLSetParameter3d,
    (void **) &cgGLSetParameter3dv,
    (void **) &cgGLSetParameter3f,
    (void **) &cgGLSetParameter3fv,
    (void **) &cgGLSetParameter4d,
    (void **) &cgGLSetParameter4dv,
    (void **) &cgGLSetParameter4f,
    (void **) &cgGLSetParameter4fv,
    (void **) &cgGLSetParameterArray1d,
    (void **) &cgGLSetParameterArray1f,
    (void **) &cgGLSetParameterArray2d,
    (void **) &cgGLSetParameterArray2f,
    (void **) &cgGLSetParameterArray3d,
    (void **) &cgGLSetParameterArray3f,
    (void **) &cgGLSetParameterArray4d,
    (void **) &cgGLSetParameterArray4f,
    (void **) &cgGLSetParameterPointer,
    (void **) &cgGLSetStateMatrixParameter,
    (void **) &cgGLSetTextureParameter,
    NULL
  };
  return list;
}

void ***
lcgGLVersion1_2_0000()
{
  static void **list[6] =
  {
    (void **) &cgGLGetManageTextureParameters,
    (void **) &cgGLGetProgramID,
    (void **) &cgGLIsProgramLoaded,
    (void **) &cgGLSetManageTextureParameters,
    (void **) &cgGLUnbindProgram,
    NULL
  };
  return list;
}

void ***
lcgGLVersion1_4_0000()
{
  static void **list[3] =
  {
    (void **) &cgGLRegisterStates,
    (void **) &cgGLSetupSampler,
    NULL
  };
  return list;
}

void ***
lcgGLVersion1_5_0000()
{
  static void **list[4] =
  {
    (void **) &cgGLDisableProgramProfiles,
    (void **) &cgGLEnableProgramProfiles,
    (void **) &cgGLSetDebugMode,
    NULL
  };
  return list;
}

void ***
lcgGLVersion2_0_0000()
{
  static void **list[3] =
  {
    (void **) &cgGLCreateBuffer,
    (void **) &cgGLGetBufferObject,
    NULL
  };
  return list;
}

void ***
lcgGLVersion2_1_0000()
{
  static void **list[2] =
  {
    (void **) &cgGLUnloadProgram,
    NULL
  };
  return list;
}

void ***
lcgGLVersion2_2_0000()
{
  static void **list[2] =
  {
    (void **) &cgGLGetOptimalOptions,
    NULL
  };
  return list;
}

void ***
lcgGLVersion3_1_0000()
{
  static void **list[9] =
  {
    (void **) &cgGLCreateBufferFromObject,
    (void **) &cgGLDetectGLSLVersion,
    (void **) &cgGLGetContextGLSLVersion,
    (void **) &cgGLGetContextOptimalOptions,
    (void **) &cgGLGetGLSLVersion,
    (void **) &cgGLGetGLSLVersionString,
    (void **) &cgGLSetContextGLSLVersion,
    (void **) &cgGLSetContextOptimalOptions,
    NULL
  };
  return list;
}

LcgGLHandle lcgGLHandle = NULL;

int
lcgGLInit(const char *filename)
{
  lcgGLHandle = lcgGLLoadLibrary(filename);
  if (!lcgGLHandle)
    return 0;

  cgGLBindProgram = (PFNCGGLBINDPROGRAMPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLBindProgram");
  cgGLCreateBuffer = (PFNCGGLCREATEBUFFERPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLCreateBuffer");
  cgGLCreateBufferFromObject = (PFNCGGLCREATEBUFFERFROMOBJECTPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLCreateBufferFromObject");
  cgGLDetectGLSLVersion = (PFNCGGLDETECTGLSLVERSIONPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLDetectGLSLVersion");
  cgGLDisableClientState = (PFNCGGLDISABLECLIENTSTATEPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLDisableClientState");
  cgGLDisableProfile = (PFNCGGLDISABLEPROFILEPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLDisableProfile");
  cgGLDisableProgramProfiles = (PFNCGGLDISABLEPROGRAMPROFILESPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLDisableProgramProfiles");
  cgGLDisableTextureParameter = (PFNCGGLDISABLETEXTUREPARAMETERPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLDisableTextureParameter");
  cgGLEnableClientState = (PFNCGGLENABLECLIENTSTATEPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLEnableClientState");
  cgGLEnableProfile = (PFNCGGLENABLEPROFILEPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLEnableProfile");
  cgGLEnableProgramProfiles = (PFNCGGLENABLEPROGRAMPROFILESPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLEnableProgramProfiles");
  cgGLEnableTextureParameter = (PFNCGGLENABLETEXTUREPARAMETERPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLEnableTextureParameter");
  cgGLGetBufferObject = (PFNCGGLGETBUFFEROBJECTPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLGetBufferObject");
  cgGLGetContextGLSLVersion = (PFNCGGLGETCONTEXTGLSLVERSIONPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLGetContextGLSLVersion");
  cgGLGetContextOptimalOptions = (PFNCGGLGETCONTEXTOPTIMALOPTIONSPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLGetContextOptimalOptions");
  cgGLGetGLSLVersion = (PFNCGGLGETGLSLVERSIONPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLGetGLSLVersion");
  cgGLGetGLSLVersionString = (PFNCGGLGETGLSLVERSIONSTRINGPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLGetGLSLVersionString");
  cgGLGetLatestProfile = (PFNCGGLGETLATESTPROFILEPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLGetLatestProfile");
  cgGLGetManageTextureParameters = (PFNCGGLGETMANAGETEXTUREPARAMETERSPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLGetManageTextureParameters");
  cgGLGetMatrixParameterArraydc = (PFNCGGLGETMATRIXPARAMETERARRAYDCPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLGetMatrixParameterArraydc");
  cgGLGetMatrixParameterArraydr = (PFNCGGLGETMATRIXPARAMETERARRAYDRPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLGetMatrixParameterArraydr");
  cgGLGetMatrixParameterArrayfc = (PFNCGGLGETMATRIXPARAMETERARRAYFCPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLGetMatrixParameterArrayfc");
  cgGLGetMatrixParameterArrayfr = (PFNCGGLGETMATRIXPARAMETERARRAYFRPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLGetMatrixParameterArrayfr");
  cgGLGetMatrixParameterdc = (PFNCGGLGETMATRIXPARAMETERDCPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLGetMatrixParameterdc");
  cgGLGetMatrixParameterdr = (PFNCGGLGETMATRIXPARAMETERDRPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLGetMatrixParameterdr");
  cgGLGetMatrixParameterfc = (PFNCGGLGETMATRIXPARAMETERFCPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLGetMatrixParameterfc");
  cgGLGetMatrixParameterfr = (PFNCGGLGETMATRIXPARAMETERFRPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLGetMatrixParameterfr");
  cgGLGetOptimalOptions = (PFNCGGLGETOPTIMALOPTIONSPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLGetOptimalOptions");
  cgGLGetParameter1d = (PFNCGGLGETPARAMETER1DPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLGetParameter1d");
  cgGLGetParameter1f = (PFNCGGLGETPARAMETER1FPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLGetParameter1f");
  cgGLGetParameter2d = (PFNCGGLGETPARAMETER2DPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLGetParameter2d");
  cgGLGetParameter2f = (PFNCGGLGETPARAMETER2FPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLGetParameter2f");
  cgGLGetParameter3d = (PFNCGGLGETPARAMETER3DPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLGetParameter3d");
  cgGLGetParameter3f = (PFNCGGLGETPARAMETER3FPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLGetParameter3f");
  cgGLGetParameter4d = (PFNCGGLGETPARAMETER4DPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLGetParameter4d");
  cgGLGetParameter4f = (PFNCGGLGETPARAMETER4FPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLGetParameter4f");
  cgGLGetParameterArray1d = (PFNCGGLGETPARAMETERARRAY1DPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLGetParameterArray1d");
  cgGLGetParameterArray1f = (PFNCGGLGETPARAMETERARRAY1FPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLGetParameterArray1f");
  cgGLGetParameterArray2d = (PFNCGGLGETPARAMETERARRAY2DPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLGetParameterArray2d");
  cgGLGetParameterArray2f = (PFNCGGLGETPARAMETERARRAY2FPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLGetParameterArray2f");
  cgGLGetParameterArray3d = (PFNCGGLGETPARAMETERARRAY3DPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLGetParameterArray3d");
  cgGLGetParameterArray3f = (PFNCGGLGETPARAMETERARRAY3FPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLGetParameterArray3f");
  cgGLGetParameterArray4d = (PFNCGGLGETPARAMETERARRAY4DPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLGetParameterArray4d");
  cgGLGetParameterArray4f = (PFNCGGLGETPARAMETERARRAY4FPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLGetParameterArray4f");
  cgGLGetProgramID = (PFNCGGLGETPROGRAMIDPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLGetProgramID");
  cgGLGetTextureEnum = (PFNCGGLGETTEXTUREENUMPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLGetTextureEnum");
  cgGLGetTextureParameter = (PFNCGGLGETTEXTUREPARAMETERPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLGetTextureParameter");
  cgGLIsProfileSupported = (PFNCGGLISPROFILESUPPORTEDPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLIsProfileSupported");
  cgGLIsProgramLoaded = (PFNCGGLISPROGRAMLOADEDPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLIsProgramLoaded");
  cgGLLoadProgram = (PFNCGGLLOADPROGRAMPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLLoadProgram");
  cgGLRegisterStates = (PFNCGGLREGISTERSTATESPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLRegisterStates");
  cgGLSetContextGLSLVersion = (PFNCGGLSETCONTEXTGLSLVERSIONPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetContextGLSLVersion");
  cgGLSetContextOptimalOptions = (PFNCGGLSETCONTEXTOPTIMALOPTIONSPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetContextOptimalOptions");
  cgGLSetDebugMode = (PFNCGGLSETDEBUGMODEPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetDebugMode");
  cgGLSetManageTextureParameters = (PFNCGGLSETMANAGETEXTUREPARAMETERSPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetManageTextureParameters");
  cgGLSetMatrixParameterArraydc = (PFNCGGLSETMATRIXPARAMETERARRAYDCPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetMatrixParameterArraydc");
  cgGLSetMatrixParameterArraydr = (PFNCGGLSETMATRIXPARAMETERARRAYDRPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetMatrixParameterArraydr");
  cgGLSetMatrixParameterArrayfc = (PFNCGGLSETMATRIXPARAMETERARRAYFCPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetMatrixParameterArrayfc");
  cgGLSetMatrixParameterArrayfr = (PFNCGGLSETMATRIXPARAMETERARRAYFRPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetMatrixParameterArrayfr");
  cgGLSetMatrixParameterdc = (PFNCGGLSETMATRIXPARAMETERDCPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetMatrixParameterdc");
  cgGLSetMatrixParameterdr = (PFNCGGLSETMATRIXPARAMETERDRPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetMatrixParameterdr");
  cgGLSetMatrixParameterfc = (PFNCGGLSETMATRIXPARAMETERFCPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetMatrixParameterfc");
  cgGLSetMatrixParameterfr = (PFNCGGLSETMATRIXPARAMETERFRPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetMatrixParameterfr");
  cgGLSetOptimalOptions = (PFNCGGLSETOPTIMALOPTIONSPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetOptimalOptions");
  cgGLSetParameter1d = (PFNCGGLSETPARAMETER1DPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetParameter1d");
  cgGLSetParameter1dv = (PFNCGGLSETPARAMETER1DVPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetParameter1dv");
  cgGLSetParameter1f = (PFNCGGLSETPARAMETER1FPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetParameter1f");
  cgGLSetParameter1fv = (PFNCGGLSETPARAMETER1FVPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetParameter1fv");
  cgGLSetParameter2d = (PFNCGGLSETPARAMETER2DPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetParameter2d");
  cgGLSetParameter2dv = (PFNCGGLSETPARAMETER2DVPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetParameter2dv");
  cgGLSetParameter2f = (PFNCGGLSETPARAMETER2FPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetParameter2f");
  cgGLSetParameter2fv = (PFNCGGLSETPARAMETER2FVPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetParameter2fv");
  cgGLSetParameter3d = (PFNCGGLSETPARAMETER3DPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetParameter3d");
  cgGLSetParameter3dv = (PFNCGGLSETPARAMETER3DVPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetParameter3dv");
  cgGLSetParameter3f = (PFNCGGLSETPARAMETER3FPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetParameter3f");
  cgGLSetParameter3fv = (PFNCGGLSETPARAMETER3FVPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetParameter3fv");
  cgGLSetParameter4d = (PFNCGGLSETPARAMETER4DPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetParameter4d");
  cgGLSetParameter4dv = (PFNCGGLSETPARAMETER4DVPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetParameter4dv");
  cgGLSetParameter4f = (PFNCGGLSETPARAMETER4FPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetParameter4f");
  cgGLSetParameter4fv = (PFNCGGLSETPARAMETER4FVPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetParameter4fv");
  cgGLSetParameterArray1d = (PFNCGGLSETPARAMETERARRAY1DPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetParameterArray1d");
  cgGLSetParameterArray1f = (PFNCGGLSETPARAMETERARRAY1FPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetParameterArray1f");
  cgGLSetParameterArray2d = (PFNCGGLSETPARAMETERARRAY2DPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetParameterArray2d");
  cgGLSetParameterArray2f = (PFNCGGLSETPARAMETERARRAY2FPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetParameterArray2f");
  cgGLSetParameterArray3d = (PFNCGGLSETPARAMETERARRAY3DPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetParameterArray3d");
  cgGLSetParameterArray3f = (PFNCGGLSETPARAMETERARRAY3FPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetParameterArray3f");
  cgGLSetParameterArray4d = (PFNCGGLSETPARAMETERARRAY4DPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetParameterArray4d");
  cgGLSetParameterArray4f = (PFNCGGLSETPARAMETERARRAY4FPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetParameterArray4f");
  cgGLSetParameterPointer = (PFNCGGLSETPARAMETERPOINTERPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetParameterPointer");
  cgGLSetStateMatrixParameter = (PFNCGGLSETSTATEMATRIXPARAMETERPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetStateMatrixParameter");
  cgGLSetTextureParameter = (PFNCGGLSETTEXTUREPARAMETERPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetTextureParameter");
  cgGLSetupSampler = (PFNCGGLSETUPSAMPLERPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLSetupSampler");
  cgGLUnbindProgram = (PFNCGGLUNBINDPROGRAMPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLUnbindProgram");
  cgGLUnloadProgram = (PFNCGGLUNLOADPROGRAMPROC) lcgGLGetProcAddress(lcgGLHandle, "cgGLUnloadProgram");

  return 1;
}

void
lcgGLList(const char *prefix, FILE *out)
{
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLBindProgram", cgGLBindProgram ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLCreateBuffer", cgGLCreateBuffer ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLCreateBufferFromObject", cgGLCreateBufferFromObject ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLDetectGLSLVersion", cgGLDetectGLSLVersion ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLDisableClientState", cgGLDisableClientState ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLDisableProfile", cgGLDisableProfile ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLDisableProgramProfiles", cgGLDisableProgramProfiles ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLDisableTextureParameter", cgGLDisableTextureParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLEnableClientState", cgGLEnableClientState ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLEnableProfile", cgGLEnableProfile ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLEnableProgramProfiles", cgGLEnableProgramProfiles ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLEnableTextureParameter", cgGLEnableTextureParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLGetBufferObject", cgGLGetBufferObject ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLGetContextGLSLVersion", cgGLGetContextGLSLVersion ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLGetContextOptimalOptions", cgGLGetContextOptimalOptions ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLGetGLSLVersion", cgGLGetGLSLVersion ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLGetGLSLVersionString", cgGLGetGLSLVersionString ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLGetLatestProfile", cgGLGetLatestProfile ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLGetManageTextureParameters", cgGLGetManageTextureParameters ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLGetMatrixParameterArraydc", cgGLGetMatrixParameterArraydc ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLGetMatrixParameterArraydr", cgGLGetMatrixParameterArraydr ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLGetMatrixParameterArrayfc", cgGLGetMatrixParameterArrayfc ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLGetMatrixParameterArrayfr", cgGLGetMatrixParameterArrayfr ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLGetMatrixParameterdc", cgGLGetMatrixParameterdc ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLGetMatrixParameterdr", cgGLGetMatrixParameterdr ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLGetMatrixParameterfc", cgGLGetMatrixParameterfc ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLGetMatrixParameterfr", cgGLGetMatrixParameterfr ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLGetOptimalOptions", cgGLGetOptimalOptions ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLGetParameter1d", cgGLGetParameter1d ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLGetParameter1f", cgGLGetParameter1f ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLGetParameter2d", cgGLGetParameter2d ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLGetParameter2f", cgGLGetParameter2f ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLGetParameter3d", cgGLGetParameter3d ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLGetParameter3f", cgGLGetParameter3f ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLGetParameter4d", cgGLGetParameter4d ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLGetParameter4f", cgGLGetParameter4f ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLGetParameterArray1d", cgGLGetParameterArray1d ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLGetParameterArray1f", cgGLGetParameterArray1f ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLGetParameterArray2d", cgGLGetParameterArray2d ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLGetParameterArray2f", cgGLGetParameterArray2f ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLGetParameterArray3d", cgGLGetParameterArray3d ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLGetParameterArray3f", cgGLGetParameterArray3f ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLGetParameterArray4d", cgGLGetParameterArray4d ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLGetParameterArray4f", cgGLGetParameterArray4f ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLGetProgramID", cgGLGetProgramID ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLGetTextureEnum", cgGLGetTextureEnum ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLGetTextureParameter", cgGLGetTextureParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLIsProfileSupported", cgGLIsProfileSupported ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLIsProgramLoaded", cgGLIsProgramLoaded ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLLoadProgram", cgGLLoadProgram ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLRegisterStates", cgGLRegisterStates ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetContextGLSLVersion", cgGLSetContextGLSLVersion ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetContextOptimalOptions", cgGLSetContextOptimalOptions ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetDebugMode", cgGLSetDebugMode ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetManageTextureParameters", cgGLSetManageTextureParameters ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetMatrixParameterArraydc", cgGLSetMatrixParameterArraydc ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetMatrixParameterArraydr", cgGLSetMatrixParameterArraydr ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetMatrixParameterArrayfc", cgGLSetMatrixParameterArrayfc ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetMatrixParameterArrayfr", cgGLSetMatrixParameterArrayfr ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetMatrixParameterdc", cgGLSetMatrixParameterdc ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetMatrixParameterdr", cgGLSetMatrixParameterdr ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetMatrixParameterfc", cgGLSetMatrixParameterfc ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetMatrixParameterfr", cgGLSetMatrixParameterfr ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetOptimalOptions", cgGLSetOptimalOptions ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetParameter1d", cgGLSetParameter1d ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetParameter1dv", cgGLSetParameter1dv ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetParameter1f", cgGLSetParameter1f ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetParameter1fv", cgGLSetParameter1fv ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetParameter2d", cgGLSetParameter2d ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetParameter2dv", cgGLSetParameter2dv ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetParameter2f", cgGLSetParameter2f ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetParameter2fv", cgGLSetParameter2fv ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetParameter3d", cgGLSetParameter3d ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetParameter3dv", cgGLSetParameter3dv ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetParameter3f", cgGLSetParameter3f ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetParameter3fv", cgGLSetParameter3fv ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetParameter4d", cgGLSetParameter4d ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetParameter4dv", cgGLSetParameter4dv ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetParameter4f", cgGLSetParameter4f ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetParameter4fv", cgGLSetParameter4fv ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetParameterArray1d", cgGLSetParameterArray1d ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetParameterArray1f", cgGLSetParameterArray1f ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetParameterArray2d", cgGLSetParameterArray2d ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetParameterArray2f", cgGLSetParameterArray2f ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetParameterArray3d", cgGLSetParameterArray3d ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetParameterArray3f", cgGLSetParameterArray3f ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetParameterArray4d", cgGLSetParameterArray4d ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetParameterArray4f", cgGLSetParameterArray4f ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetParameterPointer", cgGLSetParameterPointer ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetStateMatrixParameter", cgGLSetStateMatrixParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetTextureParameter", cgGLSetTextureParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLSetupSampler", cgGLSetupSampler ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLUnbindProgram", cgGLUnbindProgram ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgGLUnloadProgram", cgGLUnloadProgram ? "found" : "missing");
}

void
lcgGLDestroy(void)
{
  if (lcgGLHandle)
  {
    lcgGLFreeLibrary(lcgGLHandle);
    lcgGLHandle = NULL;
  }
}
