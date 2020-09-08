#if defined(_WIN32) && defined(_MSC_VER) && _MSC_VER>=1400 /* D3D10 requires VC8 */

#include "loadCgD3D11.h"

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

LcgD3D11Handle
lcgD3D11LoadLibrary(const char *filename)
{
#ifdef __APPLE__
  char *framework = NULL;

  /* 1. Try loading bare framework name */

# if defined(MAC_OS_X_VERSION_10_3)
  LcgD3D11Handle ret = (LcgD3D11Handle) dlopen(filename, RTLD_LAZY);
# else
  LcgD3D11Handle ret = (LcgD3D11Handle) NSAddImage(filename, NSADDIMAGE_OPTION_NONE);
# endif
  if (ret)
    return ret;

  /* 2. Try loading framework in Name.framework/Name */

  framework = (char *) malloc(strlen(filename)*2+12);
  sprintf(framework,"%s.framework/%s",filename,filename);

# if defined(MAC_OS_X_VERSION_10_3)
  ret = (LcgD3D11Handle) dlopen(framework, RTLD_LAZY);
# else
  ret = (LcgD3D11Handle) NSAddImage(framework, NSADDIMAGE_OPTION_NONE);
# endif

  free(framework);
  return ret;

#elif _WIN32
  return (LcgD3D11Handle) LoadLibraryA(filename);
#else
  return (LcgD3D11Handle) dlopen(filename, RTLD_LAZY);
#endif
}

int
lcgD3D11FreeLibrary(LcgD3D11Handle handle)
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
lcgD3D11GetProcAddress(LcgD3D11Handle handle, const char *name)
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
lcgD3D11GetProcName(void **function)
{
  if (!function || !*function) return NULL;
  if (function==(void **) &cgD3D11BindProgram)                                          return "cgD3D11BindProgram";
  if (function==(void **) &cgD3D11CreateBuffer)                                         return "cgD3D11CreateBuffer";
  if (function==(void **) &cgD3D11CreateBufferFromObject)                               return "cgD3D11CreateBufferFromObject";
  if (function==(void **) &cgD3D11GetBufferByIndex)                                     return "cgD3D11GetBufferByIndex";
  if (function==(void **) &cgD3D11GetBufferObject)                                      return "cgD3D11GetBufferObject";
  if (function==(void **) &cgD3D11GetCompiledProgram)                                   return "cgD3D11GetCompiledProgram";
  if (function==(void **) &cgD3D11GetDevice)                                            return "cgD3D11GetDevice";
  if (function==(void **) &cgD3D11GetIASignatureByPass)                                 return "cgD3D11GetIASignatureByPass";
  if (function==(void **) &cgD3D11GetLastError)                                         return "cgD3D11GetLastError";
  if (function==(void **) &cgD3D11GetLatestDomainProfile)                               return "cgD3D11GetLatestDomainProfile";
  if (function==(void **) &cgD3D11GetLatestGeometryProfile)                             return "cgD3D11GetLatestGeometryProfile";
  if (function==(void **) &cgD3D11GetLatestHullProfile)                                 return "cgD3D11GetLatestHullProfile";
  if (function==(void **) &cgD3D11GetLatestPixelProfile)                                return "cgD3D11GetLatestPixelProfile";
  if (function==(void **) &cgD3D11GetLatestVertexProfile)                               return "cgD3D11GetLatestVertexProfile";
  if (function==(void **) &cgD3D11GetManageTextureParameters)                           return "cgD3D11GetManageTextureParameters";
  if (function==(void **) &cgD3D11GetOptimalOptions)                                    return "cgD3D11GetOptimalOptions";
  if (function==(void **) &cgD3D11GetProgramErrors)                                     return "cgD3D11GetProgramErrors";
  if (function==(void **) &cgD3D11IsProfileSupported)                                   return "cgD3D11IsProfileSupported";
  if (function==(void **) &cgD3D11IsProgramLoaded)                                      return "cgD3D11IsProgramLoaded";
  if (function==(void **) &cgD3D11LoadProgram)                                          return "cgD3D11LoadProgram";
  if (function==(void **) &cgD3D11RegisterStates)                                       return "cgD3D11RegisterStates";
  if (function==(void **) &cgD3D11SetDevice)                                            return "cgD3D11SetDevice";
  if (function==(void **) &cgD3D11SetManageTextureParameters)                           return "cgD3D11SetManageTextureParameters";
  if (function==(void **) &cgD3D11SetSamplerStateParameter)                             return "cgD3D11SetSamplerStateParameter";
  if (function==(void **) &cgD3D11SetTextureParameter)                                  return "cgD3D11SetTextureParameter";
  if (function==(void **) &cgD3D11SetTextureSamplerStateParameter)                      return "cgD3D11SetTextureSamplerStateParameter";
  if (function==(void **) &cgD3D11TranslateCGerror)                                     return "cgD3D11TranslateCGerror";
  if (function==(void **) &cgD3D11TranslateHRESULT)                                     return "cgD3D11TranslateHRESULT";
  if (function==(void **) &cgD3D11TypeToSize)                                           return "cgD3D11TypeToSize";
  if (function==(void **) &cgD3D11UnbindProgram)                                        return "cgD3D11UnbindProgram";
  if (function==(void **) &cgD3D11UnloadProgram)                                        return "cgD3D11UnloadProgram";

  return NULL;
}

