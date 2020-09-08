#include "loadCg.h"
#include "loadCgGL.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#ifdef _WIN32
#include <windows.h>
#define strcasecmp stricmp
#else
#include <dlfcn.h>
#include <strings.h>
#endif

/* DX9 */

#if defined(_WIN32) && !defined(__CYGWIN__)
#define SUPPORT_D3D9
#endif

/* DX10, DX11 */

#if defined(_WIN32) && defined(_MSC_VER) && _MSC_VER>=1400
#define SUPPORT_D3D10
#define SUPPORT_D3D11
#endif

#if defined(SUPPORT_D3D9)
extern int  lcgD3D9Init(const char *filename);
extern void lcgD3D9List(const char *prefix, FILE *out);
extern void lcgD3D9Destroy(void);
extern int  lcgD3D9HasVersion(void ***version);
extern void ***lcgD3D9Version1_4_0000();
extern void ***lcgD3D9Version1_5_0001();
extern void ***lcgD3D9Version3_0_0000();
#endif

#if defined(SUPPORT_D3D10)
extern int  lcgD3D10Init(const char *filename);
extern void lcgD3D10List(const char *prefix, FILE *out);
extern void lcgD3D10Destroy(void);
extern int  lcgD3D10HasVersion(void ***version);
extern void ***lcgD3D10Version2_1_0000();
extern void ***lcgD3D10Version3_0_0000();
#endif

#if defined(SUPPORT_D3D11)
extern int  lcgD3D11Init(const char *filename);
extern void lcgD3D11List(const char *prefix, FILE *out);
extern void lcgD3D11Destroy(void);
extern int  lcgD3D11HasVersion(void ***version);
extern void ***lcgD3D11Version3_0_0000();
#endif

static void HandleOptions(int argc, char *argv[]);
static void PrintUsage(void);
static void ScanVersionString(const char* pVersionString);
static void DumpProfiles(void);
static void DumpVersions(void);
static void DumpEntries(void);

static const char* g_pLibraryNameCg = NULL;
static const char* g_pLibraryNameCgGL = NULL;
#if defined(SUPPORT_D3D9)
static const char* g_pLibraryNameCgD3D9 = NULL;
#endif
#if defined(SUPPORT_D3D10)
static const char* g_pLibraryNameCgD3D10 = NULL;
#endif
#if defined(SUPPORT_D3D11)
static const char* g_pLibraryNameCgD3D11 = NULL;
#endif
static const char* g_pLibrary = "";
static const char* g_pVersion = NULL;
static const char* g_pArch = NULL;
static const char* g_pBuildInfo = NULL;
static const char* g_pExeName = NULL;
static int g_VersionMajor = 0;
static int g_VersionMinor = 0;
static int g_VersionRelease = 0;
static int g_DumpProfiles = 0;
static int g_DumpVersions = 0;
static int g_DumpEntries = 0;

#ifdef _WIN32
static char tempSpace[2048];
#endif

int main( int argc, char *argv[] )
{
  // library name is platform specific

#ifdef _WIN32
  g_pLibraryNameCg = "cg.dll";
  g_pLibraryNameCgGL = "cgGL.dll";
#if defined(SUPPORT_D3D9)
  g_pLibraryNameCgD3D9 = "cgD3D9.dll";
#endif
#if defined(SUPPORT_D3D10)
  g_pLibraryNameCgD3D10 = "cgD3D10.dll";
#endif
#if defined(SUPPORT_D3D11)
  g_pLibraryNameCgD3D11 = "cgD3D11.dll";
#endif
#else
#ifdef __APPLE__
  g_pLibraryNameCg = "Cg";
  g_pLibraryNameCgGL = "Cg";
#else
  g_pLibraryNameCg = "libCg.so";
  g_pLibraryNameCgGL = "libCgGL.so";
#endif
#endif

  // if any arguments were passed, assume that the first
  // contains the path to the library of interest

  HandleOptions(argc, argv);

  // load the library

  if ( !lcgInit( g_pLibraryNameCg )  || !cgGetString ) {
    printf( "  failed to load library: %s\n", g_pLibraryNameCg );
#ifdef _WIN32
    FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM, NULL,
                   GetLastError(), 0, tempSpace, 2048, NULL );
    printf( "  LoadLibrary error: %s", tempSpace );
#else
    printf( "  failed to load library: %s\n", g_pLibraryNameCg );
    printf( "  dlopen error: %s\n", dlerror() );
#endif
    return 1;
  }

  // load the cgGL entry points too

  lcgGLInit( g_pLibraryNameCgGL );

  // load the cgD3D entry points too

