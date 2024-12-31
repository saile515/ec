#pragma once

#include "ec/math/vector3.h"
#include "ec/string.h"

typedef struct ec_matrix4f
{
    float xx;
    float xy;
    float xz;
    float xw;
    float yx;
    float yy;
    float yz;
    float yw;
    float zx;
    float zy;
    float zz;
    float zw;
    float wx;
    float wy;
    float wz;
    float ww;
} ec_matrix4f;

ec_matrix4f ec_matrix4f_create_identity_matrix();

ec_matrix4f ec_matrix4f_zero();

ec_matrix4f ec_matrix4f_create_perspective_projection_matrix(float fov,
                                                             float aspect_ratio,
                                                             float near,
                                                             float far);

ec_matrix4f ec_matrix4f_create_orthographic_projection_matrix(
    float frustum_height, float aspect_ratio, float near, float far);

ec_matrix4f ec_matrix4f_scale(const ec_matrix4f *matrix,
                              const ec_vector3f *scale);

ec_matrix4f ec_matrix4f_rotate(const ec_matrix4f *matrix,
                               const ec_vector3f *rotation);

ec_matrix4f ec_matrix4f_translate(const ec_matrix4f *matrix,
                                  const ec_vector3f *position);

ec_matrix4f ec_matrix4f_multiply(const ec_matrix4f *a, const ec_matrix4f *b);

ec_matrix4f ec_matrix4f_inverse(const ec_matrix4f *m);

ec_string ec_matrix4f_to_string(const ec_matrix4f *matrix);
