package com.example.Monkey.Poop;

import java.lang.Exception;
import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGL11;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;
import javax.microedition.khronos.egl.EGLSurface;
import javax.microedition.khronos.opengles.GL;
import javax.microedition.khronos.opengles.GL10;
import javax.microedition.khronos.opengles.GL11;
import android.opengl.*;
import javax.microedition.khronos.opengles.GL11Ext;

import java.lang.Exception;

import java.nio.FloatBuffer;
import java.nio.ShortBuffer;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import android.content.Context;
import android.graphics.Color;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.Point;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.provider.MediaStore;
import android.util.Log;
import java.nio.ByteOrder;
import java.nio.ByteBuffer;


/**
 *   Just a wrapper for creating textures and sending to native
 */

public class Texture
{

  static GL10 gl_context = null;

  private Bitmap bitmap = null;

  //**************************************************************************
  /**
   *  Keep OpenGL context for application (will change)
   */

  static public void setGlContext(GL10 gl)
  {

    gl_context = gl;
  }

  //**************************************************************************
  /** Loads the resource to memory
   *
   */

  static public int glLoadAlphaStatic(String file) throws java.io.IOException
  {

    if(gl_context == null)
    {

      Log.e("glLoadAlphaStatic(" + file + ")", " gl_context was null!\n");
      return -1;

    }

    GL10 gl = gl_context;
    
    Bitmap bitmap = null;
    try
    {

      bitmap = ResourceLoadingTools.loadImage(file);
    }
    catch(java.io.FileNotFoundException e)
    {
      Log.e("ERROR",
          "---------------------------------------------------------------\n");
      Log.e("ERROR", "Could not FIND image: " + file +
          " from apk file!\n");
      Log.e("ERROR", 
          "---------------------------------------------------------------\n");

      // Rethrow so application fails with better stack trace
      e.printStackTrace();
      throw e;
      //return -1;
    }
    catch(java.io.IOException e)
    {
      Log.e("ERROR",
          "---------------------------------------------------------------\n");
      Log.e("ERROR", "Could not load image: " + file +
          " from apk file!\n");
      Log.e("ERROR", 
          "---------------------------------------------------------------\n");
      // Rethrow so application fails with better stack trace
      e.printStackTrace();
      throw e;
      //return -1;
    }

    Log.e("SUCCESS",
        "---------------------------------------------------------------\n");
    Log.v("SUCCESS", "Loaded file: " + file + "!\n");
    Log.e("SUCCESS",
        "---------------------------------------------------------------\n");


    int textureName = -1;
    int[] texture = new int[1];
    gl.glGenTextures(1, texture, 0);
    textureName = texture[0];

    //Log.d(TAG, "Generated texture: " + textureName);
    gl.glBindTexture(GL10.GL_TEXTURE_2D, textureName);
    gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_MIN_FILTER, GL10.GL_NEAREST);
    gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_MAG_FILTER, GL10.GL_LINEAR);
    gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_WRAP_S,
        GL10.GL_CLAMP_TO_EDGE);
    gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_WRAP_T,
        GL10.GL_CLAMP_TO_EDGE);
    //gl.glTexEnvf(GL10.GL_TEXTURE_ENV, GL10.GL_TEXTURE_ENV_MODE, GL10.GL_REPLACE);
    gl.glTexEnvf(GL10.GL_TEXTURE_ENV, GL10.GL_TEXTURE_ENV_MODE, GL10.GL_MODULATE);

    ByteBuffer image_buff = ByteBuffer.allocateDirect(
        bitmap.getHeight() * bitmap.getWidth() * 4);
    image_buff.order(ByteOrder.nativeOrder());
    byte buffer[] = new byte[4];

    for(int y = 0; y < bitmap.getHeight(); y++)
    {

      for(int x = 0; x < bitmap.getWidth(); x++)
      {

        int color = bitmap.getPixel(x, y);
        buffer[0] = (byte)Color.red(color);
        buffer[1] = (byte)Color.green(color);
        buffer[2] = (byte)Color.blue(color);
        buffer[3] = (byte)Color.alpha(color);
        image_buff.put(buffer);

      }

    }

    image_buff.position(0);
    gl.glTexImage2D(GL10.GL_TEXTURE_2D, 0, GL10.GL_RGBA,
        bitmap.getWidth(), bitmap.getHeight(), 0, 
        GL10.GL_RGBA, GL10.GL_UNSIGNED_BYTE, image_buff);

    //GLUtils.texImage2D(GL10.GL_TEXTURE_2D, 0, bitmap, 0);

    //    mCropWorkspace[0] = 0;
    //    mCropWorkspace[1] = bitmap.getHeight();
    //    mCropWorkspace[2] = bitmap.getWidth();
    //    mCropWorkspace[3] = -bitmap.getHeight();
    //
    //    ((GL11) gl).glTexParameteriv(GL10.GL_TEXTURE_2D, 
    //      GL11Ext.GL_TEXTURE_CROP_RECT_OES, mCropWorkspace, 0);

    int error = gl.glGetError();
    if (error != GL10.GL_NO_ERROR)
    { 

      Log.e(Logging.TAG, "GL Texture Load Error: " + error);
      return textureName;
    }

    int width = bitmap.getWidth();
    int height = bitmap.getHeight();

    // Reclaim bitmap memory
    bitmap.recycle();
    bitmap = null;

    Log.e("SUCCESS",
        "---------------------------------------------------------------\n");
    Log.v("SUCCESS", "Loaded file as texture: " + textureName + "!\n");
    Log.e("SUCCESS",
        "---------------------------------------------------------------\n");


    //Log.d(TAG, "Loaded texture: " + textureName);
    return textureName;
  }


  //  //**************************************************************************
  //  /** Loads the resource to memory
  //   *
  //   */
  //
  //  public boolean glLoadAlpha( GL10 gl) 
  //  {
  //
  //    /*many thanks to sprite method test if this works*/
  //    if ( gl == null )
  //    {
  //      Log.e(Logging.TAG, "Failed to load resource.  Context/GL is NULL");
  //      return false;
  //    }
  //
  //    /*many thanks to sprite method test if this works*/
  //    if ( bitmap == null )
  //    {
  //      Log.e(Logging.TAG, "Failed to load texture to GPU .  "+
  //          "Texture bitmap was NULL!");
  //      return false;
  //    }
  //
  //
  //    if(textureInVRAM())
  //    {
  //
  //      glDelete(gl);
  //    }
  //
  //    int error;
  //
  //    int textureName = -1;
  //    gl.glGenTextures(1, texture, 0);
  //    textureName = texture[0];
  //
  //    //Log.d(TAG, "Generated texture: " + textureName);
  //    gl.glBindTexture(GL10.GL_TEXTURE_2D, textureName);
  //    gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_MIN_FILTER, GL10.GL_NEAREST);
  //    gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_MAG_FILTER, GL10.GL_LINEAR);
  //    gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_WRAP_S,
  //        GL10.GL_CLAMP_TO_EDGE);
  //    gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_WRAP_T,
  //        GL10.GL_CLAMP_TO_EDGE);
  //    //gl.glTexEnvf(GL10.GL_TEXTURE_ENV, GL10.GL_TEXTURE_ENV_MODE, GL10.GL_REPLACE);
  //    gl.glTexEnvf(GL10.GL_TEXTURE_ENV, GL10.GL_TEXTURE_ENV_MODE, GL10.GL_MODULATE);
  //
  //    ByteBuffer image_buff = ByteBuffer.allocateDirect(
  //        bitmap.getHeight() * bitmap.getWidth() * 4);
  //    image_buff.order(ByteOrder.nativeOrder());
  //    byte buffer[] = new byte[4];
  //
  //    for(int y = 0; y < bitmap.getHeight(); y++)
  //    {
  //
  //      for(int x = 0; x < bitmap.getWidth(); x++)
  //      {
  //
  //        int color = bitmap.getPixel(x, y);
  //        buffer[0] = (byte)Color.red(color);
  //        buffer[1] = (byte)Color.green(color);
  //        buffer[2] = (byte)Color.blue(color);
  //        buffer[3] = (byte)Color.alpha(color);
  //        image_buff.put(buffer);
  //
  //      }
  //
  //    }
  //
  //    image_buff.position(0);
  //    gl.glTexImage2D(GL10.GL_TEXTURE_2D, 0, GL10.GL_RGBA,
  //        bitmap.getWidth(), bitmap.getHeight(), 0, 
  //        GL10.GL_RGBA, GL10.GL_UNSIGNED_BYTE, image_buff);
  //
  //    //GLUtils.texImage2D(GL10.GL_TEXTURE_2D, 0, bitmap, 0);
  //
  //    //    mCropWorkspace[0] = 0;
  //    //    mCropWorkspace[1] = bitmap.getHeight();
  //    //    mCropWorkspace[2] = bitmap.getWidth();
  //    //    mCropWorkspace[3] = -bitmap.getHeight();
  //    //
  //    //    ((GL11) gl).glTexParameteriv(GL10.GL_TEXTURE_2D, 
  //    //      GL11Ext.GL_TEXTURE_CROP_RECT_OES, mCropWorkspace, 0);
  //
  //    error = gl.glGetError();
  //    if (error != GL10.GL_NO_ERROR)
  //    { 
  //
  //      Log.e(Logging.TAG, "GL Texture Load Error: " + error);
  //      return false;
  //    }
  //
  //    width = bitmap.getWidth();
  //    height = bitmap.getHeight();
  //
  //    // Reclaim bitmap memory
  //    bitmap.recycle();
  //
  //    bitmap = null;
  //
  //    //Log.d(TAG, "Loaded texture: " + textureName);
  //    return true;
  //  }


  //  //**************************************************************************
  //  /** Loads the resource to memory
  //   *
  //   *  @return texture handle
  //   */
  //
  //  public int glLoad( GL10 gl) 
  //  {
  //
  //    /*many thanks to sprite method test if this works*/
  //    if ( gl == null )
  //    {
  //      Log.e(Logging.TAG, "Failed to load resource.  Context/GL is NULL");
  //      return 0;
  //    }
  //
  //    /*many thanks to sprite method test if this works*/
  //    if ( bitmap == null )
  //    {
  //      Log.e(Logging.TAG, "Failed to load texture to GPU .  "+
  //          "Texture bitmap was NULL!");
  //      return 0;
  //    }
  //
  //    if(textureInVRAM())
  //    {
  //
  //      glDelete(gl);
  //    }
  //
  //    int error;
  //
  //    int textureName = -1;
  //    gl.glGenTextures(1, texture, 0);
  //    textureName = texture[0];
  //
  //    gl.glEnable(GL10.GL_TEXTURE_2D);
  //
  //    //Log.d(TAG, "Generated texture: " + textureName);
  //    gl.glBindTexture(GL10.GL_TEXTURE_2D, textureName);
  //    gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_MIN_FILTER, GL10.GL_NEAREST);
  //    gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_MAG_FILTER, GL10.GL_LINEAR);
  //    gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_WRAP_S,
  //        GL10.GL_CLAMP_TO_EDGE);
  //    gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_WRAP_T,
  //        GL10.GL_CLAMP_TO_EDGE);
  //    //gl.glTexEnvf(GL10.GL_TEXTURE_ENV, GL10.GL_TEXTURE_ENV_MODE, GL10.GL_REPLACE);
  //    gl.glTexEnvf(GL10.GL_TEXTURE_ENV, GL10.GL_TEXTURE_ENV_MODE, GL10.GL_MODULATE);
  //
  //    GLUtils.texImage2D(GL10.GL_TEXTURE_2D, 0, bitmap, 0);
  //
  //    //    mCropWorkspace[0] = 0;
  //    //    mCropWorkspace[1] = bitmap.getHeight();
  //    //    mCropWorkspace[2] = bitmap.getWidth();
  //    //    mCropWorkspace[3] = -bitmap.getHeight();
  //    //
  //    //    ((GL11) gl).glTexParameteriv(GL10.GL_TEXTURE_2D, 
  //    //      GL11Ext.GL_TEXTURE_CROP_RECT_OES, mCropWorkspace, 0);
  //
  //    error = gl.glGetError();
  //    if (error != GL10.GL_NO_ERROR)
  //    { 
  //
  //      Log.e(Logging.TAG, "GL Texture Load Error: " + error);
  //      return 0;
  //    }
  //
  //    width = bitmap.getWidth();
  //    height = bitmap.getHeight();
  //
  //    // Reclaim bitmap memory
  //    bitmap.recycle();
  //
  //    bitmap = null;
  //
  //    gl.glDisable(GL10.GL_TEXTURE_2D);
  //
  //    //Log.d(TAG, "Loaded texture: " + textureName);
  //    return textureName;
  //  }

  //  //**************************************************************************
  //  void draw(GL10 gl, FloatBuffer verts, int vert_size, FloatBuffer tex,
  //      int tex_size, ShortBuffer quad_index_buff, int quad_index_size)
  //  {
  //
  //
  //    if(texture[0] < 0)
  //    {
  //
  //      Log.v(Logging.TAG, "GL Texture was < 0!!");
  //      if(bitmap == null)
  //      {
  //        Log.e(Logging.TAG, "There was an issue reloading textures!!");
  //        return;
  //      }
  //
  //      glLoad(gl);
  //    }
  //
  //    gl.glDisableClientState(GL10.GL_NORMAL_ARRAY);
  //    gl.glDisableClientState(GL10.GL_COLOR_ARRAY);
  //
  //    gl.glEnable(GL10.GL_TEXTURE_2D);
  //    gl.glBindTexture( GL10.GL_TEXTURE_2D, texture[0]);
  //
  //    gl.glEnableClientState(GL10.GL_TEXTURE_COORD_ARRAY);
  //    gl.glEnableClientState(GL10.GL_VERTEX_ARRAY);
  //
  //    //gl.glFrontFace(GL10.GL_CW);
  //    gl.glTexCoordPointer( 2, GL10.GL_FLOAT, 0, tex );
  //    gl.glEnable(GL10.GL_TEXTURE_2D);
  //    //gl.glDisable(GL10.GL_TEXTURE_2D);
  //
  //    //gl.glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
  //    gl.glVertexPointer( 3, GL10.GL_FLOAT, 0, verts);
  //
  //    //    gl.glDrawElements( GL10.GL_TRIANGLES, _Indices.length,
  //    //        GL10.GL_UNSIGNED_SHORT, _IndexBuffer );
  //    //Log.e(Logging.TAG, "verts to display: "+ vert_size);
  //    //gl.glDrawArrays(GL10.GL_TRIANGLE_STRIP, 0, vert_size/3);
  //
  //    gl.glDrawElements(GL10.GL_TRIANGLES, quad_index_size, 
  //        GL10.GL_UNSIGNED_SHORT, quad_index_buff);
  //
  //    gl.glDisableClientState(GL10.GL_VERTEX_ARRAY);
  //    gl.glDisableClientState(GL10.GL_TEXTURE_COORD_ARRAY);
  //    gl.glDisable(GL10.GL_TEXTURE_2D);
  //  }

}

