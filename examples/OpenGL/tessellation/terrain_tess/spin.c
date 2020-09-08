#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef __APPLE__
# include <GLUT/glut.h>
#else
# include <GL/glut.h>
#endif

#include "spin.h"

static float _rotx, _roty, _rotz;   /* Axis to rotate */
float _degPerSec;                   /* Speed of rotation */

/* Timer variables */
static double _lastTime = -1;
static double _elapsedTime = -1;

static int _isActive = 0;  /* Whether spinner is ticking */

static float _currAngle;   /* The current angle */

void spinUpdate( void )
{
  _elapsedTime = _lastTime;

  _lastTime = timerElapsed();  /* Get elapsed time since init */

  _elapsedTime = _lastTime - _elapsedTime;

  _currAngle += _degPerSec * (_elapsedTime );

  _currAngle = fmod(_currAngle, 360.0f);

  glutPostRedisplay();
}

void spinPause( void )
{
  /* Pauses the rotation, but leaves the spinner active */
  glutIdleFunc(NULL);
}

void spinUnPause( void )
{
  /* If spinner is active, will reset the timer and restart rotation */
  if (spinIsActive())
    spinStart();
}

/* Prevents update being called when window is hidden from view */
void spinVisibility( int state )
{
  if (state == GLUT_NOT_VISIBLE)
    spinPause();
  else
    spinUnPause();
}

void spinInit( float speed, float rotx, float roty, float rotz )
{
  _rotx = rotx;
  _roty = roty;
  _rotz = rotz;

  _degPerSec = speed;

  _currAngle = 0.0f;
}

void spinOffsetSpeed( float offset )
{
  _degPerSec += offset;
}

void spinChangeSpeed( float speed )
{
  _degPerSec = speed;
}

void spinStart( void )
{
  timerInit(); /* Initialize the time */

  _lastTime = timerElapsed();

  _isActive = 1;

  glutIdleFunc( spinUpdate );
  glutVisibilityFunc( spinVisibility );
}

void spinStop( void )
{
  _isActive = 0;

  glutIdleFunc( NULL );
}

void spinRotate( void )
{
  glRotatef(_currAngle, _rotx, _roty, _rotz);
}

int spinIsActive( void )
{
  return _isActive;
}