extern int
lcgD3D11HasVersion(void ***version)
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
lcgD3D11GetModuleFileName(LcgD3D11Handle handle, void *function)
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

PFNCGD3D11BINDPROGRAMPROC cgD3D11BindProgram = NULL;
PFNCGD3D11CREATEBUFFERPROC cgD3D11CreateBuffer = NULL;
PFNCGD3D11CREATEBUFFERFROMOBJECTPROC cgD3D11CreateBufferFromObject = NULL;
PFNCGD3D11GETBUFFERBYINDEXPROC cgD3D11GetBufferByIndex = NULL;
PFNCGD3D11GETBUFFEROBJECTPROC cgD3D11GetBufferObject = NULL;
PFNCGD3D11GETCOMPILEDPROGRAMPROC cgD3D11GetCompiledProgram = NULL;
PFNCGD3D11GETDEVICEPROC cgD3D11GetDevice = NULL;
PFNCGD3D11GETIASIGNATUREBYPASSPROC cgD3D11GetIASignatureByPass = NULL;
PFNCGD3D11GETLASTERRORPROC cgD3D11GetLastError = NULL;
PFNCGD3D11GETLATESTDOMAINPROFILEPROC cgD3D11GetLatestDomainProfile = NULL;
PFNCGD3D11GETLATESTGEOMETRYPROFILEPROC cgD3D11GetLatestGeometryProfile = NULL;
PFNCGD3D11GETLATESTHULLPROFILEPROC cgD3D11GetLatestHullProfile = NULL;
PFNCGD3D11GETLATESTPIXELPROFILEPROC cgD3D11GetLatestPixelProfile = NULL;
PFNCGD3D11GETLATESTVERTEXPROFILEPROC cgD3D11GetLatestVertexProfile = NULL;
PFNCGD3D11GETMANAGETEXTUREPARAMETERSPROC cgD3D11GetManageTextureParameters = NULL;
PFNCGD3D11GETOPTIMALOPTIONSPROC cgD3D11GetOptimalOptions = NULL;
PFNCGD3D11GETPROGRAMERRORSPROC cgD3D11GetProgramErrors = NULL;
PFNCGD3D11ISPROFILESUPPORTEDPROC cgD3D11IsProfileSupported = NULL;
PFNCGD3D11ISPROGRAMLOADEDPROC cgD3D11IsProgramLoaded = NULL;
PFNCGD3D11LOADPROGRAMPROC cgD3D11LoadProgram = NULL;
PFNCGD3D11REGISTERSTATESPROC cgD3D11RegisterStates = NULL;
PFNCGD3D11SETDEVICEPROC cgD3D11SetDevice = NULL;
PFNCGD3D11SETMANAGETEXTUREPARAMETERSPROC cgD3D11SetManageTextureParameters = NULL;
PFNCGD3D11SETSAMPLERSTATEPARAMETERPROC cgD3D11SetSamplerStateParameter = NULL;
PFNCGD3D11SETTEXTUREPARAMETERPROC cgD3D11SetTextureParameter = NULL;
PFNCGD3D11SETTEXTURESAMPLERSTATEPARAMETERPROC cgD3D11SetTextureSamplerStateParameter = NULL;
PFNCGD3D11TRANSLATECGERRORPROC cgD3D11TranslateCGerror = NULL;
PFNCGD3D11TRANSLATEHRESULTPROC cgD3D11TranslateHRESULT = NULL;
PFNCGD3D11TYPETOSIZEPROC cgD3D11TypeToSize = NULL;
PFNCGD3D11UNBINDPROGRAMPROC cgD3D11UnbindProgram = NULL;
PFNCGD3D11UNLOADPROGRAMPROC cgD3D11UnloadProgram = NULL;