#if defined(SUPPORT_D3D9)
  lcgD3D9Init( g_pLibraryNameCgD3D9 );
#endif

#if defined(SUPPORT_D3D10)
  lcgD3D10Init( g_pLibraryNameCgD3D10 );
#endif

#if defined(SUPPORT_D3D11)
  lcgD3D11Init( g_pLibraryNameCgD3D11 );
#endif

  // get the name of the library which satisfied this symbol.  this
  // is useful if the dynamic loader located the library by searching
  // along LD_LIBRARY_PATH, DYLD_LIBRARY_PATH, or etc.

  g_pLibrary = lcgGetModuleFileName( lcgHandle, (void *) cgGetString );

  // get version from library

  g_pVersion = cgGetString( CG_VERSION );
  g_pBuildInfo = cgGetString( (CGenum) 4151 );

  ScanVersionString(g_pVersion);

  // Architecture for Windows, Mac OS X, Linux, Solaris

#if defined(_ARM_)
  g_pArch = "ARM";
#elif defined(_WIN64)
  g_pArch = "x86_64";
#elif defined(_WIN32)
  g_pArch = "i386";
#elif defined(__APPLE__) || defined(__linux) || defined(__sun)
#if defined(__i386__) || defined(__i386)
  g_pArch = "i386";
#elif defined(__x86_64__) || defined(__x86_64)
  g_pArch = "x86_64";
#elif defined(__ppc__)
  g_pArch = "ppc";
#endif
#endif

  // print results

  printf( "  Library      = %s\n", ( g_pLibrary ? g_pLibrary : "" ) );
  printf( "  Version      = %s\n", ( g_pVersion ? g_pVersion : "" ) );

  if (g_pArch)
    printf( "  Architecture = %s\n", g_pArch );

  printf( "  Build Info   = %s\n", ( g_pBuildInfo ? g_pBuildInfo : "" ) );
  printf( "  cgGetString  = %p\n", cgGetString );

  DumpProfiles();
  DumpVersions();
  DumpEntries();

  return 0;
}

static void PrintUsage(void)
{
  printf( "Usage: %s [-profiles] [-entries] [/path/to/library]\n", g_pExeName );
}

static void HandleOptions(int argc, char *argv[])
{
  int ii;

  // first argv is program name

  g_pExeName = argv[0];

  // last argv (if it doesn't begin with '-') is library name

  if ( argc > 1 && *(argv[argc-1]) != '-') {
    g_pLibraryNameCg = argv[argc-1];
    argc--;
  }

  // Parse remaining arguments

  for (ii = 1; ii < argc; ii++) {
    if (!strcasecmp(argv[ii], "-profiles")) {
      g_DumpProfiles = 1;
    } else if (!strcasecmp(argv[ii], "-versions")) {
      g_DumpVersions = 1;
    } else if (!strcasecmp(argv[ii], "-entries")) {
      g_DumpEntries = 1;
    } else {
      PrintUsage();
      exit( 1 );
    }
  }
}

static void ScanVersionString(const char* pVersionString)
{
  char* pNext = NULL;
  g_VersionMajor = strtol( pVersionString, &pNext, 10 );
  pNext++;
  g_VersionMinor = strtol( pNext, &pNext, 10 );
  pNext++;
  g_VersionRelease = strtol( pNext, &pNext, 10 );
}

static void DumpProfiles(void)
{
  int ii;
  int nProfiles;
  CGprofile profile;

  // dump profiles when:
  //   option -profiles passed in command line, and
  //   library version is 2.2 or greater

  if ( !g_DumpProfiles ||
       (g_VersionMajor < 2) ||
       (g_VersionMajor == 2 && g_VersionMinor < 2) ) {
    return;
  }

  if ( !cgGetNumSupportedProfiles ||
       !cgGetSupportedProfile ||
       !cgGetProfileString ) {
    return;
  }

  nProfiles = cgGetNumSupportedProfiles();

  printf("\n  Supported profiles:\n\n");

  for (ii=0; ii<nProfiles; ++ii) {
    profile = cgGetSupportedProfile(ii);
    printf("    %i = %s\n", profile, cgGetProfileString(profile));
  }
}

