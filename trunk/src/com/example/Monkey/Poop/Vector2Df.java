package com.example.Monkey.Poop;

public class Vector2Df
{

  float x;
  float y;

  Vector2Df()
  {
    x = 0.0f;
    y = 0.0f;

  }

  Vector2Df(float _x, float _y)
  {

    x = _x;
    y = _y;
  }

  //**************************************************************************
  Vector2Df add(Vector2Df v)
  {

    return new Vector2Df(v.x+x, v.y+y);
  }

  //**************************************************************************
  /**
   *  Make deep copy
   */

  Vector2Df copy()
  {

    Vector2Df c = new Vector2Df();
    c.x = x;
    c.y = y;
    return c;

  }

}
