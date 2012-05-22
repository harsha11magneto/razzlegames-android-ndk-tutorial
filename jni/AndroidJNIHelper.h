
#ifndef ANDROIDJNIHELPER_H
#define ANDROIDJNIHELPER_H 

#include <string>
#include <jni.h>
#include <GLES/gl.h>
#include <math.h>
#include <new>
#include <zip.h>
#include "def.h"
#include "GLHelpers.h"


/**
 *   @file AndroidJNIHelper.cpp
 *    
 *
 *    Create an easy to use way to grab jni environment
 *    
 *    JNI method and constructor signature cheat sheet
 *
 *  B=byte
 *  C=char
 *  D=double
 *  F=float
 *  I=int
 *  J=long
 *  S=short
 *  V=void
 *  Z=boolean
 *  Lfully-qualified-class=fully qualified class
 *  [type=array of type>
 *  (argument types)return type=method type. 
 *     If no arguments, use empty argument types: (). 
 *     If return type is void (or constructor) use (argument types)V.*    
 *
 *     Example
 *     @code
 *     constructor:
 *     (String s)
 *
 *     translates to:
 *     (Ljava/lang/String;)V
 *
 *     method:
 *     String toString()
 *
 *     translates to:
 *     ()Ljava/lang/String;
 *
 *     method:
 *     long myMethod(int n, String s, int[] arr)
 *
 *     translates to:
 *     (ILjava/lang/String;[I)J
 *     @endcode
 *
 */

//*****************************************************************************
/**
 *   Singleton class for helping interface with Java Native Interface
 */

class AndroidJNIHelper
{

  private: 

    /// The current JNI context
    JNIEnv* jni_env;

    const char* java_package_path;

    AndroidJNIHelper():
      jni_env(NULL)
  {

  }

  public:
    static AndroidJNIHelper& getJNIHelper()
    {

      static const char JAVA_PACKAGE_PATH[] = "com/example/Monkey/Poop/";
      static AndroidJNIHelper a;
      a.java_package_path = JAVA_PACKAGE_PATH;
      return a;

    }

    std::string getJavaPackagePath()
    {

      return (std::string)java_package_path;
    }

    void setJNIEnv(JNIEnv* env)
    {

      jni_env = env;
    }

    JNIEnv* getJNIEnv()
    {

      return jni_env;
    }

    int jniLoadTexture(const char* s);


};


#endif /* ANDROIDJNIHELPER_H */
