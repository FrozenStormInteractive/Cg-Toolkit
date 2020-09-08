#if defined(_WIN32) && !defined(__CYGWIN__)

#include "loadCgD3D9.h"

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

LcgD3D9Handle
lcgD3D9LoadLibrary(const char *filename)
{
#ifdef __APPLE__
  char *framework = NULL;

  /* 1. Try loading bare framework name */

# if defined(MAC_OS_X_VERSION_10_3)
  LcgD3D9Handle ret = (LcgD3D9Handle) dlopen(filename, RTLD_LAZY);
# else
  LcgD3D9Handle ret = (LcgD3D9Handle) NSAddImage(filename, NSADDIMAGE_OPTION_NONE);
# endif
  if (ret)
    return ret;

  /* 2. Try loading framework in Name.framework/Name */

  framework = (char *) malloc(strlen(filename)*2+12);
  sprintf(framework,"%s.framework/%s",filename,filename);

# if defined(MAC_OS_X_VERSION_10_3)
  ret = (LcgD3D9Handle) dlopen(framework, RTLD_LAZY);
# else
  ret = (LcgD3D9Handle) NSAddImage(framework, NSADDIMAGE_OPTION_NONE);
# endif

  free(framework);
  return ret;

#elif _WIN32
  return (LcgD3D9Handle) LoadLibraryA(filename);
#else
  return (LcgD3D9Handle) dlopen(filename, RTLD_LAZY);
#endif
}

int
lcgD3D9FreeLibrary(LcgD3D9Handle handle)
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
lcgD3D9GetProcAddress(LcgD3D9Handle handle, const char *name)
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
lcgD3D9GetProcName(void **function)
{
  if (!function || !*function) return NULL;
  if (function==(void **) &cgD3D9BindProgram)                                           return "cgD3D9BindProgram";
  if (function==(void **) &cgD3D9EnableDebugTracing)                                    return "cgD3D9EnableDebugTracing";
  if (function==(void **) &cgD3D9EnableParameterShadowing)                              return "cgD3D9EnableParameterShadowing";
  if (function==(void **) &cgD3D9GetDevice)                                             return "cgD3D9GetDevice";
  if (function==(void **) &cgD3D9GetLastError)                                          return "cgD3D9GetLastError";
  if (function==(void **) &cgD3D9GetLatestPixelProfile)                                 return "cgD3D9GetLatestPixelProfile";
  if (function==(void **) &cgD3D9GetLatestVertexProfile)                                return "cgD3D9GetLatestVertexProfile";
  if (function==(void **) &cgD3D9GetManageTextureParameters)                            return "cgD3D9GetManageTextureParameters";
  if (function==(void **) &cgD3D9GetOptimalOptions)                                     return "cgD3D9GetOptimalOptions";
  if (function==(void **) &cgD3D9GetTextureParameter)                                   return "cgD3D9GetTextureParameter";
  if (function==(void **) &cgD3D9GetVertexDeclaration)                                  return "cgD3D9GetVertexDeclaration";
  if (function==(void **) &cgD3D9IsParameterShadowingEnabled)                           return "cgD3D9IsParameterShadowingEnabled";
  if (function==(void **) &cgD3D9IsProfileSupported)                                    return "cgD3D9IsProfileSupported";
  if (function==(void **) &cgD3D9IsProgramLoaded)                                       return "cgD3D9IsProgramLoaded";
  if (function==(void **) &cgD3D9LoadProgram)                                           return "cgD3D9LoadProgram";
  if (function==(void **) &cgD3D9RegisterStates)                                        return "cgD3D9RegisterStates";
  if (function==(void **) &cgD3D9ResourceToDeclUsage)                                   return "cgD3D9ResourceToDeclUsage";
  if (function==(void **) &cgD3D9SetDevice)                                             return "cgD3D9SetDevice";
  if (function==(void **) &cgD3D9SetManageTextureParameters)                            return "cgD3D9SetManageTextureParameters";
  if (function==(void **) &cgD3D9SetSamplerState)                                       return "cgD3D9SetSamplerState";
  if (function==(void **) &cgD3D9SetTexture)                                            return "cgD3D9SetTexture";
  if (function==(void **) &cgD3D9SetTextureParameter)                                   return "cgD3D9SetTextureParameter";
  if (function==(void **) &cgD3D9SetTextureWrapMode)                                    return "cgD3D9SetTextureWrapMode";
  if (function==(void **) &cgD3D9SetUniform)                                            return "cgD3D9SetUniform";
  if (function==(void **) &cgD3D9SetUniformArray)                                       return "cgD3D9SetUniformArray";
  if (function==(void **) &cgD3D9SetUniformMatrix)                                      return "cgD3D9SetUniformMatrix";
  if (function==(void **) &cgD3D9SetUniformMatrixArray)                                 return "cgD3D9SetUniformMatrixArray";
  if (function==(void **) &cgD3D9TranslateCGerror)                                      return "cgD3D9TranslateCGerror";
  if (function==(void **) &cgD3D9TranslateHRESULT)                                      return "cgD3D9TranslateHRESULT";
  if (function==(void **) &cgD3D9TypeToSize)                                            return "cgD3D9TypeToSize";
  if (function==(void **) &cgD3D9UnbindProgram)                                         return "cgD3D9UnbindProgram";
  if (function==(void **) &cgD3D9UnloadAllPrograms)                                     return "cgD3D9UnloadAllPrograms";
  if (function==(void **) &cgD3D9UnloadProgram)                                         return "cgD3D9UnloadProgram";
  if (function==(void **) &cgD3D9ValidateVertexDeclaration)                             return "cgD3D9ValidateVertexDeclaration";

  return NULL;
}

