#if defined(_WIN32) && defined(_MSC_VER) && _MSC_VER>=1400 /* D3D10 requires VC8 */

#include "loadCgD3D10.h"

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

LcgD3D10Handle
lcgD3D10LoadLibrary(const char *filename)
{
#ifdef __APPLE__
  char *framework = NULL;

  /* 1. Try loading bare framework name */

# if defined(MAC_OS_X_VERSION_10_3)
  LcgD3D10Handle ret = (LcgD3D10Handle) dlopen(filename, RTLD_LAZY);
# else
  LcgD3D10Handle ret = (LcgD3D10Handle) NSAddImage(filename, NSADDIMAGE_OPTION_NONE);
# endif
  if (ret)
    return ret;

  /* 2. Try loading framework in Name.framework/Name */

  framework = (char *) malloc(strlen(filename)*2+12);
  sprintf(framework,"%s.framework/%s",filename,filename);

# if defined(MAC_OS_X_VERSION_10_3)
  ret = (LcgD3D10Handle) dlopen(framework, RTLD_LAZY);
# else
  ret = (LcgD3D10Handle) NSAddImage(framework, NSADDIMAGE_OPTION_NONE);
# endif

  free(framework);
  return ret;

#elif _WIN32
  return (LcgD3D10Handle) LoadLibraryA(filename);
#else
  return (LcgD3D10Handle) dlopen(filename, RTLD_LAZY);
#endif
}

int
lcgD3D10FreeLibrary(LcgD3D10Handle handle)
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
lcgD3D10GetProcAddress(LcgD3D10Handle handle, const char *name)
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
lcgD3D10GetProcName(void **function)
{
  if (!function || !*function) return NULL;
  if (function==(void **) &cgD3D10BindProgram)                                          return "cgD3D10BindProgram";
  if (function==(void **) &cgD3D10CreateBuffer)                                         return "cgD3D10CreateBuffer";
  if (function==(void **) &cgD3D10CreateBufferFromObject)                               return "cgD3D10CreateBufferFromObject";
  if (function==(void **) &cgD3D10GetBufferByIndex)                                     return "cgD3D10GetBufferByIndex";
  if (function==(void **) &cgD3D10GetBufferObject)                                      return "cgD3D10GetBufferObject";
  if (function==(void **) &cgD3D10GetCompiledProgram)                                   return "cgD3D10GetCompiledProgram";
  if (function==(void **) &cgD3D10GetDevice)                                            return "cgD3D10GetDevice";
  if (function==(void **) &cgD3D10GetIASignatureByPass)                                 return "cgD3D10GetIASignatureByPass";
  if (function==(void **) &cgD3D10GetLastError)                                         return "cgD3D10GetLastError";
  if (function==(void **) &cgD3D10GetLatestGeometryProfile)                             return "cgD3D10GetLatestGeometryProfile";
  if (function==(void **) &cgD3D10GetLatestPixelProfile)                                return "cgD3D10GetLatestPixelProfile";
  if (function==(void **) &cgD3D10GetLatestVertexProfile)                               return "cgD3D10GetLatestVertexProfile";
  if (function==(void **) &cgD3D10GetManageTextureParameters)                           return "cgD3D10GetManageTextureParameters";
  if (function==(void **) &cgD3D10GetOptimalOptions)                                    return "cgD3D10GetOptimalOptions";
  if (function==(void **) &cgD3D10GetProgramErrors)                                     return "cgD3D10GetProgramErrors";
  if (function==(void **) &cgD3D10IsProfileSupported)                                   return "cgD3D10IsProfileSupported";
  if (function==(void **) &cgD3D10IsProgramLoaded)                                      return "cgD3D10IsProgramLoaded";
  if (function==(void **) &cgD3D10LoadProgram)                                          return "cgD3D10LoadProgram";
  if (function==(void **) &cgD3D10RegisterStates)                                       return "cgD3D10RegisterStates";
  if (function==(void **) &cgD3D10SetDevice)                                            return "cgD3D10SetDevice";
  if (function==(void **) &cgD3D10SetManageTextureParameters)                           return "cgD3D10SetManageTextureParameters";
  if (function==(void **) &cgD3D10SetSamplerStateParameter)                             return "cgD3D10SetSamplerStateParameter";
  if (function==(void **) &cgD3D10SetTextureParameter)                                  return "cgD3D10SetTextureParameter";
  if (function==(void **) &cgD3D10SetTextureSamplerStateParameter)                      return "cgD3D10SetTextureSamplerStateParameter";
  if (function==(void **) &cgD3D10TranslateCGerror)                                     return "cgD3D10TranslateCGerror";
  if (function==(void **) &cgD3D10TranslateHRESULT)                                     return "cgD3D10TranslateHRESULT";
  if (function==(void **) &cgD3D10TypeToSize)                                           return "cgD3D10TypeToSize";
  if (function==(void **) &cgD3D10UnbindProgram)                                        return "cgD3D10UnbindProgram";
  if (function==(void **) &cgD3D10UnloadProgram)                                        return "cgD3D10UnloadProgram";

  return NULL;
}

