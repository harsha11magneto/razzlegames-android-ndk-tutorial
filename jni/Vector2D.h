/* vim: set filetype=cpp.doxygen : */
#ifndef VECTOR2D_H
#define VECTOR2D_H 

#include <vector>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <cmath>



// TODO, CREATE THIS THING

template<typename T>
class Vector2D
{

  public:

  typedef enum {
    X_CORD=0,Y_CORD=1}cords;

  /// XCord of Vector
  T x;
  /// YCord of Vector
  T y;

  Vector2D();
  Vector2D(T x, T y);

  //---------------------------------------------
  // Operators
  //---------------------------------------------
  Vector2D<T> operator+(const Vector2D<T>);
  Vector2D<T>  operator-(void);
  Vector2D<T>  operator- (const Vector2D<T> v2);
  Vector2D<T> operator*(const Vector2D<T>);

  Vector2D<T>  operator/(const T n);
  Vector2D<T>  operator/=(const T n);

  template<typename R, typename M>
    friend Vector2D<R> operator*(Vector2D<R> v, const M s);
  template<typename R, typename M>
    friend Vector2D<R> operator*=(Vector2D<R>& v, const M s);
  template<typename R, typename M>
    friend Vector2D<R> operator*(const M s, Vector2D<R> v);


  bool operator==(const Vector2D<T> v);
  bool operator!=(const Vector2D<T> v)
  {
    return !equal(v);

  }
  Vector2D<T>& operator+=(const Vector2D<T> v2);
  Vector2D<T>& operator-=(const Vector2D<T> v2);
  Vector2D<T> operator*=(const Vector2D<T>);

  // Array like access to attributes (for convenience)
  T& operator[](int i);
  T& getCord(unsigned int i);

  template<typename R>
    friend std::ostream& operator<<(
        std::ostream& o, const Vector2D<R> v);


  bool equal(const Vector2D<T> v);

  T magnitude();

  T length();

  std::string toString();
};

//**********************************************************
/**
 */
template<typename T>
Vector2D<T>::Vector2D():
    x(0),
    y(0)
{

}


//**********************************************************
/**
 *   @param x cord
 *   @param y cord
 */
template<typename T>
Vector2D<T>::Vector2D(T x_, T y_):
    x(x_),
    y(y_)
{

}


//**********************************************************************
/**
 * Array like access to attributes (for convenience)
 *
 * @param i index into Vector (x=0,y=1)
 */
  template<typename T>
inline T& Vector2D<T>::operator[](int i)
{

  return getCord(i);

}

//**********************************************************
/**
 * Get the cordinate of this vector in array like access
 *
 * @param i index into Vector (x=0,y=1)
 */
  template<typename T>
inline T& Vector2D<T>::getCord(unsigned int i) 
{

  if(i == X_CORD)
  {

    return x;
  }

  else if(i == Y_CORD)
  {

    return y;
  }

  else
  {

    printf("Vector2D[%d] Tried to access vector index that is"
        "out of bounds!", i);
    throw  i;
  }

}

//**********************************************************
template<typename T>
bool Vector2D<T>::equal(const Vector2D<T> v)
{
  return (x == v.x && y == v.y );
}

//**********************************************************
  template<typename T>
bool Vector2D<T>::operator==(const Vector2D<T> v)
{
  return equal(v);
}

//**********************************************************
/**
 * 		 adding of vectors
 * 			@param v1 first to add
 * 			@param v2 second
 * 		@return new vector
 */
  template<typename T>
Vector2D<T>  Vector2D<T>::operator+ (const Vector2D<T> v2)
{

  const Vector2D<T>& v1 = *(this);
  return Vector2D(v1.x+v2.x, v1.y+v2.y);
}

//**********************************************************
/**
 * 		 adding of vectors
 * 			@param v2 second
 * 		@return new vector
 */
  template<typename T>
Vector2D<T>&  Vector2D<T>::operator+= (const Vector2D<T> v2)
{

  *this = *this + v2;
  return *this;
}

//**********************************************************
/**
 * 		 subtraction of vectors
 * 			@param v2 second
 * 		@return new vector
 */
  template<typename T>
Vector2D<T>&  Vector2D<T>::operator-= (const Vector2D<T> v2)
{

  *this = *this - v2;
  return *this;
}


//**********************************************************
/**
 * 		 subtraction of vectors
 * 			@param v1 first to add
 * 			@param v2 second
 * 		@return new vector
 */
  template<typename T>
Vector2D<T>  Vector2D<T>::operator- (const Vector2D<T> v2)
{

  const Vector2D<T>& v1 = *(this);
  return Vector2D(v1.x-v2.x, v1.y-v2.y);
}

//**********************************************************
/**
 * 		 negation of vector
 * 		@return new vector
 */
  template<typename T>
Vector2D<T>  Vector2D<T>::operator- ()
{

  const Vector2D<T>& v1 = *(this);
  return Vector2D(-v1.x, -v1.y);
}


//**********************************************************
/**
 * 		 mult of vector with scalar
 * 			@param v1 first to add
 * 			@param v2 second
 * 		@return new vector scaled by s
 */
  template<typename T, typename M>
inline Vector2D<T> operator* (Vector2D<T> v, const M s)
{

  return Vector2D<T>(v.x*s,v.y*s);
}

//**********************************************************
/**
 * 		 mult of vector with scalar
 * 			@param v1 first to add
 * 			@param v2 second
 * 		@return new vector scaled by s
 */
  template<typename T, typename M>
inline Vector2D<T> operator*= (Vector2D<T>& v, const M s)
{

  v.x *= s;
  v.y *= s;
  return v;
}


//**********************************************************
/**
 * 		 mult of vector with scalar
 * 			@param v1 first to add
 * 			@param v2 second
 * 		@return new vector scaled by s
 */
  template<typename T, typename M>
inline Vector2D<T> operator*(const M s, Vector2D<T> v)
{

  return Vector2D<T>(v.x*s,v.y*s);

}
;
//**********************************************************
/**
 *  Friend function for printing Vector2D to output streams
 */

  template<typename T>
std::ostream& operator<< (std::ostream& o, const Vector2D<T> v)
{

  return o << "{" << v.x <<", "<<  v.y <<"} ";

}

//**********************************************************
/**
 *  Friend function for printing Vector3D to output streams
 */

template<typename T>
std::string Vector2D<T>::toString()
{

  std::ostringstream o; 
  
  o << "{" << x <<", "<<  y <<"} ";

  return o.str();

}


//************************************************************
/**
 * 	 Scalar division of vector by n
 */
  template<typename T>
Vector2D<T>  Vector2D<T>::operator/ (T n)
{
  return Vector2D(x/n, y/n);
}

//************************************************************
/**
 * 	 Scalar division of vector by n
 */
  template<typename T>
Vector2D<T>  Vector2D<T>::operator/= (const T n)
{
  x /= n;
  y /= n;
  return *this;
}

//**********************************************************
/**
 * 		 mult of vector with vector (used for color, mostly)
 * 			@param v1 first to mult
 * 			@param v2 second
 * 		@return new vector scaled by s
 */
  template<typename T>
inline Vector2D<T> Vector2D<T>::operator* (Vector2D<T> v)
{

  return Vector2D<T>(
      v.x * x,
      v.y * y);

}



typedef Vector2D<float> Vector2Df;
typedef Vector2D<int> Vector2Di;



#endif /* VECTOR2D_H */
