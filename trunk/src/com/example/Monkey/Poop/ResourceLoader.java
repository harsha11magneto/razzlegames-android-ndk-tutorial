package com.example.Monkey.Poop;

import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Rect;
import android.os.Handler;
import android.os.SystemClock;
import android.util.Log;
import android.view.Display;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.graphics.Rect;


import java.io.InputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import android.content.Context;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.Point;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.provider.MediaStore;
import android.util.Log;
import android.content.res.Resources;
import android.content.res.AssetManager;
import android.app.Application;


class ResourceLoadingTools
{

  private static Application application = null;

  //**************************************************************************
  /**
   */

  public static void setApplication(Application a)
  {

    application = a;
  }

  //**************************************************************************
  /**
   *   Load background resource
   *
   *   @param resource_id from apk file stuff .
   *   @param screen_size current android screen size.
   *   @param r_loader the Service/Context etc that has access to the image
   *   resources in apk file.
   *
   *   @return scaled background bitmap for android screen
   *
   */

  public static Bitmap loadBackground(int resource_id, 
      Vector2Df screen_size, Resources res)
  {

    BitmapFactory.Options opts = new BitmapFactory.Options();

    opts.outWidth = (int)screen_size.x;
    opts.outHeight = (int)screen_size.y;
    opts.inJustDecodeBounds = true;
    BitmapFactory.decodeResource(res, resource_id, opts);

    //    // compute the smallest size bitmap we need to read
    //    int w = opts.outWidth;
    //    int h = opts.outHeight;
    //    int s = 1;
    //    while(true) 
    //    {
    //      if((w/2 < maxDim) || (h/2 < maxDim)){
    //        break;
    //      }
    //      w /= 2;
    //      h /= 2;
    //      s++;
    //    }
    //
    // scale and read the data
    opts.inJustDecodeBounds = false;
    //opts.inSampleSize = 1;
    //opts.inPreferredConfig = Bitmap.Config.RGB_565;
    opts.inScaled = false;

    //    background_bm = BitmapFactory.decodeStream(getResources(), 
    //        resource_id);
    Bitmap bmp = BitmapFactory.decodeResource(res, 
        resource_id, opts);
    if(bmp == null)
    {
      Log.v(Logging.TAG, "Image returned by BitmapFactory is null!");
      return null;
    }

    return scaleBgBitmap(bmp, screen_size);

  }

  //**************************************************************************
  private static Bitmap scaleBgBitmap(Bitmap b, Vector2Df screen_size)
  {

    Bitmap result = null;
    int bw = b.getWidth();
    int bh = b.getHeight();
    double s = (double)screen_size.y / (double)bh;
    int newW = (int)(bw * s);
    if(newW < screen_size.x)
    {
      newW = (int)screen_size.x;
    }
    result = Bitmap.createScaledBitmap(b, newW, (int)screen_size.y, false);
    return(result);
  }

  //**************************************************************************
  /**
   *   Load image resource, as is (no scaling)
   *
   *   @param file_name name of file to load
   *
   *   @return image loaded
   */

  public static Bitmap loadImage(String file_name) throws java.io.IOException
  {

    AssetManager am = application.getAssets();
    InputStream stream = am.open(file_name);

    Bitmap bmp = BitmapFactory.decodeStream(stream);

    return bmp;

  }


  //**************************************************************************
  /**
   *   Load image resource, as is (no scaling)
   *
   *   @param resource_id from apk file stuff .
   *   @param r_loader the Service/Context etc that has access to the image
   *   resources in apk file.
   *
   *   @return scaled background bitmap for android screen
   *
   */

  public static Bitmap loadImage(int resource_id, 
      Resources res)
  {

    BitmapFactory.Options opts = new BitmapFactory.Options();

    opts.inJustDecodeBounds = true;
    BitmapFactory.decodeResource(res, resource_id, opts);

    // scale and read the data
    opts.inJustDecodeBounds = false;
    opts.inSampleSize = 4;
    opts.inPreferredConfig = Bitmap.Config.ARGB_4444;

    //    background_bm = BitmapFactory.decodeStream(getResources(), 
    //        resource_id);
    Bitmap bmp = BitmapFactory.decodeResource(res,
        resource_id, opts);
    if(bmp == null)
    {
      Log.v(Logging.TAG, "Image returned by BitmapFactory is null!");
      return null;
    }

    return bmp;

  }

}