extern int
lcgD3D9HasVersion(void ***version)
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
lcgD3D9GetModuleFileName(LcgD3D9Handle handle, void *function)
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

PFNCGD3D9BINDPROGRAMPROC cgD3D9BindProgram = NULL;
PFNCGD3D9ENABLEDEBUGTRACINGPROC cgD3D9EnableDebugTracing = NULL;
PFNCGD3D9ENABLEPARAMETERSHADOWINGPROC cgD3D9EnableParameterShadowing = NULL;
PFNCGD3D9GETDEVICEPROC cgD3D9GetDevice = NULL;
PFNCGD3D9GETLASTERRORPROC cgD3D9GetLastError = NULL;
PFNCGD3D9GETLATESTPIXELPROFILEPROC cgD3D9GetLatestPixelProfile = NULL;
PFNCGD3D9GETLATESTVERTEXPROFILEPROC cgD3D9GetLatestVertexProfile = NULL;
PFNCGD3D9GETMANAGETEXTUREPARAMETERSPROC cgD3D9GetManageTextureParameters = NULL;
PFNCGD3D9GETOPTIMALOPTIONSPROC cgD3D9GetOptimalOptions = NULL;
PFNCGD3D9GETTEXTUREPARAMETERPROC cgD3D9GetTextureParameter = NULL;
PFNCGD3D9GETVERTEXDECLARATIONPROC cgD3D9GetVertexDeclaration = NULL;
PFNCGD3D9ISPARAMETERSHADOWINGENABLEDPROC cgD3D9IsParameterShadowingEnabled = NULL;
PFNCGD3D9ISPROFILESUPPORTEDPROC cgD3D9IsProfileSupported = NULL;
PFNCGD3D9ISPROGRAMLOADEDPROC cgD3D9IsProgramLoaded = NULL;
PFNCGD3D9LOADPROGRAMPROC cgD3D9LoadProgram = NULL;
PFNCGD3D9REGISTERSTATESPROC cgD3D9RegisterStates = NULL;
PFNCGD3D9RESOURCETODECLUSAGEPROC cgD3D9ResourceToDeclUsage = NULL;
PFNCGD3D9SETDEVICEPROC cgD3D9SetDevice = NULL;
PFNCGD3D9SETMANAGETEXTUREPARAMETERSPROC cgD3D9SetManageTextureParameters = NULL;
PFNCGD3D9SETSAMPLERSTATEPROC cgD3D9SetSamplerState = NULL;
PFNCGD3D9SETTEXTUREPROC cgD3D9SetTexture = NULL;
PFNCGD3D9SETTEXTUREPARAMETERPROC cgD3D9SetTextureParameter = NULL;
PFNCGD3D9SETTEXTUREWRAPMODEPROC cgD3D9SetTextureWrapMode = NULL;
PFNCGD3D9SETUNIFORMPROC cgD3D9SetUniform = NULL;
PFNCGD3D9SETUNIFORMARRAYPROC cgD3D9SetUniformArray = NULL;
PFNCGD3D9SETUNIFORMMATRIXPROC cgD3D9SetUniformMatrix = NULL;
PFNCGD3D9SETUNIFORMMATRIXARRAYPROC cgD3D9SetUniformMatrixArray = NULL;
PFNCGD3D9TRANSLATECGERRORPROC cgD3D9TranslateCGerror = NULL;
PFNCGD3D9TRANSLATEHRESULTPROC cgD3D9TranslateHRESULT = NULL;
PFNCGD3D9TYPETOSIZEPROC cgD3D9TypeToSize = NULL;
PFNCGD3D9UNBINDPROGRAMPROC cgD3D9UnbindProgram = NULL;
PFNCGD3D9UNLOADALLPROGRAMSPROC cgD3D9UnloadAllPrograms = NULL;
PFNCGD3D9UNLOADPROGRAMPROC cgD3D9UnloadProgram = NULL;
PFNCGD3D9VALIDATEVERTEXDECLARATIONPROC cgD3D9ValidateVertexDeclaration = NULL;

