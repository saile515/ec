#include "ec/math/matrix4.h"

#include "ec/math/common.h"
#include <math.h>

ec_matrix4f ec_matrix4f_create_identity_matrix()
{
    ec_matrix4f result = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

    return result;
}

ec_matrix4f ec_matrix4f_create_perspective_projection_matrix(float fov,
                                                             float aspect_ratio,
                                                             float near,
                                                             float far)
{
    ec_matrix4f result = ec_matrix4f_create_identity_matrix();

    float tangent = tan(fov / 2 * DEG_TO_RAD);

    result.xx = 1 / (tangent * aspect_ratio);
    result.yy = 1 / tangent;
    result.zz = -(far + near) / (far - near);
    result.zw = -1;
    result.wz = -(2 * far * near) / (far - near);
    result.ww = 0;

    return result;
}

ec_matrix4f ec_matrix4f_scale(const ec_matrix4f *matrix,
                              const ec_vector3f *scale)
{
    ec_matrix4f scaling_matrix;

    scaling_matrix.xx = scale->x;
    scaling_matrix.yy = scale->y;
    scaling_matrix.zz = scale->z;
    scaling_matrix.ww = 1;

    return ec_matrix4f_multiply(&scaling_matrix, matrix);
};

ec_matrix4f ec_matrix4f_rotate(const ec_matrix4f *matrix,
                               const ec_vector3f *rotation)
{
    double sinx = sin(rotation->x);
    double cosx = cos(rotation->x);
    double siny = sin(rotation->y);
    double cosy = cos(rotation->y);
    double sinz = sin(rotation->z);
    double cosz = cos(rotation->z);

    ec_matrix4f rotation_matrix = ec_matrix4f_create_identity_matrix();

    rotation_matrix.xx = cosy * cosz;
    rotation_matrix.xy = cosy * sinz;
    rotation_matrix.xz = -siny;
    rotation_matrix.yx = cosz * sinx * siny - cosx * sinz;
    rotation_matrix.yy = cosx * cosz + sinx * siny * sinz;
    rotation_matrix.yz = cosy * sinx;
    rotation_matrix.zx = cosx * cosz * siny + sinx * sinz;
    rotation_matrix.zy = cosx * siny * sinz - cosz * sinx;
    rotation_matrix.zz = cosx * cosy;

    return ec_matrix4f_multiply(&rotation_matrix, matrix);
};

ec_matrix4f ec_matrix4f_translate(const ec_matrix4f *matrix,
                                  const ec_vector3f *position)
{
    ec_matrix4f translation_matrix = ec_matrix4f_create_identity_matrix();

    translation_matrix.wx = position->x;
    translation_matrix.wy = position->y;
    translation_matrix.wz = position->z;

    return ec_matrix4f_multiply(&translation_matrix, matrix);
};

ec_matrix4f ec_matrix4f_multiply(const ec_matrix4f *a, const ec_matrix4f *b)
{
    ec_matrix4f result;

    result.xx = a->xx * b->xx + a->yx * b->xy + a->zx * b->xz + a->wx * b->xw;
    result.xy = a->xy * b->xx + a->yy * b->xy + a->zy * b->xz + a->wy * b->xw;
    result.xz = a->xz * b->xx + a->yz * b->xy + a->zz * b->xz + a->wz * b->xw;
    result.xw = a->xw * b->xx + a->yw * b->xy + a->zw * b->xz + a->ww * b->xw;
    result.yx = a->xx * b->yx + a->yx * b->yy + a->zx * b->yz + a->wx * b->yw;
    result.yy = a->xy * b->yx + a->yy * b->yy + a->zy * b->yz + a->wy * b->yw;
    result.yz = a->xz * b->yx + a->yz * b->yy + a->zz * b->yz + a->wz * b->yw;
    result.yw = a->xw * b->yx + a->yw * b->yy + a->zw * b->yz + a->ww * b->yw;
    result.zx = a->xx * b->zx + a->yx * b->zy + a->zx * b->zz + a->wx * b->zw;
    result.zy = a->xy * b->zx + a->yy * b->zy + a->zy * b->zz + a->wy * b->zw;
    result.zz = a->xz * b->zx + a->yz * b->zy + a->zz * b->zz + a->wz * b->zw;
    result.zw = a->xw * b->zx + a->yw * b->zy + a->zw * b->zz + a->ww * b->zw;
    result.wx = a->xx * b->wx + a->yx * b->wy + a->zx * b->wz + a->wx * b->ww;
    result.wy = a->xy * b->wx + a->yy * b->wy + a->zy * b->wz + a->wy * b->ww;
    result.wz = a->xz * b->wx + a->yz * b->wy + a->zz * b->wz + a->wz * b->ww;
    result.ww = a->xw * b->wx + a->yw * b->wy + a->zw * b->wz + a->ww * b->ww;

    return result;
}

