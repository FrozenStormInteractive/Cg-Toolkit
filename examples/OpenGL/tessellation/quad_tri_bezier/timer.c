#include <stdlib.h>
#include <stdio.h>

#include "timer.h"

static double timerRes = 0;

#ifdef _WIN32

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>

static LARGE_INTEGER timerStart;

int timerInit()
{
  LARGE_INTEGER freq;
  if( QueryPerformanceFrequency( &freq ) )
  {
    QueryPerformanceCounter( &timerStart );
    timerRes = 1.0/((double)freq.QuadPart);
    return 1;
  }
  else
  {
    printf("No high performance counter found\n");
    return 0;
  }
}

double timerElapsed()
{
  double elapsed;
  LARGE_INTEGER time;
  QueryPerformanceCounter( &time );
  elapsed = (double)(time.QuadPart - timerStart.QuadPart);
  return elapsed * timerRes;
}

#else /* non-Windows */

#include <sys/time.h>

long long timerStart = 0;

int timerInit()
{
  struct timeval val;
  gettimeofday( &val, NULL );
  timerRes = 0.000001;
  timerStart = (long long) val.tv_sec * (long long) 1000000 + (long long) val.tv_usec;
  return 1;
}

double timerElapsed()
{
  double elapsed;
  struct timeval val;
  gettimeofday( &val, NULL );
  elapsed = (double)(((long long) val.tv_sec * (long long) 1000000 + (long long) val.tv_usec) - timerStart);
  return elapsed * timerRes;
}

#endif