/* Implementation */

void ***
lcgD3D9Version1_4_0000()
{
  static void **list[27] =
  {
    (void **) &cgD3D9BindProgram,
    (void **) &cgD3D9EnableDebugTracing,
    (void **) &cgD3D9EnableParameterShadowing,
    (void **) &cgD3D9GetDevice,
    (void **) &cgD3D9GetLastError,
    (void **) &cgD3D9GetLatestPixelProfile,
    (void **) &cgD3D9GetLatestVertexProfile,
    (void **) &cgD3D9GetOptimalOptions,
    (void **) &cgD3D9GetVertexDeclaration,
    (void **) &cgD3D9IsParameterShadowingEnabled,
    (void **) &cgD3D9IsProgramLoaded,
    (void **) &cgD3D9LoadProgram,
    (void **) &cgD3D9ResourceToDeclUsage,
    (void **) &cgD3D9SetDevice,
    (void **) &cgD3D9SetSamplerState,
    (void **) &cgD3D9SetTexture,
    (void **) &cgD3D9SetTextureWrapMode,
    (void **) &cgD3D9SetUniform,
    (void **) &cgD3D9SetUniformArray,
    (void **) &cgD3D9SetUniformMatrix,
    (void **) &cgD3D9SetUniformMatrixArray,
    (void **) &cgD3D9TranslateCGerror,
    (void **) &cgD3D9TranslateHRESULT,
    (void **) &cgD3D9TypeToSize,
    (void **) &cgD3D9UnloadProgram,
    (void **) &cgD3D9ValidateVertexDeclaration,
    NULL
  };
  return list;
}

void ***
lcgD3D9Version1_5_0001()
{
  static void **list[8] =
  {
    (void **) &cgD3D9GetManageTextureParameters,
    (void **) &cgD3D9GetTextureParameter,
    (void **) &cgD3D9IsProfileSupported,
    (void **) &cgD3D9RegisterStates,
    (void **) &cgD3D9SetManageTextureParameters,
    (void **) &cgD3D9SetTextureParameter,
    (void **) &cgD3D9UnloadAllPrograms,
    NULL
  };
  return list;
}

void ***
lcgD3D9Version3_0_0000()
{
  static void **list[2] =
  {
    (void **) &cgD3D9UnbindProgram,
    NULL
  };
  return list;
}

LcgD3D9Handle lcgD3D9Handle = NULL;

