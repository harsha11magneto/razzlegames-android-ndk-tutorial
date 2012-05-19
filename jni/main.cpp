#include <jni.h>
#include <GLES/gl.h>
#include <math.h>
#include <new>
#include <zip.h>
#include "def.h"
#include "utils.h"
#include "GLHelpers.h"

#include "Texture.h"
#include "AndroidJNIHelper.h"

//#include "importgl.h"

#include <unistd.h>
#include <EGL/egl.h>
//#include <GLES2/gl2.h>
//#include <GLES2/gl2ext.h>


#include "Sprite.h"
#include "Renderer.h"
#include <Box2D/Box2D.h>

int width = 0;
int height = 0;


static void loadAPK (const char* apkPath) {
  LOGI("Loading APK %s", apkPath);
  zip* APKArchive = zip_open(apkPath, 0, NULL);
  if (APKArchive == NULL) {
    LOGE("Error loading APK");
    return;
  }

  //Just for debug, print APK contents
  int numFiles = zip_get_num_files(APKArchive);
  for (int i=0; i<numFiles; i++) {
    const char* name = zip_get_name(APKArchive, i, 0);
    if (name == NULL) {
      LOGE("Error reading zip file name at index %i : %s", zip_strerror(APKArchive));
      return;
    }
    LOGI("File %i : %s\n", i, name);
  }
}


//*****************************************************************************
/**
 */

void native_initializeGL()
{

  //  printGLString("Version", GL_VERSION);
  //  printGLString("Vendor", GL_VENDOR);
  //  printGLString("Renderer", GL_RENDERER);
  //  printGLString("Extensions", GL_EXTENSIONS);

  glClearColor(1.0f, 0.0f, 0.0f, 0.5f);
  //glEnable(GL_CULL_FACE);
  glDisable(GL_CULL_FACE);
  glFrontFace(GL_CW);

  glShadeModel(GL_SMOOTH);
  //glDisable(GL_LIGHTING);

}


//*****************************************************************************
/**
 */

void parseAPKDetails( JNIEnv* env, jstring apk_path)
{

  const char* str;
  jboolean isCopy;
  str = env->GetStringUTFChars(apk_path, &isCopy);
  loadAPK(str);

  AndroidJNIHelper& jni_helper = AndroidJNIHelper::getJNIHelper();
  jni_helper.setJNIEnv(env);

}

GLfloat m_glMat[16];
b2World *m_world = NULL;
b2Body *m_bodyList = NULL;