static void DumpVersions(void)
{
  if ( !g_DumpVersions ) {
    return;
  }

  printf("\n");
  printf("  Cg      1.1 ... %s\n", lcgHasVersion( lcgVersion1_1_0000() )                                          ? "supported" : "not available" );
  printf("  Cg      1.2 ... %s\n", lcgHasVersion( lcgVersion1_2_0000() )                                          ? "supported" : "not available" );
  printf("  Cg      1.4 ... %s\n", lcgHasVersion( lcgVersion1_4_0000() )                                          ? "supported" : "not available" );
  printf("  Cg      1.5 ... %s\n", lcgHasVersion( lcgVersion1_5_0000() ) && lcgHasVersion( lcgVersion1_5_0001() ) ? "supported" : "not available" );
  printf("  Cg      2.0 ... %s\n", lcgHasVersion( lcgVersion2_0_0000() )                                          ? "supported" : "not available" );
  printf("  Cg      2.1 ... %s\n", lcgHasVersion( lcgVersion2_1_0000() )                                          ? "supported" : "not available" );
  printf("  Cg      2.2 ... %s\n", lcgHasVersion( lcgVersion2_2_0000() )                                          ? "supported" : "not available" );
  printf("  Cg      3.0 ... %s\n", lcgHasVersion( lcgVersion3_0_0000() ) && lcgHasVersion( lcgVersion3_0_0005() ) ? "supported" : "not available" );
  printf("  Cg      3.1 ... %s\n", lcgHasVersion( lcgVersion3_1_0000() )                                          ? "supported" : "not available" );

  printf("\n");
  printf("  CgGL    1.1 ... %s\n", lcgGLHasVersion( lcgGLVersion1_1_0000() )                                      ? "supported" : "not available" );
  printf("  CgGL    1.2 ... %s\n", lcgGLHasVersion( lcgGLVersion1_2_0000() )                                      ? "supported" : "not available" );
  printf("  CgGL    1.4 ... %s\n", lcgGLHasVersion( lcgGLVersion1_4_0000() )                                      ? "supported" : "not available" );
  printf("  CgGL    1.5 ... %s\n", lcgGLHasVersion( lcgGLVersion1_5_0000() )                                      ? "supported" : "not available" );
  printf("  CgGL    2.0 ... %s\n", lcgGLHasVersion( lcgGLVersion2_0_0000() )                                      ? "supported" : "not available" );
  printf("  CgGL    2.1 ... %s\n", lcgGLHasVersion( lcgGLVersion2_1_0000() )                                      ? "supported" : "not available" );
  printf("  CgGL    2.2 ... %s\n", lcgGLHasVersion( lcgGLVersion2_2_0000() )                                      ? "supported" : "not available" );
  printf("  CgGL    3.1 ... %s\n", lcgGLHasVersion( lcgGLVersion3_1_0000() )                                      ? "supported" : "not available" );

#if defined(SUPPORT_D3D9)
  printf("\n");
  printf("  CgD3D9  1.4 ... %s\n", lcgD3D9HasVersion( lcgD3D9Version1_4_0000() )                                  ? "supported" : "not available" );
  printf("  CgD3D9  1.5 ... %s\n", lcgD3D9HasVersion( lcgD3D9Version1_5_0001() )                                  ? "supported" : "not available" );
  printf("  CgD3D9  3.0 ... %s\n", lcgD3D9HasVersion( lcgD3D9Version3_0_0000() )                                  ? "supported" : "not available" );
#endif

#if defined(SUPPORT_D3D10)
  printf("\n");
  printf("  CgD3D10 2.1 ... %s\n", lcgD3D10HasVersion( lcgD3D10Version2_1_0000() )                                ? "supported" : "not available" );
  printf("  CgD3D10 3.0 ... %s\n", lcgD3D10HasVersion( lcgD3D10Version3_0_0000() )                                ? "supported" : "not available" );
#endif

#if defined(SUPPORT_D3D11)
  printf("\n");
  printf("  CgD3D11 3.0 ... %s\n", lcgD3D11HasVersion( lcgD3D11Version3_0_0000() )                                ? "supported" : "not available" );
#endif
}

static void DumpEntries(void)
{
  if ( !g_DumpEntries ) {
    return;
  }

  printf("\n  Cg entry points:\n\n");
  lcgList("    ", stdout);
  printf("\n  CgGL entry points:\n\n");
  lcgGLList("    ", stdout);

#if defined(SUPPORT_D3D9)
  printf("\n  CgD3D9 entry points:\n\n");
  lcgD3D9List("    ", stdout);
#endif

#if defined(SUPPORT_D3D10)
  printf("\n  CgD3D10 entry points:\n\n");
  lcgD3D10List("    ", stdout);
#endif

#if defined(SUPPORT_D3D11)
  printf("\n  CgD3D11 entry points:\n\n");
  lcgD3D11List("    ", stdout);
#endif
}