/* Implementation */

void ***
lcgD3D11Version3_0_0000()
{
  static void **list[29] =
  {
    (void **) &cgD3D11BindProgram,
    (void **) &cgD3D11GetBufferByIndex,
    (void **) &cgD3D11GetCompiledProgram,
    (void **) &cgD3D11GetDevice,
    (void **) &cgD3D11GetIASignatureByPass,
    (void **) &cgD3D11GetLastError,
    (void **) &cgD3D11GetLatestDomainProfile,
    (void **) &cgD3D11GetLatestGeometryProfile,
    (void **) &cgD3D11GetLatestHullProfile,
    (void **) &cgD3D11GetLatestPixelProfile,
    (void **) &cgD3D11GetLatestVertexProfile,
    (void **) &cgD3D11GetManageTextureParameters,
    (void **) &cgD3D11GetOptimalOptions,
    (void **) &cgD3D11GetProgramErrors,
    (void **) &cgD3D11IsProfileSupported,
    (void **) &cgD3D11IsProgramLoaded,
    (void **) &cgD3D11LoadProgram,
    (void **) &cgD3D11RegisterStates,
    (void **) &cgD3D11SetDevice,
    (void **) &cgD3D11SetManageTextureParameters,
    (void **) &cgD3D11SetSamplerStateParameter,
    (void **) &cgD3D11SetTextureParameter,
    (void **) &cgD3D11SetTextureSamplerStateParameter,
    (void **) &cgD3D11TranslateCGerror,
    (void **) &cgD3D11TranslateHRESULT,
    (void **) &cgD3D11TypeToSize,
    (void **) &cgD3D11UnbindProgram,
    (void **) &cgD3D11UnloadProgram,
    NULL
  };
  return list;
}

void ***
lcgD3D11Version3_1_0000()
{
  static void **list[4] =
  {
    (void **) &cgD3D11CreateBuffer,
    (void **) &cgD3D11CreateBufferFromObject,
    (void **) &cgD3D11GetBufferObject,
    NULL
  };
  return list;
}

LcgD3D11Handle lcgD3D11Handle = NULL;