void InitPhysics()
{

  LOGI("InitPhysics() called\n");
	m_world = new b2World(b2Vec2(0.0f, -9.81f), true);

  //  float *boxGeometry = new float[8];
  //  boxGeometry[0] = 1.0f; boxGeometry[1] = 0.0f; boxGeometry[2] = 1.0f;
  //  boxGeometry[3] = 1.0f;
  //  boxGeometry[4] = 0.0f; boxGeometry[5] = 1.0f; boxGeometry[6] = 0.0f;
  //  boxGeometry[7] = 0.0f;


  // ground
  {
    b2BodyDef groundBodyDef;
    groundBodyDef.position = b2Vec2(0.0, 1.0f);

    Sprite* sprite = new Sprite();
    sprite->vertex.push_back(Vector2Df(50.0f, 0.0f));
    sprite->vertex.push_back(Vector2Df(50.0f, 1.0f));
    sprite->vertex.push_back(Vector2Df(-50.0f, 1.0f));
    sprite->vertex.push_back(Vector2Df(-50.0f, 0.0f));

    sprite->texture_coords.push_back(Vector2Df(1.0f, 0.0f));
    sprite->texture_coords.push_back(Vector2Df(1.0f, 1.0f));
    sprite->texture_coords.push_back(Vector2Df(0.0f, 1.0f));
    sprite->texture_coords.push_back(Vector2Df(0.0f, 0.0f));

    groundBodyDef.userData = sprite;

    b2Body* ground = m_world->CreateBody(&groundBodyDef);

    //ground geometry
    b2PolygonShape shape;
    shape.SetAsBox(50.0f, 1.0f);
    //shape.SetAsEdge(b2Vec2(-12.0f, -7.0f), b2Vec2(12.0f, -7.0f));
    ground->CreateFixture(&shape, 0.0f);

  }

  // box
  {

    b2Vec2 vertices[] = { b2Vec2(2.0f, 0.0f), b2Vec2(2.0f, 2.0f),
      b2Vec2(0.0f, 2.0f), b2Vec2(0.0f, 0.0f) };
    b2PolygonShape shape;
    shape.Set(vertices, 4);

    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.userData = NULL;

    for (int i = 0; i < 5; i++)
    {

      Sprite* sprite = new Sprite();
      sprite->vertex.push_back(Vector2Df(2.0f, 0.0f));
      sprite->vertex.push_back(Vector2Df(2.0f, 2.0f));
      sprite->vertex.push_back(Vector2Df(0.0f, 2.0f));
      sprite->vertex.push_back(Vector2Df(0.0f, 0.0f));

      sprite->texture_coords.push_back(Vector2Df(1.0f, 0.0f));
      sprite->texture_coords.push_back(Vector2Df(1.0f, 1.0f));
      sprite->texture_coords.push_back(Vector2Df(0.0f, 1.0f));
      sprite->texture_coords.push_back(Vector2Df(0.0f, 0.0f));

      // Save our custom sprite in Box2D body definition
      bd.userData = sprite;


      bd.position = b2Vec2(1.0f * i, 20.0f+ .2f*i);
      //bd.position = b2Vec2(-5.0f + i * 2, 30.0f);
      //bd.position.Set(5.0f + 4 * 0.5f, 4.0f + 3*4);
      //bd.position = b2Vec2(5.0f + i * 0.5f, 4.0f + 3*i);
      //bd.position = b2Vec2(5.0f + i * 0.5f, 4.0f + 3*i);
      bd.angle = M_PI / (float)(i + 1);
      b2Body *box = m_world->CreateBody(&bd);
      box->CreateFixture(&shape, 1.0f);

    }

  }

}

#ifdef __cplusplus
extern "C" 
{
#endif


  //*****************************************************************************
  /**
   */

  JNIEXPORT void JNICALL Java_com_example_Monkey_Poop_MyRenderer_initializeGL(
      JNIEnv* env, jclass cls)
  {

    LOGD("Java_com_example_Monkey_Poop_MyRenderer_initializeGL called\n");

    //importGLInit();
    //parseAPKDetails(env, apk_path);

    sleep(1);

    AndroidJNIHelper& jni_helper = AndroidJNIHelper::getJNIHelper();
    jni_helper.setJNIEnv(env);

    glClearColor(1.0f, 0.0f, 0.0f, 0.5f);
    glFrontFace(GL_CW);     

    native_initializeGL();

    InitPhysics();

    Texture::loadTexture("box.png");
  }

  JNIEXPORT void JNICALL Java_com_example_Monkey_Poop_MyRenderer_resizeGL(
      JNIEnv* env, jobject obj, jint w, jint h)
  {

    //native_initializeGL();

    AndroidJNIHelper& jni_helper = AndroidJNIHelper::getJNIHelper();
    jni_helper.setJNIEnv(env);

    glViewport(0, 0, w, h);
    checkGlError("glViewport");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect = (float)w / (float)h;
    width = (float)w;
    height = (float)h;
    //glOrthof(-10.0f * aspect, 10.0f * aspect, -10.0f, 10.0f, 0.1f, 10.0f);
    glOrthof(0, aspect*40.0f, 0, 40.0f, -1.0f, 1.0f);
    //gluPerspective(45.0f, (float)w / (float)h, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //glTranslatef(0.0f, 0.0f, -20.0f);

  }

  Renderer renderer;

  //*****************************************************************************

  JNIEXPORT void JNICALL Java_com_example_Monkey_Poop_MyRenderer_paintGL(JNIEnv* env)
  {

    AndroidJNIHelper& jni_helper = AndroidJNIHelper::getJNIHelper();
    jni_helper.setJNIEnv(env);

    Renderer::drawFrame();
  }

#ifdef __cplusplus
}
#endif
