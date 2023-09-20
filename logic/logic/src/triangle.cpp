//
// Created by Георгий Кузнецов on 24.04.2023.
//

#include <utility>

#include "../inc/triangle.h"
triangle::triangle() = default;
triangle::triangle(const point3& v0, const point3& v1, const point3& v2, std::shared_ptr<material> m)
    : v0(v0), v1(v1), v2(v2), mat_ptr(std::move(m)) {}

double determinant(const std::vector<vec3>& mat) {
  return mat[0][0] * (mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1]) -
      mat[0][1] * (mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0]) +
      mat[0][2] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]);
}

bool triangle::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {

  const float EPSILON = 0.0000001;
  vec3 edge1 = v1 - v0;
  vec3 edge2 = v2 - v0;
  vec3 h = cross(r.dir, edge2);
  double a = dot(edge1, h);
  if (a > -EPSILON && a < EPSILON) {
    return false;
  }    // This ray is parallel to this triangle.

  double f = 1.0 / a;
  vec3 s = r.orig - v0;
  double u = f * dot(s, h);

  if (u < 0.0 || u > 1.0)
    return false;

  vec3 q = cross(s, edge1);
  double v = f * dot(r.dir, q);

  if (v < 0.0 || u + v > 1.0)
    return false;

  double t = f * dot(edge2, q);

  if (t <= EPSILON || t < t_min || t > t_max)
    return false;

  //otherwise

  rec.t = t;
  rec.p = r.at(rec.t);
  rec.mat_ptr = mat_ptr;
  return true;

  // e1 = (v1 - v0);
  // e2 = (v2 - v0);

  // r_origin + t * r_direction = v0 + beta * e1 + theta * e2
  // beta * e1 + theta * e2 - t * r_direction = r_origin - v0
  // ('v1_x - v0_x'   'v2_x - v0_x'   -'r_direction_x')       (beta )       (r_origin_x - v0_x)
  // ('v1_y - v0_y'   'v2_y - v0_y'   -'r_direction_y')   *   (theta)   =   (r_origin_y - v0_y)
  // ('v1_z - v0_z'   'v2_z - v0_z'   -'r_direction_z')       (t    )       (r_origin_z - v0_z)


  //          ('r_origin_x - v0_x'   'v2_x - v0_x'   -'r_direction_x')
  //          ('r_origin_y - v0_y'   'v2_y - v0_y'   -'r_direction_y')
  //          ('r_origin_z - v0_z'   'v2_z - v0_z'   -'r_direction_z')
  //  beta =    --------------------------------------------------
  //                                |A|

  //          ('v1_x - v0_x'   'r_origin_x - v0_x'   -'r_direction_x')
  //          ('v1_y - v0_y'   'r_origin_y - v0_y'   -'r_direction_y')
  //          ('v1_z - v0_z'   'r_origin_z - v0_z'   -'r_direction_z')
  //  theta =   --------------------------------------------------
  //                                |A|


  //          ('v1_x - v0_x'   'v2_x - v0_x'    'r_origin_x - v0_x')
  //          ('v1_y - v0_y'   'v2_y - v0_y'    'r_origin_y - v0_y')
  //          ('v1_z - v0_z'   'v2_z - v0_z'    'r_origin_z - v0_z')
  //  t     =   --------------------------------------------------
  //                                |A|


  auto A = std::vector<vec3>{{v1.x() - v0.x(), v2.x() - v0.x(), -r.dir.x()},
                             {v1.y() - v0.y(), v2.y() - v0.y(), -r.dir.y()},
                             {v1.z() - v0.z(), v2.z() - v0.z(), -r.dir.z()}};

  auto beta = determinant(std::vector<vec3>{{r.orig.x() - v0.x(), v2.x() - v0.x(), -r.dir.x()},
                                            {r.orig.y() - v0.y(), v2.y() - v0.y(), -r.dir.y()},
                                            {r.orig.z() - v0.z(), v2.z() - v0.z(), -r.dir.z()}})
      / determinant(A);
  if (beta < 0)
    return false;

  auto theta = determinant(std::vector<vec3>{{v1.x() - v0.x(), r.orig.x() - v0.x(), -r.dir.x()},
                                             {v1.y() - v0.y(), r.orig.y() - v0.y(), -r.dir.y()},
                                             {v1.z() - v0.z(), r.orig.z() - v0.z(), -r.dir.z()}})
      / determinant(A);
  if (theta < 0)
    return false;
  if (beta + theta > 1)
    return false;

//  auto t = determinant(std::vector<vec3>{{v1.x() - v0.x(), v2.x() - v0.x(), r.orig.x() - v0.x()},
//                                         {v1.y() - v0.y(), v2.y() - v0.y(), r.orig.y() - v0.y()},
//                                         {v1.z() - v0.z(), v2.z() - v0.z(), r.orig.z() - v0.z()}})
//      / determinant(A);

  if (t < t_min || t > t_max)
    return false;

  // there is collision
  // there is collision
  rec.t = t;
  rec.p = r.at(rec.t);
  rec.mat_ptr = mat_ptr;
//  vec3 outward_normal = (rec.p - center_) / radius_;
//  rec.set_face_normal(r, outward_normal);

  return true;
}
triangle::~triangle() = default;

