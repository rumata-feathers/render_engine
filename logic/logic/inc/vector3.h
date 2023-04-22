//
// Created by Георгий Кузнецов on 12.04.2023.
//

#ifndef ENGINE_LOGIC_VECTOR3_H_
#define ENGINE_LOGIC_VECTOR3_H_

#include <vector>
#include <QColor>

template<typename T = double>
class vector3 {
 public:
  vector3();
//  template<typename ...Args>
//  vector3(Args&& ... args);
  vector3(T a, T b, T c);
  explicit vector3(const std::vector<T>& other);
  // K will cast to T
  template<typename K>
  vector3(const vector3<K>& other);

  // accessing vector3
  T x() const;
  T y() const;
  T z() const;
  T x_angle() const;
  T y_angle() const;
  T z_angle() const;
  T& x();
  T& y();
  T& z();
  T& x_angle();
  T& y_angle();
  T& z_angle();

  //operators for vector3
  vector3 operator-() const;
  T operator[](int i) const;
  T& operator[](int i);

  vector3& operator+=(const vector3& other);
  vector3& operator-=(const vector3& other);
  vector3& operator*=(const vector3& other);
  vector3& operator/=(const vector3& other);
  template<typename K>
  vector3& operator=(const vector3<K>& other);

  T length() const;
  T length_squared() const;
  void invert();

  void normalize();

  //conversion from vec3 to QColor
  operator QColor();

  ~vector3();
 private:
  std::vector<T> list;

};
template<typename T>
std::ostream& operator<<(std::ostream& out, const vector3<T>& v);
template<typename T, typename K>
vector3<T> operator+(const vector3<T>& u, const vector3<K>& v);
template<typename T, typename K>
vector3<T> operator-(const vector3<T>& u, const vector3<K>& v);
template<typename T, typename K>
vector3<T> operator*(const vector3<T>& u, const vector3<T>& v);
template<typename T>
vector3<T> operator*(T t, const vector3<T>& v);
template<typename T>
vector3<T> operator*(const vector3<T>& v, T t);
template<typename T>
vector3<T> operator/(vector3<T> v, T t);
template<typename T>
T dot(const vector3<T>& u, const vector3<T>& v);
template<typename T>
vector3<T> cross(const vector3<T>& u, const vector3<T>& v);
template<typename T>
vector3<T> unit_vector(vector3<T> v);

template<typename T>
vector3<vector3<T>> mat_mul(const vector3<vector3<T>>& mat1, const vector3<vector3<T>>& mat2);

// Type aliases for vec3
using point3 = vector3<double>;   // 3D point
using vec3 = vector3<double>;   // 3D point
using color = vector3<double>;    // RGB color

#endif //ENGINE_LOGIC_VECTOR3_H_