int
lcgD3D9Init(const char *filename)
{
  lcgD3D9Handle = lcgD3D9LoadLibrary(filename);
  if (!lcgD3D9Handle)
    return 0;

  cgD3D9BindProgram = (PFNCGD3D9BINDPROGRAMPROC) lcgD3D9GetProcAddress(lcgD3D9Handle, "cgD3D9BindProgram");
  cgD3D9EnableDebugTracing = (PFNCGD3D9ENABLEDEBUGTRACINGPROC) lcgD3D9GetProcAddress(lcgD3D9Handle, "cgD3D9EnableDebugTracing");
  cgD3D9EnableParameterShadowing = (PFNCGD3D9ENABLEPARAMETERSHADOWINGPROC) lcgD3D9GetProcAddress(lcgD3D9Handle, "cgD3D9EnableParameterShadowing");
  cgD3D9GetDevice = (PFNCGD3D9GETDEVICEPROC) lcgD3D9GetProcAddress(lcgD3D9Handle, "cgD3D9GetDevice");
  cgD3D9GetLastError = (PFNCGD3D9GETLASTERRORPROC) lcgD3D9GetProcAddress(lcgD3D9Handle, "cgD3D9GetLastError");
  cgD3D9GetLatestPixelProfile = (PFNCGD3D9GETLATESTPIXELPROFILEPROC) lcgD3D9GetProcAddress(lcgD3D9Handle, "cgD3D9GetLatestPixelProfile");
  cgD3D9GetLatestVertexProfile = (PFNCGD3D9GETLATESTVERTEXPROFILEPROC) lcgD3D9GetProcAddress(lcgD3D9Handle, "cgD3D9GetLatestVertexProfile");
  cgD3D9GetManageTextureParameters = (PFNCGD3D9GETMANAGETEXTUREPARAMETERSPROC) lcgD3D9GetProcAddress(lcgD3D9Handle, "cgD3D9GetManageTextureParameters");
  cgD3D9GetOptimalOptions = (PFNCGD3D9GETOPTIMALOPTIONSPROC) lcgD3D9GetProcAddress(lcgD3D9Handle, "cgD3D9GetOptimalOptions");
  cgD3D9GetTextureParameter = (PFNCGD3D9GETTEXTUREPARAMETERPROC) lcgD3D9GetProcAddress(lcgD3D9Handle, "cgD3D9GetTextureParameter");
  cgD3D9GetVertexDeclaration = (PFNCGD3D9GETVERTEXDECLARATIONPROC) lcgD3D9GetProcAddress(lcgD3D9Handle, "cgD3D9GetVertexDeclaration");
  cgD3D9IsParameterShadowingEnabled = (PFNCGD3D9ISPARAMETERSHADOWINGENABLEDPROC) lcgD3D9GetProcAddress(lcgD3D9Handle, "cgD3D9IsParameterShadowingEnabled");
  cgD3D9IsProfileSupported = (PFNCGD3D9ISPROFILESUPPORTEDPROC) lcgD3D9GetProcAddress(lcgD3D9Handle, "cgD3D9IsProfileSupported");
  cgD3D9IsProgramLoaded = (PFNCGD3D9ISPROGRAMLOADEDPROC) lcgD3D9GetProcAddress(lcgD3D9Handle, "cgD3D9IsProgramLoaded");
  cgD3D9LoadProgram = (PFNCGD3D9LOADPROGRAMPROC) lcgD3D9GetProcAddress(lcgD3D9Handle, "cgD3D9LoadProgram");
  cgD3D9RegisterStates = (PFNCGD3D9REGISTERSTATESPROC) lcgD3D9GetProcAddress(lcgD3D9Handle, "cgD3D9RegisterStates");
  cgD3D9ResourceToDeclUsage = (PFNCGD3D9RESOURCETODECLUSAGEPROC) lcgD3D9GetProcAddress(lcgD3D9Handle, "cgD3D9ResourceToDeclUsage");
  cgD3D9SetDevice = (PFNCGD3D9SETDEVICEPROC) lcgD3D9GetProcAddress(lcgD3D9Handle, "cgD3D9SetDevice");
  cgD3D9SetManageTextureParameters = (PFNCGD3D9SETMANAGETEXTUREPARAMETERSPROC) lcgD3D9GetProcAddress(lcgD3D9Handle, "cgD3D9SetManageTextureParameters");
  cgD3D9SetSamplerState = (PFNCGD3D9SETSAMPLERSTATEPROC) lcgD3D9GetProcAddress(lcgD3D9Handle, "cgD3D9SetSamplerState");
  cgD3D9SetTexture = (PFNCGD3D9SETTEXTUREPROC) lcgD3D9GetProcAddress(lcgD3D9Handle, "cgD3D9SetTexture");
  cgD3D9SetTextureParameter = (PFNCGD3D9SETTEXTUREPARAMETERPROC) lcgD3D9GetProcAddress(lcgD3D9Handle, "cgD3D9SetTextureParameter");
  cgD3D9SetTextureWrapMode = (PFNCGD3D9SETTEXTUREWRAPMODEPROC) lcgD3D9GetProcAddress(lcgD3D9Handle, "cgD3D9SetTextureWrapMode");
  cgD3D9SetUniform = (PFNCGD3D9SETUNIFORMPROC) lcgD3D9GetProcAddress(lcgD3D9Handle, "cgD3D9SetUniform");
  cgD3D9SetUniformArray = (PFNCGD3D9SETUNIFORMARRAYPROC) lcgD3D9GetProcAddress(lcgD3D9Handle, "cgD3D9SetUniformArray");
  cgD3D9SetUniformMatrix = (PFNCGD3D9SETUNIFORMMATRIXPROC) lcgD3D9GetProcAddress(lcgD3D9Handle, "cgD3D9SetUniformMatrix");
  cgD3D9SetUniformMatrixArray = (PFNCGD3D9SETUNIFORMMATRIXARRAYPROC) lcgD3D9GetProcAddress(lcgD3D9Handle, "cgD3D9SetUniformMatrixArray");
  cgD3D9TranslateCGerror = (PFNCGD3D9TRANSLATECGERRORPROC) lcgD3D9GetProcAddress(lcgD3D9Handle, "cgD3D9TranslateCGerror");
  cgD3D9TranslateHRESULT = (PFNCGD3D9TRANSLATEHRESULTPROC) lcgD3D9GetProcAddress(lcgD3D9Handle, "cgD3D9TranslateHRESULT");
  cgD3D9TypeToSize = (PFNCGD3D9TYPETOSIZEPROC) lcgD3D9GetProcAddress(lcgD3D9Handle, "cgD3D9TypeToSize");
  cgD3D9UnbindProgram = (PFNCGD3D9UNBINDPROGRAMPROC) lcgD3D9GetProcAddress(lcgD3D9Handle, "cgD3D9UnbindProgram");
  cgD3D9UnloadAllPrograms = (PFNCGD3D9UNLOADALLPROGRAMSPROC) lcgD3D9GetProcAddress(lcgD3D9Handle, "cgD3D9UnloadAllPrograms");
  cgD3D9UnloadProgram = (PFNCGD3D9UNLOADPROGRAMPROC) lcgD3D9GetProcAddress(lcgD3D9Handle, "cgD3D9UnloadProgram");
  cgD3D9ValidateVertexDeclaration = (PFNCGD3D9VALIDATEVERTEXDECLARATIONPROC) lcgD3D9GetProcAddress(lcgD3D9Handle, "cgD3D9ValidateVertexDeclaration");

  return 1;
}

