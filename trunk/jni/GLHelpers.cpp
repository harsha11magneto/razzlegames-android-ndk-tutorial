

#include <jni.h>
#include <GLES/gl.h>
#include <math.h>
#include <new>
#include <zip.h>
#include "def.h"
#include "utils.h"
#include "GLHelpers.h"


#include <EGL/egl.h>
//#include <GLES2/gl2.h>
//#include <GLES2/gl2ext.h>

#include "importgl.h"

#include "Renderer.h"
#include <Box2D/Box2D.h>


void printGLString(const char *name, GLenum s) {
    // fprintf(stderr, "printGLString %s, %d\n", name, s);
    const char *v = (const char *) glGetString(s);
    // int error = glGetError();
    // fprintf(stderr, "glGetError() = %d, result of glGetString = %x\n", error,
    //        (unsigned int) v);
    // if ((v < (const char*) 0) || (v > (const char*) 0x10000))
    //    fprintf(stderr, "GL %s = %s\n", name, v);
    // else
    //    fprintf(stderr, "GL %s = (null) 0x%08x\n", name, (unsigned int) v);
    fprintf(stderr, "GL %s = %s\n", name, v);
}

void checkEglError(const char* op, EGLBoolean returnVal = EGL_TRUE) 
{
  //    if (returnVal != EGL_TRUE) 
  //    {
  //        fprintf(stderr, "%s() returned %d\n", op, returnVal);
  //    }
  //
  //    for (EGLint error = eglGetError(); error != EGL_SUCCESS; error
  //            = eglGetError()) {
  //        fprintf(stderr, "after %s() eglError %s (0x%x)\n", op, strerror(error),
  //                error);
  //    }
}

void checkGlError(const char* op) {
  //    for (GLint error = glGetError(); error; error
  //            = glGetError()) {
  //        fprintf(stderr, "after %s() glError (0x%x)\n", op, error);
  //    }
}


