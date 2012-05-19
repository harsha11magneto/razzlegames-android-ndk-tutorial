
#include "AndroidJNIHelper.h"


int AndroidJNIHelper::jniLoadTexture(const char* s)
{

  JNIEnv *env = jni_env;
  jclass cls = env->FindClass("com/galcon/igalcon/Galcon");
  jmethodID mid = env->GetStaticMethodID(cls,
      "load_texture",
      "(Ljava/lang/String;)I");
  // there could be some exception handling happening here, but there isn't
  jint ret;
  jstring mystr = env->NewStringUTF(s);
  ret = env->CallStaticIntMethod(cls, mid, mystr);
  return ret;

}