extern int
lcgD3D10HasVersion(void ***version)
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
lcgD3D10GetModuleFileName(LcgD3D10Handle handle, void *function)
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

PFNCGD3D10BINDPROGRAMPROC cgD3D10BindProgram = NULL;
PFNCGD3D10CREATEBUFFERPROC cgD3D10CreateBuffer = NULL;
PFNCGD3D10CREATEBUFFERFROMOBJECTPROC cgD3D10CreateBufferFromObject = NULL;
PFNCGD3D10GETBUFFERBYINDEXPROC cgD3D10GetBufferByIndex = NULL;
PFNCGD3D10GETBUFFEROBJECTPROC cgD3D10GetBufferObject = NULL;
PFNCGD3D10GETCOMPILEDPROGRAMPROC cgD3D10GetCompiledProgram = NULL;
PFNCGD3D10GETDEVICEPROC cgD3D10GetDevice = NULL;
PFNCGD3D10GETIASIGNATUREBYPASSPROC cgD3D10GetIASignatureByPass = NULL;
PFNCGD3D10GETLASTERRORPROC cgD3D10GetLastError = NULL;
PFNCGD3D10GETLATESTGEOMETRYPROFILEPROC cgD3D10GetLatestGeometryProfile = NULL;
PFNCGD3D10GETLATESTPIXELPROFILEPROC cgD3D10GetLatestPixelProfile = NULL;
PFNCGD3D10GETLATESTVERTEXPROFILEPROC cgD3D10GetLatestVertexProfile = NULL;
PFNCGD3D10GETMANAGETEXTUREPARAMETERSPROC cgD3D10GetManageTextureParameters = NULL;
PFNCGD3D10GETOPTIMALOPTIONSPROC cgD3D10GetOptimalOptions = NULL;
PFNCGD3D10GETPROGRAMERRORSPROC cgD3D10GetProgramErrors = NULL;
PFNCGD3D10ISPROFILESUPPORTEDPROC cgD3D10IsProfileSupported = NULL;
PFNCGD3D10ISPROGRAMLOADEDPROC cgD3D10IsProgramLoaded = NULL;
PFNCGD3D10LOADPROGRAMPROC cgD3D10LoadProgram = NULL;
PFNCGD3D10REGISTERSTATESPROC cgD3D10RegisterStates = NULL;
PFNCGD3D10SETDEVICEPROC cgD3D10SetDevice = NULL;
PFNCGD3D10SETMANAGETEXTUREPARAMETERSPROC cgD3D10SetManageTextureParameters = NULL;
PFNCGD3D10SETSAMPLERSTATEPARAMETERPROC cgD3D10SetSamplerStateParameter = NULL;
PFNCGD3D10SETTEXTUREPARAMETERPROC cgD3D10SetTextureParameter = NULL;
PFNCGD3D10SETTEXTURESAMPLERSTATEPARAMETERPROC cgD3D10SetTextureSamplerStateParameter = NULL;
PFNCGD3D10TRANSLATECGERRORPROC cgD3D10TranslateCGerror = NULL;
PFNCGD3D10TRANSLATEHRESULTPROC cgD3D10TranslateHRESULT = NULL;
PFNCGD3D10TYPETOSIZEPROC cgD3D10TypeToSize = NULL;
PFNCGD3D10UNBINDPROGRAMPROC cgD3D10UnbindProgram = NULL;
PFNCGD3D10UNLOADPROGRAMPROC cgD3D10UnloadProgram = NULL;

