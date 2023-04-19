//
// Created by Георгий Кузнецов on 12.04.2023.
//

#include "../inc/vector3.h"
#include <iostream>

template<typename T>
vector3<T>::vector3(): list(std::vector<T>(3)) {}
template<typename T>
vector3<T>::vector3(const std::vector<T>& other) {
  try {
    if (other.size() == 3)
      list = other;
    else
      throw "Cannot construct vector3";

  } catch (const char* exception) {
    std::cerr << exception << std::endl;
  }
}
template<typename T>
template<typename K>
vector3<T>::vector3(const vector3<K>& other): list(other.list) {}

template<typename T>
template<typename ...Args>
vector3<T>::vector3(Args&& ...args): list{std::forward<Args>(args)...} {
  try {
    if (list.size() != 3) {
      throw "Cannot build vector3 with these arguments";
    }
  }
  catch (const char* exception) {
    std::cerr << exception << std::endl;
  }
}

// now functions
template<typename T>
T& vector3<T>::x() {
  return list[0];
}
template<typename T>
T vector3<T>::x() const {
  return list[0];
}
template<typename T>
T& vector3<T>::y() {
  return list[1];
}
template<typename T>
T vector3<T>::y() const {
  return list[1];
}
template<typename T>
T& vector3<T>::z() {
  return list[2];
}
template<typename T>
T vector3<T>::z() const {
  return list[2];
}
template<typename T>
T& vector3<T>::x_angle() {
  return list[0];
}
template<typename T>
T vector3<T>::x_angle() const {
  return list[0];
}
template<typename T>
T& vector3<T>::y_angle() {
  return list[1];
}
template<typename T>
T vector3<T>::y_angle() const {
  return list[1];
}
template<typename T>
T& vector3<T>::z_angle() {
  return list[2];
}
template<typename T>
T vector3<T>::z_angle() const {
  return list[2];
}

template<typename T>
vector3<T> vector3<T>::operator-() const {
  return vector3(-list[0], -list[1], -list[2]);
}
template<typename T>
T vector3<T>::operator[](int i) const {
  try {
    return list[i];
  } catch (...) {
    throw std::out_of_range("Invalid iterator in vector3");
  }
}
template<typename T>
T& vector3<T>::operator[](int i) {
  try {
    return list[i];
  } catch (...) {
    throw std::out_of_range("Invalid iterator in vector3");
  }
}

template<typename T>
vector3<T>& vector3<T>::operator+=(const vector3& other) {
  list[0] += other.list[0];
  list[1] += other.list[1];
  list[2] += other.list[2];
  return *this;
}
template<typename T>
vector3<T>& vector3<T>::operator-=(const vector3& other) {
  list[0] -= other.list[0];
  list[1] -= other.list[1];
  list[2] -= other.list[2];
  return *this;
}
template<typename T>
vector3<T>& vector3<T>::operator*=(const vector3& other) {
  list[0] *= other.list[0];
  list[1] *= other.list[1];
  list[2] *= other.list[2];
  return *this;
}
template<typename T>
vector3<T>& vector3<T>::operator/=(const vector3& other) {
  list[0] /= other.list[0];
  list[1] /= other.list[1];
  list[2] /= other.list[2];
  return *this;
}
template<typename T>
template<typename K>
vector3<T>& vector3<T>::operator=(const vector3<K>& other) {
  list = other.list;
  return *this;
}
template<typename T>
T vector3<T>::length() const {
  return std::sqrt(list[0] * list[0] + list[1] * list[1] + list[2] * list[2]);
}
template<typename T>
T vector3<T>::length_squared() const {
  return list[0] * list[0] + list[1] * list[1] + list[2] * list[2];

}
template<typename T>
void vector3<T>::normalize() {
  list[0] /= length();
  list[1] /= length();
  list[2] /= length();
}
template<typename T>
vector3<T>::~vector3() {
  list.clear();
}
template<typename T>
void vector3<T>::invert() {
  *this = -(*this);
}
template<typename T>
vector3<T>::vector3(std::initializer_list<T> initializer_list): list {initializer_list} {}

// external functions
template<typename T>
std::ostream& operator<<(std::ostream& out, const vector3<T>& vec3) {
  return out << vec3[0] << ' ' << vec3[1] << ' ' << vec3[2];
}
template<typename T, typename K>
vector3<T> operator+(const vector3<T>& u, const vector3<K>& v) {
  auto copy(u);
  copy += v;
  return copy;
}
template<typename T, typename K>
vector3<T> operator-(const vector3<T>& u, const vector3<K>& v) {
  auto copy(u);
  copy -= v;
  return copy;
}
template<typename T, typename K>
vector3<T> operator*(const vector3<T>& u, const vector3<K>& v) {
  auto copy(u);
  copy *= v;
  return copy;
}
template<typename T>
vector3<T> operator*(T t, const vector3<T>& v) {
  return vector3<T>(t * v.list[0], t * v.list[1], t * v.list[2]);
}
template<typename T>
vector3<T> operator*(const vector3<T>& v, T t) {
  return t * v;
}
template<typename T>
vector3<T> operator/(vector3<T> v, T t) {
  return (1 / t) * v;
}
template<typename T>
T dot(const vector3<T>& u, const vector3<T>& v) {
  return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
}
template<typename T>
vector3<T> cross(const vector3<T>& u, const vector3<T>& v) {
  return vector3<T>(u[1] * v[2] - u[2] * v[1],
                    u[2] * v[0] - u[0] * v[2],
                    u[0] * v[1] - u[1] * v[0]);
}
template<typename T>
vector3<T> unit_vector(vector3<T> v) {
  return v / v.length();
}

template class vector3<double>;
template class vector3<int>;

