#ifndef TINYMATH_HPP
#define TINYMATH_HPP

#include <cmath>
#include <ostream>
#include "assert.h"

// Forward references of each of the structs
struct Vec2D;
struct Matrix3D;

//! Vec2D performs vector operations with 3-dimensions
// The purpose of this class is primarily for 3D graphics
// applications.
struct Vec2D{

    // I'm wrapping all of our member variables in a union.
    // So long as you make sure the byte-size is equivalent, this
    // allows you to access the data in whatever form is most convenient.
    // Meaning I can access Vec2D[0] or equivalently Vec2D.x .
    // I can also pass Vec2D internal array or just individual values if needed conveniently.
    union{
        struct {
            // Note: x,y are a convention
            // x,y could be position, but also any 2-component value.
            float x{0};
            float y{0};
            float w{0};     // 'w' is a third hidden component that could be used
                            // to determine if this is being used as a vector or a point
                            // If w=0 then a vector, if w=1 then a point
                            // DO not use 'w' for any computation however.
        };
        float data[3]; // for convenience if you want to access as 'data' or pass Vec2D as an array 
    };

    // Default conostrutcor
    // 'why default?' https://stackoverflow.com/questions/20828907/the-new-keyword-default-in-c11
//    Vec2D() = default;

    //! The "Real" constructor we want to use.
    // This initializes the values x,y, and the 'w' value
    Vec2D(float _x=0, float _y=0, float _w=0){
      x = _x;
      y = _y;
      w = _w;
    }

    //! Index operator, allowing us to access the individual
    // x,y components of our vector.
    float& operator[](int i){
        // NOTE: Think about why this works.
        //       There is no code to change here. 
      return ((&x)[i]);
    }

    //! Index operator, allowing us to access the individual
    // x,y components of our vector.
    const float& operator[](int i) const{
        // NOTE: Think about why this works.
        //       There is no code to change here.
        return ((&x)[i]);
    }


    // General Note
    // You'll observer that some of the operator overloads appear in this class
    // as member functions versus some that are free functions.
    // In general, if you need access to private member variables or the 'this' pointer
    // then you must use a member function. Otherwise, I recommend to 'free your functions'
    // and not make them part of the class for maximum use.
    //
    //! Multiplication Operator
    // Multiply vector by a uniform-scalar.
    Vec2D& operator *=(float s){
        x *= s;
        y *= s;
        return (*this);
    }

    //! Division Operator
    Vec2D& operator /=(float s){
        x /= s;
        y /= s;
        return (*this);
    }

    //! Addition operator
    Vec2D& operator +=(const Vec2D& v){
      x += v.x;
      y += v.y;
      w += v.w;
      assert(w != 2);
      return (*this);
    }

    //! Subtraction operator
    Vec2D& operator -=(const Vec2D& v){
      x -= v.x;
      y -= v.y;
      w -= v.w;
      assert(w != -1);
      return (*this);
    }

    
    //! Determines if this Vec2D represents a point.
    bool IsAPoint() const{
        if(1==w){
            return true;
        }
        return false;
    }
    
    //! Determines if this Vec2D represents a vector.
    bool IsAVector() const{
        if(0==w){
            return true;
        }
        return false;
    }
    
    //! Determine if the Vec2D is potentially in an invalid state.
    // This could occur for instance after trying to add a point and a point together.
    bool IsValid() const{
        if(w!= 0.0f || w!= 1.0f){
            return true;   
        }
        return false;
    }

};

//! Compute the dot product of a Vec2D
inline float Dot(const Vec2D& a, const Vec2D& b){
  return (a.x * b.x) + (a.y * b.y);
}

//! Test for equality
// NOTE: Comparing floats is somewhat tricky, meaning that
//       you will want to take the fabs(lhs.x - lhs.y) < 0.00001
//       of each component to see if they are 'close enough'
inline bool operator==(const Vec2D& lhs, const Vec2D& rhs) {
    bool result = fabs(lhs.x - rhs.x) < 0.00001 && fabs(lhs.y - rhs.y) < 0.00001 && lhs.w == rhs.w;
    return result;
}

//! Multiplication of a vector by a scalar values
inline Vec2D operator *(const Vec2D& v, float s){
  Vec2D vec;
  vec.x *= s;
  vec.y *= s;
  return vec;
}

//! Division of a vector by a scalar value.
inline Vec2D operator /(const Vec2D& v, float s){
  Vec2D vec;
  vec.x /= s;
  vec.y /= s;
  return vec;
}

//! Negation of a vector
// Use Case: Sometimes it is handy to apply a force in an opposite direction
inline Vec2D operator -(const Vec2D& v){
  Vec2D vec;
  vec.x *= -1;
  vec.y *= -1;
  return vec;
}

//! Return the magnitude of a vector
inline float Magnitude(const Vec2D& v){
  return sqrt(v.x * v.x + v.y * v.y);
}

//! Add two vectors together
inline Vec2D operator +(const Vec2D& a, const Vec2D& b){
  Vec2D vec;
  vec.x = a.x + b.x;
  vec.y = a.y + b.y;
  vec.w = a.w + b.w;
  assert(vec.w != 2);
  return vec;
}

