
#ifndef GLHELPERS_H
#define GLHELPERS_H 

#include <jni.h>
#include <GLES/gl.h>
#include <math.h>
#include <new>
#include <zip.h>
#include "def.h"


#include <EGL/egl.h>
//#include <GLES2/gl2.h>
//#include <GLES2/gl2ext.h>


#include "Renderer.h"
#include <Box2D/Box2D.h>


void printGLString(const char *name, GLenum s);

void checkEglError(const char* op, EGLBoolean returnVal);


void checkGlError(const char* op);



#endif /* GLHELPERS_H */
