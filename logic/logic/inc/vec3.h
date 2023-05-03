//
// Created by Георгий Кузнецов on 26.04.2023.
//

#ifndef ENGINE_LOGIC_LOGIC_INC_VEC3_H_
#define ENGINE_LOGIC_LOGIC_INC_VEC3_H_

#include <vector>
#include <iostream>

class vec3 {
 public:
  vec3();
  vec3(double a, double b, double c);
  vec3(const vec3& other);

  double x() const;
  double y() const;
  double z() const;
  double x_angle() const;
  double y_angle() const;
  double z_angle() const;

  vec3 operator-() const;
  double operator[](int i) const;
  double& operator[](int i);

  vec3& operator+=(const vec3& other);
  vec3& operator-=(const vec3& other);
  vec3& operator*=(const vec3& other);
  vec3& operator*=(double t);
  vec3& operator/=(const vec3& other);
  vec3& operator=(const vec3& other);

  double length() const;
  double length_squared() const;
  void invert();

  void normalize();

  inline static vec3 random();

  inline static vec3 random(double min, double max);

  ~vec3();

//  //conversion from vec3 to QColor
//  operator QColor(){
//    QColor color_;
//    color_.setRedF(x());
//    color_.setGreenF(y());
//    color_.setBlueF(z());
//    return color_;
//  }
 private:
  std::vector<double> list;
};

std::ostream& operator<<(std::ostream& out, const vec3& v);
vec3 operator+(const vec3& u, const vec3& v);
vec3 operator-(const vec3& u, const vec3& v);
vec3 operator*(const vec3& u, const vec3& v);
vec3 operator*(double t, const vec3& v);
vec3 operator*(const vec3& v, double t);
vec3 operator/(const vec3& v, double t);

double dot(const vec3& u, const vec3& v);

vec3 cross(const vec3& u, const vec3& v);

vec3 unit_vector(const vec3& v);

std::vector<vec3> mat_mul(const std::vector<vec3>& mat1, const std::vector<vec3>& mat2);

vec3 random_in_unit_sphere();

// Type aliases for vec3
using point3 = vec3;   // 3D point
using color = vec3;    // RGB color

typedef vec3 point3;

#endif //ENGINE_LOGIC_LOGIC_INC_VEC3_H_