int
lcgD3D11Init(const char *filename)
{
  lcgD3D11Handle = lcgD3D11LoadLibrary(filename);
  if (!lcgD3D11Handle)
    return 0;

  cgD3D11BindProgram = (PFNCGD3D11BINDPROGRAMPROC) lcgD3D11GetProcAddress(lcgD3D11Handle, "cgD3D11BindProgram");
  cgD3D11CreateBuffer = (PFNCGD3D11CREATEBUFFERPROC) lcgD3D11GetProcAddress(lcgD3D11Handle, "cgD3D11CreateBuffer");
  cgD3D11CreateBufferFromObject = (PFNCGD3D11CREATEBUFFERFROMOBJECTPROC) lcgD3D11GetProcAddress(lcgD3D11Handle, "cgD3D11CreateBufferFromObject");
  cgD3D11GetBufferByIndex = (PFNCGD3D11GETBUFFERBYINDEXPROC) lcgD3D11GetProcAddress(lcgD3D11Handle, "cgD3D11GetBufferByIndex");
  cgD3D11GetBufferObject = (PFNCGD3D11GETBUFFEROBJECTPROC) lcgD3D11GetProcAddress(lcgD3D11Handle, "cgD3D11GetBufferObject");
  cgD3D11GetCompiledProgram = (PFNCGD3D11GETCOMPILEDPROGRAMPROC) lcgD3D11GetProcAddress(lcgD3D11Handle, "cgD3D11GetCompiledProgram");
  cgD3D11GetDevice = (PFNCGD3D11GETDEVICEPROC) lcgD3D11GetProcAddress(lcgD3D11Handle, "cgD3D11GetDevice");
  cgD3D11GetIASignatureByPass = (PFNCGD3D11GETIASIGNATUREBYPASSPROC) lcgD3D11GetProcAddress(lcgD3D11Handle, "cgD3D11GetIASignatureByPass");
  cgD3D11GetLastError = (PFNCGD3D11GETLASTERRORPROC) lcgD3D11GetProcAddress(lcgD3D11Handle, "cgD3D11GetLastError");
  cgD3D11GetLatestDomainProfile = (PFNCGD3D11GETLATESTDOMAINPROFILEPROC) lcgD3D11GetProcAddress(lcgD3D11Handle, "cgD3D11GetLatestDomainProfile");
  cgD3D11GetLatestGeometryProfile = (PFNCGD3D11GETLATESTGEOMETRYPROFILEPROC) lcgD3D11GetProcAddress(lcgD3D11Handle, "cgD3D11GetLatestGeometryProfile");
  cgD3D11GetLatestHullProfile = (PFNCGD3D11GETLATESTHULLPROFILEPROC) lcgD3D11GetProcAddress(lcgD3D11Handle, "cgD3D11GetLatestHullProfile");
  cgD3D11GetLatestPixelProfile = (PFNCGD3D11GETLATESTPIXELPROFILEPROC) lcgD3D11GetProcAddress(lcgD3D11Handle, "cgD3D11GetLatestPixelProfile");
  cgD3D11GetLatestVertexProfile = (PFNCGD3D11GETLATESTVERTEXPROFILEPROC) lcgD3D11GetProcAddress(lcgD3D11Handle, "cgD3D11GetLatestVertexProfile");
  cgD3D11GetManageTextureParameters = (PFNCGD3D11GETMANAGETEXTUREPARAMETERSPROC) lcgD3D11GetProcAddress(lcgD3D11Handle, "cgD3D11GetManageTextureParameters");
  cgD3D11GetOptimalOptions = (PFNCGD3D11GETOPTIMALOPTIONSPROC) lcgD3D11GetProcAddress(lcgD3D11Handle, "cgD3D11GetOptimalOptions");
  cgD3D11GetProgramErrors = (PFNCGD3D11GETPROGRAMERRORSPROC) lcgD3D11GetProcAddress(lcgD3D11Handle, "cgD3D11GetProgramErrors");
  cgD3D11IsProfileSupported = (PFNCGD3D11ISPROFILESUPPORTEDPROC) lcgD3D11GetProcAddress(lcgD3D11Handle, "cgD3D11IsProfileSupported");
  cgD3D11IsProgramLoaded = (PFNCGD3D11ISPROGRAMLOADEDPROC) lcgD3D11GetProcAddress(lcgD3D11Handle, "cgD3D11IsProgramLoaded");
  cgD3D11LoadProgram = (PFNCGD3D11LOADPROGRAMPROC) lcgD3D11GetProcAddress(lcgD3D11Handle, "cgD3D11LoadProgram");
  cgD3D11RegisterStates = (PFNCGD3D11REGISTERSTATESPROC) lcgD3D11GetProcAddress(lcgD3D11Handle, "cgD3D11RegisterStates");
  cgD3D11SetDevice = (PFNCGD3D11SETDEVICEPROC) lcgD3D11GetProcAddress(lcgD3D11Handle, "cgD3D11SetDevice");
  cgD3D11SetManageTextureParameters = (PFNCGD3D11SETMANAGETEXTUREPARAMETERSPROC) lcgD3D11GetProcAddress(lcgD3D11Handle, "cgD3D11SetManageTextureParameters");
  cgD3D11SetSamplerStateParameter = (PFNCGD3D11SETSAMPLERSTATEPARAMETERPROC) lcgD3D11GetProcAddress(lcgD3D11Handle, "cgD3D11SetSamplerStateParameter");
  cgD3D11SetTextureParameter = (PFNCGD3D11SETTEXTUREPARAMETERPROC) lcgD3D11GetProcAddress(lcgD3D11Handle, "cgD3D11SetTextureParameter");
  cgD3D11SetTextureSamplerStateParameter = (PFNCGD3D11SETTEXTURESAMPLERSTATEPARAMETERPROC) lcgD3D11GetProcAddress(lcgD3D11Handle, "cgD3D11SetTextureSamplerStateParameter");
  cgD3D11TranslateCGerror = (PFNCGD3D11TRANSLATECGERRORPROC) lcgD3D11GetProcAddress(lcgD3D11Handle, "cgD3D11TranslateCGerror");
  cgD3D11TranslateHRESULT = (PFNCGD3D11TRANSLATEHRESULTPROC) lcgD3D11GetProcAddress(lcgD3D11Handle, "cgD3D11TranslateHRESULT");
  cgD3D11TypeToSize = (PFNCGD3D11TYPETOSIZEPROC) lcgD3D11GetProcAddress(lcgD3D11Handle, "cgD3D11TypeToSize");
  cgD3D11UnbindProgram = (PFNCGD3D11UNBINDPROGRAMPROC) lcgD3D11GetProcAddress(lcgD3D11Handle, "cgD3D11UnbindProgram");
  cgD3D11UnloadProgram = (PFNCGD3D11UNLOADPROGRAMPROC) lcgD3D11GetProcAddress(lcgD3D11Handle, "cgD3D11UnloadProgram");

  return 1;
}

