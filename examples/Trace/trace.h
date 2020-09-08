#ifndef TRACE_H
#define TRACE_H

#ifdef _WIN32
# define DLLEXPORT __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__>=4
# define DLLEXPORT __attribute__ ((visibility("default")))
#elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)
# define DLLEXPORT __global
#else
# define DLLEXPORT
#endif

/* Central trace library public API */

typedef void *(*GetProcAddressFunc)(const char *);

DLLEXPORT extern const char *traceLibraryLocation(const char *);
DLLEXPORT extern void traceRegister(GetProcAddressFunc);
DLLEXPORT extern void *traceGetProcAddress(const char *);

/* trace.c */

DLLEXPORT extern void traceInfo(const char *, ...);
DLLEXPORT extern void traceWarning(const char *, ...);
DLLEXPORT extern void traceError(const char *, ...);

/* traceFilter.c */

DLLEXPORT extern int  traceEnabled(const char *, int *);

/* traceOutput.c */

DLLEXPORT extern void traceBegin(void);
DLLEXPORT extern void traceFunction(const char *);
DLLEXPORT extern void traceInputParameter(const char *, const char *, ...);
DLLEXPORT extern void tracePreCondition(void);
DLLEXPORT extern void tracePostCondition(void);
DLLEXPORT extern void traceOutputParameter(const char *, const char *, ...);
DLLEXPORT extern void traceReturn(const char *, ...);
DLLEXPORT extern void traceEnd(void);

#undef DLLEXPORT

/* Central trace library private API (not exported) */

#ifdef TRACE_INTERNALS

#include <stdio.h>

extern int   indent;
extern int   indentStep;
extern char  indentBuffer[1024];
extern int   base64;
extern int   traceEnable;          /* CG_TRACE_ENABLE=0        (default: enabled)   */
extern long  maxBlobSize;          /* CG_TRACE_BLOB_LIMIT=n    (default: unlimited) */
extern FILE *traceOut;             /* CG_TRACE_FILE=filename   (default: stdout)    */
extern FILE *traceErr;             /* CG_TRACE_ERROR=filename  (default: stderr)    */
extern int   timeStamp;            /* CG_TRACE_TIMESTAMP=1     (default: disabled)  */
extern int   maxDepth;             /* CG_TRACE_DEPTH_LIMIT=n   (default: unlimited) */
extern int   parameter;            /* CG_TRACE_PARAMETER=0     (default: enabled)   */

/* trace.c */

extern void updateIndent(int step);
extern void traceInit(void);

extern int  isStringAscii(const char *str);
extern int  isArrayAscii(const char *str, const long length);

/* traceOutput.c */

extern int currentDepth;

/* traceTime.c */

extern int    timeInit(void);
extern double timeElapsed(void);

#endif

#endif
