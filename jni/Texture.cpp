#include "Texture.h"
#include "AndroidJNIHelper.h"

using namespace std;

/** Verts to be used for all quads, just uniform scale and all that */
const float quad_verts[] =
{

  // Bottom left
  0.0f, 0.0f,0.0f,

  // Top left
  0.0f, 1.0f, 0.0f,

  // Top right
  1.0f, 1.0f, 0.0f,

  // Bottom right
  1.0f, 0.0f, 0.0f,

};

/** Text coords to be used for all quads, just uniform scale and all that */
const float quad_tex[] =
{

  // Bottom left
  0.0f, 1.0f,

  // Top left
  0.0f, 0.0f, 

  // Top right
  1.0f, 0.0f, 

  // Bottom right
  1.0f, 1.0f, 

};

/** Text coords to be used for all quads, just uniform scale and all that */
const short quad_index[] =
{

  0, 1, 2,
  2, 3, 0,

};

//*****************************************************************************
/**
 *  Grab a image resource from apk file and load in OpenGL context and 
 *    create a Texture wrapper for it all.
 *
 * @return Texture object with valid texture ID or NULL
 */

Texture* Texture::createTexture(const char* filename)
{
  int id = loadTexture(filename);
  if(id > 0)
  {

    Texture* t = new Texture();
    t->texture_id = id;
    return t;
  }
  return NULL;

}



//*****************************************************************************
/**
 *  Grab a image resource from apk file and load in OpenGL context
 *
 *  @return texture ID from opengl context
 */

int Texture::loadTexture(const char* filename)
{

  if(filename == NULL)
  {

    LOGE("filename passed was NULL!\n");
    return -1;
  }
  LOGI("Texture::loadTexture(%s) called\n",
      filename);

  const char CLASS_NAME[]  = "Texture";
  const char METHOD_NAME[]  = "glLoadAlphaStatic";
  int texture_num = -1;
  AndroidJNIHelper helper = AndroidJNIHelper::getJNIHelper();
  JNIEnv* env = helper.getJNIEnv();
  if(env == NULL)
  {

    LOGE("JNIEnv was NULL!\n");
    return -1;
  }

  string class_path = helper.getJavaPackagePath() + CLASS_NAME;
  jclass cls = env->FindClass(class_path.c_str());
  LOGD("class_path: %s\n", class_path.c_str());

  jmethodID mid = env->GetStaticMethodID(cls, 
      METHOD_NAME,
      "(Ljava/lang/String;)I");

  if(mid == 0)
  {

    LOGE("Unable to load method: %s:%s\n",
        CLASS_NAME,
        METHOD_NAME);
    return -1;
  }

  jint ret_val = -1;
  jstring mystr = env->NewStringUTF(filename);
  ret_val = env->CallStaticIntMethod(cls, mid, mystr);
  return ret_val;

}

