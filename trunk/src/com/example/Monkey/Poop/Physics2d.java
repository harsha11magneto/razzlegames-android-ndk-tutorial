package com.example.Monkey.Poop;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.app.Activity;
import android.os.Bundle;
import android.opengl.GLSurfaceView;
import android.opengl.GLSurfaceView.Renderer;

import android.app.Application;
import android.app.Activity;
import android.content.Context;
import android.content.pm.ActivityInfo;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.content.res.AssetFileDescriptor;
import android.content.res.AssetManager;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.MotionEvent;
import android.util.Log;

import android.view.Display;
import android.view.Window;
import android.view.WindowManager;

import android.opengl.*;

public class Physics2d extends Activity
{

  private GLSurfaceView glSurface;
  private MyRenderer mRenderer;


  @Override 
  public void onCreate(Bundle savedInstanceState)
  {
    super.onCreate(savedInstanceState);

    glSurface = new GLSurfaceView(this);
    mRenderer = new MyRenderer(getApplication());
    glSurface.setRenderer(mRenderer);

    // Turn off app title
    requestWindowFeature(Window.FEATURE_NO_TITLE);

    //getWindow().setFlags(
    //WindowManager.LayoutParams.NO_STATUS_BAR_FLAG,
    //WindowManager.LayoutParams.NO_STATUS_BAR_FLAG);
    getWindow().setFlags(
        WindowManager.LayoutParams.FLAG_FULLSCREEN,
        WindowManager.LayoutParams.FLAG_FULLSCREEN);

    setContentView(glSurface);

    Display display = getWindowManager().getDefaultDisplay();

    Log.e("Screen Size", "Screen dimensions: {" +
        display.getWidth() + ", " +
        display.getHeight() +
        "}");
  }

  @Override
  public void onResume()
  {
    super.onResume();
    glSurface.onResume();
  }

  @Override 
  public void onPause()
  {
    super.onPause();
    glSurface.onPause();
  }

  static
  {
    System.loadLibrary("main");
  }
}

class MyRenderer implements Renderer
{

  Application application = null;
  private String apk_file = null;

  public MyRenderer(Application a)
  {

    application = a;
  }

  @Override
  public void onSurfaceCreated(GL10 gl, EGLConfig config)
  {

    Texture.setGlContext(gl);
    ResourceLoadingTools.setApplication(application);

    //    if(apk_file == null)
    //    {
    //
    //      apk_file = getAPKFilePath();
    //      if(apk_file == null)
    //      {
    //
    //        Log.e("ERROR", "Problem grabbing APK file\n");
    //        throw new RuntimeException("APK file for this app not found!\n");
    //      }
    //    }

    initializeGL();

  }

  public String getAPKFilePath()
  {

    if(application == null)
    {

      throw new RuntimeException("Application given to Renderer was null!");
    }

		// return apk file path (or null on error)
		String apkFilePath = null;
		ApplicationInfo appInfo = null;
		PackageManager packMgmr = application.getPackageManager();

		try 
    {

	    appInfo = packMgmr.getApplicationInfo("com.example.Monkey.Poop.Physics2d", 0);
    } 
    catch (NameNotFoundException e) 
    {

	    e.printStackTrace();
	    throw new RuntimeException("Unable to locate assets, aborting...");
    }

		apkFilePath = appInfo.sourceDir;
    //nativeInit(apkFilePath);

    return apkFilePath;
  }

  @Override
  public void onSurfaceChanged(GL10 gl, int width, int height)
  {

    Texture.setGlContext(gl);
    ResourceLoadingTools.setApplication(application);

    //Texture.glLoadAlphaStatic("box.png");

    gl.glViewport(0, 0, width, height);

    gl.glMatrixMode(GL10.GL_PROJECTION);
    gl.glLoadIdentity();
    float aspect = (float)width / (float)height;

    //gl.glOrthof(-10.0f * aspect, 10.0f * aspect, -10.0f, 10.0f, 0.1f, 10.0f);
    //gl.glOrthof(-10.0f , 10.0f , -10.0f, 10.0f, 0.1f, 10.0f);
    //GLU.gluOrtho2D(gl, 0.0f, (float)width,  0.0f, (float)height);
    //GLU.gluOrtho2D(gl, 0.0f, 10.0f, 0.0f, 10.0f);
    //gl.glOrthof(0.0f , 10.0f , 0.0f, 10.0f, -1f, 1f);
    //gluPerspective(45.0f, (float)w / (float)h, 0.1f, 100.0f);

    gl.glMatrixMode(GL10.GL_MODELVIEW);
    gl.glLoadIdentity();
    //gl.glTranslatef(0.0f, 0.0f, -20.0f);
    resizeGL(width, height);
  }

  @Override
  public void onDrawFrame(GL10 gl)
  {

    Texture.setGlContext(gl);
    ResourceLoadingTools.setApplication(application);

    paintGL(); 
    //eglSwapBuffers();
  }

  private native void initializeGL();
  private native void resizeGL(int w, int h);
  private native void paintGL();

  //private static native void nativeInit(String apkPath);
  //	private static native void nativeResize(int w, int h);
  //	private static native void nativeRender();

}