void
lcgD3D11List(const char *prefix, FILE *out)
{
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D11BindProgram", cgD3D11BindProgram ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D11CreateBuffer", cgD3D11CreateBuffer ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D11CreateBufferFromObject", cgD3D11CreateBufferFromObject ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D11GetBufferByIndex", cgD3D11GetBufferByIndex ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D11GetBufferObject", cgD3D11GetBufferObject ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D11GetCompiledProgram", cgD3D11GetCompiledProgram ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D11GetDevice", cgD3D11GetDevice ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D11GetIASignatureByPass", cgD3D11GetIASignatureByPass ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D11GetLastError", cgD3D11GetLastError ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D11GetLatestDomainProfile", cgD3D11GetLatestDomainProfile ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D11GetLatestGeometryProfile", cgD3D11GetLatestGeometryProfile ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D11GetLatestHullProfile", cgD3D11GetLatestHullProfile ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D11GetLatestPixelProfile", cgD3D11GetLatestPixelProfile ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D11GetLatestVertexProfile", cgD3D11GetLatestVertexProfile ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D11GetManageTextureParameters", cgD3D11GetManageTextureParameters ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D11GetOptimalOptions", cgD3D11GetOptimalOptions ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D11GetProgramErrors", cgD3D11GetProgramErrors ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D11IsProfileSupported", cgD3D11IsProfileSupported ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D11IsProgramLoaded", cgD3D11IsProgramLoaded ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D11LoadProgram", cgD3D11LoadProgram ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D11RegisterStates", cgD3D11RegisterStates ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D11SetDevice", cgD3D11SetDevice ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D11SetManageTextureParameters", cgD3D11SetManageTextureParameters ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D11SetSamplerStateParameter", cgD3D11SetSamplerStateParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D11SetTextureParameter", cgD3D11SetTextureParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D11SetTextureSamplerStateParameter", cgD3D11SetTextureSamplerStateParameter ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D11TranslateCGerror", cgD3D11TranslateCGerror ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D11TranslateHRESULT", cgD3D11TranslateHRESULT ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D11TypeToSize", cgD3D11TypeToSize ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D11UnbindProgram", cgD3D11UnbindProgram ? "found" : "missing");
  fprintf(out, "%s%-60s ... %s\n", prefix, "cgD3D11UnloadProgram", cgD3D11UnloadProgram ? "found" : "missing");
}

void
lcgD3D11Destroy(void)
{
  if (lcgD3D11Handle)
  {
    lcgD3D11FreeLibrary(lcgD3D11Handle);
    lcgD3D11Handle = NULL;
  }
}

#endif