//! Subtract two vectors
inline Vec2D operator -(const Vec2D& a, const Vec2D& b){
  Vec2D vec;
  vec.x = a.x - b.x;
  vec.y = a.y - b.y;
  vec.w = a.w - b.w;
  assert(vec.w != -1);
  return vec;
}

//! Vector Projection
inline Vec2D Project(const Vec2D& a, const Vec2D& b){
  float magA = Magnitude(a);
  Vec2D vec = a * (Dot(a, b) / (magA * magA));
  return vec;
}

//! Set a vectors magnitude to 1
// Note: This is NOT generating a normal vector
inline Vec2D Normalize(const Vec2D& v){
  Vec2D vec = v / Magnitude(v);
  return vec;
}

//! a x b (read: 'a crossed b')
// With a 3D vector we would yield another perpendicular cross product
// For 2D cross product, this will yield a scalar.
// You should write this to yield a scalar value.
inline float CrossProduct(const Vec2D& a, const Vec2D& b){
  float result = a.x * b.y + b.x * a.y;
  return result;
}

//! Pretty print a vector 
// std::ostream& could be 'std::cout' for example'
// This function is primarily used for debugging purposes
inline void PrettyPrint(std::ostream& os, const Vec2D& a){
   os << "x  : " << a.x << std::endl; 
   os << "y  : " << a.y << std::endl; 
   os << "(w): " << a.w << std::endl; 
}


//! Matrix 3D represents 3x3 matrices in Math
struct Matrix3D{
private:
    float n[3][3];  // Store each value of the matrix

public:

    //! Initializes to a identity matrix by default
    Matrix3D() {
        n[0][0] = 1; n[0][1] = 0; n[0][2] = 0;
        n[1][0] = 0; n[1][1] = 1; n[1][2] = 0;
        n[2][0] = 0; n[2][1] = 0; n[2][2] = 1;
    }

    
    //! Matrix constructor with 9 scalar values.
    Matrix3D( float n00, float n01, float n02,
              float n10, float n11, float n12,
              float n20, float n21, float n22){

        n[0][0] = n00; n[0][1] = n10; n[0][2] = n20;
        n[1][0] = n01; n[1][1] = n11; n[1][2] = n21;
        n[2][0] = n02; n[2][1] = n12; n[2][2] = n22;
    }

    //! Matrix constructor from three vectors.
    Matrix3D(const Vec2D& a, const Vec2D& b, const Vec2D& c){
      n[0][0] = a.x; n[0][1] = a.y; n[0][2] = a.w;
      n[1][0] = b.x; n[1][1] = b.y; n[1][2] = b.w;
      n[2][0] = c.x; n[2][1] = c.y; n[2][2] = c.w;
    }

    //! Index operator with two dimensions
    // Example: M(1,1) returns row 1 and column 1 of matrix M.
    float& operator ()(int i, int j){
      return (n[j][i]);
    }

    //! Index operator with two dimensions
    // Example: M(1,1) returns row 1 and column 1 of matrix M.
    const float& operator ()(int i, int j) const{
      return (n[j][i]);
    }

    //! Return a row from a matrix as a vector.
    Vec2D& operator [](int j){
      return (*reinterpret_cast<Vec2D *>(n[j]));
    }

    //! Return a row from a matrix as a vector.
    const Vec2D& operator [](int j) const{
      return (*reinterpret_cast<const Vec2D *>(n[j]));
    }

};

//! Matrix Multiplication
inline Matrix3D operator *(const Matrix3D& A, const Matrix3D& B){
  Matrix3D result;
  
  result[0][0] = A[0][0] * B[0][0] + A[0][1] * B[1][0] + A[0][2] * B[2][0];
  result[0][1] = A[0][0] * B[0][1] + A[0][1] * B[1][1] + A[0][2] * B[2][1];
  result[0][2] = A[0][0] * B[0][2] + A[0][1] * B[1][2] + A[0][2] * B[2][2];

  result[1][0] = A[1][0] * B[0][0] + A[1][1] * B[1][0] + A[1][2] * B[2][0];
  result[1][1] = A[1][0] * B[0][1] + A[1][1] * B[1][1] + A[1][2] * B[2][1];
  result[1][2] = A[1][0] * B[0][2] + A[1][1] * B[1][2] + A[1][2] * B[2][2];

  result[2][0] = A[2][0] * B[0][0] + A[2][1] * B[1][0] + A[2][2] * B[2][0];
  result[2][1] = A[2][0] * B[0][1] + A[2][1] * B[1][1] + A[2][2] * B[2][1];
  result[2][2] = A[2][0] * B[0][2] + A[2][1] * B[1][2] + A[2][2] * B[2][2];

  return result;
}

//! Matrix multiply by a vector
inline Vec2D operator *(const Matrix3D& M, const Vec2D& v){
  Vec2D vec;

  vec.x = M[0][0] * v.x + M[0][1] * v.y + M[0][2] * v.w;
  vec.y = M[1][0] * v.x + M[1][1] * v.y + M[1][2] * v.w;
  vec.w = M[2][0] * v.x + M[2][1] * v.y + M[2][2] * v.w;
    
  return vec;
}


#endif