/* Implementation */

void ***
lcgD3D10Version2_1_0000()
{
  static void **list[26] =
  {
    (void **) &cgD3D10BindProgram,
    (void **) &cgD3D10GetBufferByIndex,
    (void **) &cgD3D10GetCompiledProgram,
    (void **) &cgD3D10GetDevice,
    (void **) &cgD3D10GetIASignatureByPass,
    (void **) &cgD3D10GetLastError,
    (void **) &cgD3D10GetLatestGeometryProfile,
    (void **) &cgD3D10GetLatestPixelProfile,
    (void **) &cgD3D10GetLatestVertexProfile,
    (void **) &cgD3D10GetManageTextureParameters,
    (void **) &cgD3D10GetOptimalOptions,
    (void **) &cgD3D10GetProgramErrors,
    (void **) &cgD3D10IsProfileSupported,
    (void **) &cgD3D10IsProgramLoaded,
    (void **) &cgD3D10LoadProgram,
    (void **) &cgD3D10RegisterStates,
    (void **) &cgD3D10SetDevice,
    (void **) &cgD3D10SetManageTextureParameters,
    (void **) &cgD3D10SetSamplerStateParameter,
    (void **) &cgD3D10SetTextureParameter,
    (void **) &cgD3D10SetTextureSamplerStateParameter,
    (void **) &cgD3D10TranslateCGerror,
    (void **) &cgD3D10TranslateHRESULT,
    (void **) &cgD3D10TypeToSize,
    (void **) &cgD3D10UnloadProgram,
    NULL
  };
  return list;
}

void ***
lcgD3D10Version3_0_0000()
{
  static void **list[2] =
  {
    (void **) &cgD3D10UnbindProgram,
    NULL
  };
  return list;
}

void ***
lcgD3D10Version3_1_0000()
{
  static void **list[4] =
  {
    (void **) &cgD3D10CreateBuffer,
    (void **) &cgD3D10CreateBufferFromObject,
    (void **) &cgD3D10GetBufferObject,
    NULL
  };
  return list;
}

LcgD3D10Handle lcgD3D10Handle = NULL;

