#ifndef SPINNER_HEADER
#define SPINNER_HEADER

#include "timer.h"

/* Spinner module for easy spinning.
   Use:
    1. Call spinInit(degPerSec, rotx, roty, rotz) in your initialization function.
        degPerSec: Number of degrees to rotate per second.
        rotx, roty, rotz: The axes to rotate around.  Ex. rotx=0, roty=1, rotz=0 will
        rotation around the positive y axis.
    2. Call spinStart() to start spin/rotations.
    3. Call spinStop() to pauce the spin.
    4. In your display function, put spinRotate() before your model's draw calls,
        but in between glPushMatrix() and glPopMatrix().  This function will modify the
        GL modelview matrix.
    5. SpinPause() SpinUnPause() will pause and unpause the spinner , respectively.  If
        the spinner is not active, these functions have no effect.

   Limitations:
    Registers its own update function for simplicity, so user can't have a user-defined update function.
    Must be used exlusively with GLUT.
    
*/
      
    

void spinInit( float degPerSec, float rotx, float roty, float rotz );

void spinStart( void );

void spinStop( void );

void spinRotate( void );

int spinIsActive( void );

void spinOffsetSpeed( float );

void spinChangeSpeed( float );

void spinPause( void );

void spinUnPause( void );

#endif