ec_matrix4f ec_matrix4f_inverse(const ec_matrix4f *m)
{
    ec_matrix4f inv;
    float determinant;

    inv.xx = m->yy * m->zz * m->ww - m->yy * m->zw * m->wz -
             m->zy * m->yz * m->ww + m->zy * m->yw * m->wz +
             m->wy * m->yz * m->zw - m->wy * m->yw * m->zz;
    inv.xy = -m->xy * m->zz * m->ww + m->xy * m->zw * m->wz +
             m->zy * m->xz * m->ww - m->zy * m->xw * m->wz -
             m->wy * m->xz * m->zw + m->wy * m->xw * m->zz;
    inv.xz = m->xy * m->yz * m->ww - m->xy * m->yw * m->wz -
             m->yy * m->xz * m->ww + m->yy * m->xw * m->wz +
             m->wy * m->xz * m->yw - m->wy * m->xw * m->yz;
    inv.xw = -m->xy * m->yz * m->zw + m->xy * m->yw * m->zz +
             m->yy * m->xz * m->zw - m->yy * m->xw * m->zz -
             m->zy * m->xz * m->yw + m->zy * m->xw * m->yz;
    inv.yx = -m->yx * m->zz * m->ww + m->yx * m->zw * m->wz +
             m->zx * m->yz * m->ww - m->zx * m->yw * m->wz -
             m->wx * m->yz * m->zw + m->wx * m->yw * m->zz;
    inv.yy = m->xx * m->zz * m->ww - m->xx * m->zw * m->wz -
             m->zx * m->xz * m->ww + m->zx * m->xw * m->wz +
             m->wx * m->xz * m->zw - m->wx * m->xw * m->zz;
    inv.yz = -m->xx * m->yz * m->ww + m->xx * m->yw * m->wz +
             m->yx * m->xz * m->ww - m->yx * m->xw * m->wz -
             m->wx * m->xz * m->yw + m->wx * m->xw * m->yz;
    inv.yw = m->xx * m->yz * m->zw - m->xx * m->yw * m->zz -
             m->yx * m->xz * m->zw + m->yx * m->xw * m->zz +
             m->zx * m->xz * m->yw - m->zx * m->xw * m->yz;
    inv.zx = m->yx * m->zy * m->ww - m->yx * m->zw * m->wy -
             m->zx * m->yy * m->ww + m->zx * m->yw * m->wy +
             m->wx * m->yy * m->zw - m->wx * m->yw * m->zy;
    inv.zy = -m->xx * m->zy * m->ww + m->xx * m->zw * m->wy +
             m->zx * m->xy * m->ww - m->zx * m->xw * m->wy -
             m->wx * m->xy * m->zw + m->wx * m->xw * m->zy;
    inv.zz = m->xx * m->yy * m->ww - m->xx * m->yw * m->wy -
             m->yx * m->xy * m->ww + m->yx * m->xw * m->wy +
             m->wx * m->xy * m->yw - m->wx * m->xw * m->yy;
    inv.zw = -m->xx * m->yy * m->zw + m->xx * m->yw * m->zy +
             m->yx * m->xy * m->zw - m->yx * m->xw * m->zy -
             m->zx * m->xy * m->yw + m->zx * m->xw * m->yy;
    inv.wx = -m->yx * m->zy * m->wz + m->yx * m->zz * m->wy +
             m->zx * m->yy * m->wz - m->zx * m->yz * m->wy -
             m->wx * m->yy * m->zz + m->wx * m->yz * m->zy;
    inv.wy = m->xx * m->zy * m->wz - m->xx * m->zz * m->wy -
             m->zx * m->xy * m->wz + m->zx * m->xz * m->wy +
             m->wx * m->xy * m->zz - m->wx * m->xz * m->zy;
    inv.wz = -m->xx * m->yy * m->wz + m->xx * m->yz * m->wy +
             m->yx * m->xy * m->wz - m->yx * m->xz * m->wy -
             m->wx * m->xy * m->yz + m->wx * m->xz * m->yy;
    inv.ww = m->xx * m->yy * m->zz - m->xx * m->yz * m->zy -
             m->yx * m->xy * m->zz + m->yx * m->xz * m->zy +
             m->zx * m->xy * m->yz - m->zx * m->xz * m->yy;

    determinant =
        m->xx * inv.xx + m->xy * inv.yx + m->xz * inv.zx + m->xw * inv.wx;

    ec_matrix4f result;

    if (determinant == 0)
    {
        return result;
    }

    determinant = 1.0 / determinant;

    for (unsigned int i = 0; i < 16; i++)
    {
        ((float *)&result)[i] = ((float *)&inv)[i] * determinant;
    }

    return result;
}
