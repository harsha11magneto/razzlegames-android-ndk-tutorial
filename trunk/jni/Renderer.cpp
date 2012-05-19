#include <jni.h>
#include <GLES/gl.h>
#include <math.h>
#include <new>

#include <Box2D/Box2D.h>

#include "GLHelpers.h"
#include "Box2DTools.h"
#include "Renderer.h"
#include "def.h"

#include "Sprite.h"


extern GLfloat m_glMat[16];
extern b2World *m_world ;
extern b2Body *m_bodyList ;

extern int width;
extern int height;


//*****************************************************************************
/**
 */

void Renderer::drawFrame()
{

  static int frame_count = 0;


  glClearColor(1.0f, 0.0f, 0.0f, 0.5f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  checkGlError("glClear");
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // simulate physics
  m_world->Step(1.0f / 60.0f, 6, 2);
  m_world->ClearForces();

  // draw assets
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 1);

  static const GLfloat verts[] = 
  {
    0, 0, //0, 
    10, 0, //0,
    10, 10, //0,

  };


  glPushMatrix();
  glVertexPointer(2, GL_FLOAT, 0, verts);
  glColor4f(1.0f,1.0f,1.0f,1.0f);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  checkGlError("glDrawArrays");
  glPopMatrix();

  int i = 0;
  for(m_bodyList = m_world->GetBodyList(); m_bodyList != NULL;
      m_bodyList = m_bodyList->GetNext())
  {

    Box2dtoGL(m_glMat, m_bodyList->GetTransform());

    if(frame_count % 10 == 0)
    {

      b2Vec2 position = m_bodyList->GetPosition();
      LOGE("body %i position {%02f, %02f}\n", 
          i, 
          position.x, position.y);
      if(i == 0)
      {
        LOGE("width %d, height %d\n", width, height);
      }

    }


    Sprite* sprite = (Sprite*)m_bodyList->GetUserData();
    if(sprite == NULL)
    {

      LOGE("Sprite from Box2D body was NULL!\n");
      continue;
    }

    glPushMatrix();
    glMultMatrixf(m_glMat);
    glVertexPointer(2, GL_FLOAT, 0, &sprite->vertex[0]);
    glTexCoordPointer(2, GL_FLOAT, 0,&sprite->texture_coords[0]);
    glColor4f(1.0f,1.0f,1.0f,1.0f);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glPopMatrix();
    i++;

  }

  frame_count++;
  glDisableClientState(GL_VERTEX_ARRAY);

}