int
lcgD3D10Init(const char *filename)
{
  lcgD3D10Handle = lcgD3D10LoadLibrary(filename);
  if (!lcgD3D10Handle)
    return 0;

  cgD3D10BindProgram = (PFNCGD3D10BINDPROGRAMPROC) lcgD3D10GetProcAddress(lcgD3D10Handle, "cgD3D10BindProgram");
  cgD3D10CreateBuffer = (PFNCGD3D10CREATEBUFFERPROC) lcgD3D10GetProcAddress(lcgD3D10Handle, "cgD3D10CreateBuffer");
  cgD3D10CreateBufferFromObject = (PFNCGD3D10CREATEBUFFERFROMOBJECTPROC) lcgD3D10GetProcAddress(lcgD3D10Handle, "cgD3D10CreateBufferFromObject");
  cgD3D10GetBufferByIndex = (PFNCGD3D10GETBUFFERBYINDEXPROC) lcgD3D10GetProcAddress(lcgD3D10Handle, "cgD3D10GetBufferByIndex");
  cgD3D10GetBufferObject = (PFNCGD3D10GETBUFFEROBJECTPROC) lcgD3D10GetProcAddress(lcgD3D10Handle, "cgD3D10GetBufferObject");
  cgD3D10GetCompiledProgram = (PFNCGD3D10GETCOMPILEDPROGRAMPROC) lcgD3D10GetProcAddress(lcgD3D10Handle, "cgD3D10GetCompiledProgram");
  cgD3D10GetDevice = (PFNCGD3D10GETDEVICEPROC) lcgD3D10GetProcAddress(lcgD3D10Handle, "cgD3D10GetDevice");
  cgD3D10GetIASignatureByPass = (PFNCGD3D10GETIASIGNATUREBYPASSPROC) lcgD3D10GetProcAddress(lcgD3D10Handle, "cgD3D10GetIASignatureByPass");
  cgD3D10GetLastError = (PFNCGD3D10GETLASTERRORPROC) lcgD3D10GetProcAddress(lcgD3D10Handle, "cgD3D10GetLastError");
  cgD3D10GetLatestGeometryProfile = (PFNCGD3D10GETLATESTGEOMETRYPROFILEPROC) lcgD3D10GetProcAddress(lcgD3D10Handle, "cgD3D10GetLatestGeometryProfile");
  cgD3D10GetLatestPixelProfile = (PFNCGD3D10GETLATESTPIXELPROFILEPROC) lcgD3D10GetProcAddress(lcgD3D10Handle, "cgD3D10GetLatestPixelProfile");
  cgD3D10GetLatestVertexProfile = (PFNCGD3D10GETLATESTVERTEXPROFILEPROC) lcgD3D10GetProcAddress(lcgD3D10Handle, "cgD3D10GetLatestVertexProfile");
  cgD3D10GetManageTextureParameters = (PFNCGD3D10GETMANAGETEXTUREPARAMETERSPROC) lcgD3D10GetProcAddress(lcgD3D10Handle, "cgD3D10GetManageTextureParameters");
  cgD3D10GetOptimalOptions = (PFNCGD3D10GETOPTIMALOPTIONSPROC) lcgD3D10GetProcAddress(lcgD3D10Handle, "cgD3D10GetOptimalOptions");
  cgD3D10GetProgramErrors = (PFNCGD3D10GETPROGRAMERRORSPROC) lcgD3D10GetProcAddress(lcgD3D10Handle, "cgD3D10GetProgramErrors");
  cgD3D10IsProfileSupported = (PFNCGD3D10ISPROFILESUPPORTEDPROC) lcgD3D10GetProcAddress(lcgD3D10Handle, "cgD3D10IsProfileSupported");
  cgD3D10IsProgramLoaded = (PFNCGD3D10ISPROGRAMLOADEDPROC) lcgD3D10GetProcAddress(lcgD3D10Handle, "cgD3D10IsProgramLoaded");
  cgD3D10LoadProgram = (PFNCGD3D10LOADPROGRAMPROC) lcgD3D10GetProcAddress(lcgD3D10Handle, "cgD3D10LoadProgram");
  cgD3D10RegisterStates = (PFNCGD3D10REGISTERSTATESPROC) lcgD3D10GetProcAddress(lcgD3D10Handle, "cgD3D10RegisterStates");
  cgD3D10SetDevice = (PFNCGD3D10SETDEVICEPROC) lcgD3D10GetProcAddress(lcgD3D10Handle, "cgD3D10SetDevice");
  cgD3D10SetManageTextureParameters = (PFNCGD3D10SETMANAGETEXTUREPARAMETERSPROC) lcgD3D10GetProcAddress(lcgD3D10Handle, "cgD3D10SetManageTextureParameters");
  cgD3D10SetSamplerStateParameter = (PFNCGD3D10SETSAMPLERSTATEPARAMETERPROC) lcgD3D10GetProcAddress(lcgD3D10Handle, "cgD3D10SetSamplerStateParameter");
  cgD3D10SetTextureParameter = (PFNCGD3D10SETTEXTUREPARAMETERPROC) lcgD3D10GetProcAddress(lcgD3D10Handle, "cgD3D10SetTextureParameter");
  cgD3D10SetTextureSamplerStateParameter = (PFNCGD3D10SETTEXTURESAMPLERSTATEPARAMETERPROC) lcgD3D10GetProcAddress(lcgD3D10Handle, "cgD3D10SetTextureSamplerStateParameter");
  cgD3D10TranslateCGerror = (PFNCGD3D10TRANSLATECGERRORPROC) lcgD3D10GetProcAddress(lcgD3D10Handle, "cgD3D10TranslateCGerror");
  cgD3D10TranslateHRESULT = (PFNCGD3D10TRANSLATEHRESULTPROC) lcgD3D10GetProcAddress(lcgD3D10Handle, "cgD3D10TranslateHRESULT");
  cgD3D10TypeToSize = (PFNCGD3D10TYPETOSIZEPROC) lcgD3D10GetProcAddress(lcgD3D10Handle, "cgD3D10TypeToSize");
  cgD3D10UnbindProgram = (PFNCGD3D10UNBINDPROGRAMPROC) lcgD3D10GetProcAddress(lcgD3D10Handle, "cgD3D10UnbindProgram");
  cgD3D10UnloadProgram = (PFNCGD3D10UNLOADPROGRAMPROC) lcgD3D10GetProcAddress(lcgD3D10Handle, "cgD3D10UnloadProgram");

  return 1;
}

