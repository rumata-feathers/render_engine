//
// Created by Георгий Кузнецов on 26.04.2023.
//

#include "../inc/vec3.h"
#include "../inc/resources.h"
#include <QColor>
#include <vector>

vec3::vec3() : list(std::vector<double>(3)) {}

vec3::vec3(const vec3& other) {
  try {
    list = other.list;

  } catch (...) {
    std::cerr << "Cannot construct vec3" << std::endl;
  }
}

vec3::vec3(double a, double b, double c) {
  list = std::vector<double>{a, b, c};
}

// now functions
double vec3::x() const {
  return list[0];
}
double vec3::y() const {
  return list[1];
}
double vec3::z() const {
  return list[2];
}
double vec3::x_angle() const {
  return list[0];
}
double vec3::y_angle() const {
  return list[1];
}
double vec3::z_angle() const {
  return list[2];
}
vec3 vec3::operator-() const {
  return {-list[0], -list[1], -list[2]};
}
double vec3::operator[](int i) const {
  try {
    return list[i];
  } catch (...) {
    throw std::out_of_range("Invalid iterator in vec3");
  }
}
double& vec3::operator[](int i) {
  try {
    return list[i];
  } catch (...) {
    throw std::out_of_range("Invalid iterator in vec3");
  }
}
vec3& vec3::operator+=(const vec3& other) {
  list[0] += other.list[0];
  list[1] += other.list[1];
  list[2] += other.list[2];
  return *this;
}
vec3& vec3::operator-=(const vec3& other) {
  list[0] -= other.list[0];
  list[1] -= other.list[1];
  list[2] -= other.list[2];
  return *this;
}
vec3& vec3::operator*=(const vec3& other) {
  list[0] *= other.list[0];
  list[1] *= other.list[1];
  list[2] *= other.list[2];
  return *this;
}
vec3& vec3::operator/=(const vec3& other) {
  list[0] /= other.list[0];
  list[1] /= other.list[1];
  list[2] /= other.list[2];
  return *this;
}
vec3& vec3::operator=(const vec3& other) {
  list = other.list;
  return *this;
}
double vec3::length() const {
  return std::sqrt(list[0] * list[0] + list[1] * list[1] + list[2] * list[2]);
}
double vec3::length_squared() const {
  return list[0] * list[0] + list[1] * list[1] + list[2] * list[2];

}
void vec3::normalize() {
  list[0] /= length();
  list[1] /= length();
  list[2] /= length();
}
vec3::~vec3() {
  list.clear();
}
void vec3::invert() {
  *this = -(*this);
}
vec3 vec3::random() {
  return {random_double(), random_double(), random_double()};
}
vec3 vec3::random(double min, double max) {
  return {random_double(min, max), random_double(min, max), random_double(min, max)};
}
vec3& vec3::operator*=(double t) {
  list[0] *= t;
  list[1] *= t;
  list[2] *= t;
  return *this;
}

std::ostream& operator<<(std::ostream& out, const vec3& vec3) {
  return out << vec3[0] << ' ' << vec3[1] << ' ' << vec3[2];
}

vec3 operator+(const vec3& u, const vec3& v) {
  auto copy(u);
  copy += v;
  return copy;
}

vec3 operator-(const vec3& u, const vec3& v) {
  auto copy(u);
  copy -= v;
  return copy;
}

vec3 operator*(const vec3& u, const vec3& v) {
  auto copy(u);
  copy *= v;
  return copy;
}

vec3 operator*(double t, const vec3& v) {
  return vec3(t * v[0], t * v[1], t * v[2]);
}

vec3 operator*(const vec3& v, double t) {
  return t * v;
}

vec3 operator/(const vec3& v, double t) {
  return (1 / t) * v;
}

double dot(const vec3& u, const vec3& v) {
  return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
}

vec3 cross(const vec3& u, const vec3& v) {
  return vec3(u[1] * v[2] - u[2] * v[1],
              u[2] * v[0] - u[0] * v[2],
              u[0] * v[1] - u[1] * v[0]);
}

vec3 unit_vector(const vec3& v) {
  return v / v.length();
}

std::vector<vec3> mat_mul(const std::vector<vec3>& mat1, const std::vector<vec3>& mat2) {
  int m = (int)mat1.size();
  int n = (int)mat2.size();
  int l = 3;

  assert(m == 3);
  assert(n == 3);

  std::vector<vec3> result(3);

  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < l; ++j) {
      double res = 0;
      for (int k = 0; k < n; ++k) {
        res += mat1[i][k] * mat2[k][j];
      }
      result[i][j] = res;
    }
  }

  return result;
}

vec3 random_in_unit_sphere() {
  while (true) {
    auto p = vec3::random(-1,1);
    if (p.length_squared() >= 1) continue;
    return p;
  }
}

class vec3;