void
lcgD3D9List(const char *prefix, FILE *out)
{
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D9BindProgram", cgD3D9BindProgram ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D9EnableDebugTracing", cgD3D9EnableDebugTracing ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D9EnableParameterShadowing", cgD3D9EnableParameterShadowing ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D9GetDevice", cgD3D9GetDevice ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D9GetLastError", cgD3D9GetLastError ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D9GetLatestPixelProfile", cgD3D9GetLatestPixelProfile ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D9GetLatestVertexProfile", cgD3D9GetLatestVertexProfile ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D9GetManageTextureParameters", cgD3D9GetManageTextureParameters ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D9GetOptimalOptions", cgD3D9GetOptimalOptions ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D9GetTextureParameter", cgD3D9GetTextureParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D9GetVertexDeclaration", cgD3D9GetVertexDeclaration ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D9IsParameterShadowingEnabled", cgD3D9IsParameterShadowingEnabled ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D9IsProfileSupported", cgD3D9IsProfileSupported ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D9IsProgramLoaded", cgD3D9IsProgramLoaded ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D9LoadProgram", cgD3D9LoadProgram ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D9RegisterStates", cgD3D9RegisterStates ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D9ResourceToDeclUsage", cgD3D9ResourceToDeclUsage ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D9SetDevice", cgD3D9SetDevice ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D9SetManageTextureParameters", cgD3D9SetManageTextureParameters ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D9SetSamplerState", cgD3D9SetSamplerState ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D9SetTexture", cgD3D9SetTexture ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D9SetTextureParameter", cgD3D9SetTextureParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D9SetTextureWrapMode", cgD3D9SetTextureWrapMode ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D9SetUniform", cgD3D9SetUniform ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D9SetUniformArray", cgD3D9SetUniformArray ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D9SetUniformMatrix", cgD3D9SetUniformMatrix ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D9SetUniformMatrixArray", cgD3D9SetUniformMatrixArray ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D9TranslateCGerror", cgD3D9TranslateCGerror ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D9TranslateHRESULT", cgD3D9TranslateHRESULT ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D9TypeToSize", cgD3D9TypeToSize ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D9UnbindProgram", cgD3D9UnbindProgram ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D9UnloadAllPrograms", cgD3D9UnloadAllPrograms ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D9UnloadProgram", cgD3D9UnloadProgram ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D9ValidateVertexDeclaration", cgD3D9ValidateVertexDeclaration ? "found" : "missing");
}

void
lcgD3D9Destroy(void)
{
  if (lcgD3D9Handle)
  {
    lcgD3D9FreeLibrary(lcgD3D9Handle);
    lcgD3D9Handle = NULL;
  }
}

#endif