void
lcgD3D10List(const char *prefix, FILE *out)
{
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D10BindProgram", cgD3D10BindProgram ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D10CreateBuffer", cgD3D10CreateBuffer ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D10CreateBufferFromObject", cgD3D10CreateBufferFromObject ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D10GetBufferByIndex", cgD3D10GetBufferByIndex ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D10GetBufferObject", cgD3D10GetBufferObject ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D10GetCompiledProgram", cgD3D10GetCompiledProgram ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D10GetDevice", cgD3D10GetDevice ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D10GetIASignatureByPass", cgD3D10GetIASignatureByPass ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D10GetLastError", cgD3D10GetLastError ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D10GetLatestGeometryProfile", cgD3D10GetLatestGeometryProfile ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D10GetLatestPixelProfile", cgD3D10GetLatestPixelProfile ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D10GetLatestVertexProfile", cgD3D10GetLatestVertexProfile ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D10GetManageTextureParameters", cgD3D10GetManageTextureParameters ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D10GetOptimalOptions", cgD3D10GetOptimalOptions ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D10GetProgramErrors", cgD3D10GetProgramErrors ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D10IsProfileSupported", cgD3D10IsProfileSupported ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D10IsProgramLoaded", cgD3D10IsProgramLoaded ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D10LoadProgram", cgD3D10LoadProgram ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D10RegisterStates", cgD3D10RegisterStates ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D10SetDevice", cgD3D10SetDevice ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D10SetManageTextureParameters", cgD3D10SetManageTextureParameters ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D10SetSamplerStateParameter", cgD3D10SetSamplerStateParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D10SetTextureParameter", cgD3D10SetTextureParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D10SetTextureSamplerStateParameter", cgD3D10SetTextureSamplerStateParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D10TranslateCGerror", cgD3D10TranslateCGerror ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D10TranslateHRESULT", cgD3D10TranslateHRESULT ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D10TypeToSize", cgD3D10TypeToSize ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D10UnbindProgram", cgD3D10UnbindProgram ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D10UnloadProgram", cgD3D10UnloadProgram ? "found" : "missing");
}

void
lcgD3D10Destroy(void)
{
  if (lcgD3D10Handle)
  {
    lcgD3D10FreeLibrary(lcgD3D10Handle);
    lcgD3D10Handle = NULL;
  }
}

#endif
