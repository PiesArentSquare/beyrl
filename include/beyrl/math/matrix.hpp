#pragma once
#include <math.h>
#include <array>

#include "vector.hpp"

namespace beyrl {

template<typename T> struct Matrix4 {
    std::array<T, 16> elements;

    inline Matrix4<T> mul(Matrix4<T> const &other) const {
        Matrix4<T> result;
        T sum;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++) {
                sum = 0;
                for (int k = 0; k < 4; k++) sum += this->elements[k + j * 4] * other.elements[i + k * 4];
                result.elements[i + j * 4] = sum;
            }
        return result;
    };

    inline Vector4<T> mul(Vector4<T> const &other) const {
        return { other.x * this->elements[0] + other.y * this->elements[1] + other.z * this->elements[2] + other.w * this->elements[3],
                 other.x * this->elements[4] + other.y * this->elements[5] + other.z * this->elements[6] + other.w * this->elements[7],
                 other.x * this->elements[8] + other.y * this->elements[9] + other.z * this->elements[10] + other.w * this->elements[11],
                 other.x * this->elements[12] + other.y * this->elements[13] + other.z * this->elements[14] + other.w * this->elements[15] };
    };

    inline Matrix4<T> operator * (Matrix4<T> const &other) const { return other.mul(*this); }
    inline Matrix4<T> operator *= (Matrix4<T> const &other) { return *this = *this * other; }

    inline Vector4<T> operator * (Vector4<T> const &other) const { return this->mul(other); }
    friend Vector4<T> operator *= (Vector4<T> &vec, const Matrix4<T> &mat) { return vec = vec * mat; }

    inline const T &operator [] (int index) const { return elements.at(index); }

    inline constexpr static Matrix4<T> identity() {
        return { 1, 0, 0, 0,
                 0, 1, 0, 0,
                 0, 0, 1, 0,
                 0, 0, 0, 1 };
    }


    inline constexpr static Matrix4<T> orthographic(T const l, T const r, T const t, T const b, T const n = -1, T const f = 1) {
        return { 2/(r-l),      0,           0,           0,
                 0,            2/(t-b),     0,           0,
                 0,            0,          -2/(f-n),     0,
                 -(r+l)/(r-l),-(t+b)/(t-b),-(f+n)/(f-n), 1 };
    }

    inline constexpr static Matrix4<T> perspective(T const aspect, T const fov, T const near, T const far) {
        return { 1/(aspect * tan(fov/2)), 0,              0,                        0,
                 0,                       1/(tan(fov/2)), 0,                        0,
                 0,                       0,              (-far-near)/(far-near),  -1,
                 0,                       0,              (-2*far*near)/(far-near), 0 };
    }


    inline constexpr static Matrix4<T> translate(T const x, T const y, T const z) {
        return { 1, 0, 0, 0,
                 0, 1, 0, 0,
                 0, 0, 1, 0,
                 x, y, z, 1 };
    }

    inline constexpr static Matrix4<T> translate(Vector3<T> const &position) {
        return translate(position.x, position.y, position.z);
    }

    inline constexpr static Matrix4<T> rotateX(T const a) {
        return { 1, 0,      0,      0,
                 0, cos(a),-sin(a), 0,
                 0, sin(a), cos(a), 0,
                 0, 0,      0,      1 };
    }

    inline constexpr static Matrix4<T> rotateY(T const a) {
        return { cos(a), 0,-sin(a), 0,
                 0,      1, 0,      0,
                 sin(a), 0, cos(a), 0,
                 0,      0, 0,      1 };
    }

    inline constexpr static Matrix4<T> rotateZ(T const a) {
        return { cos(a), sin(a), 0, 0,
                -sin(a), cos(a), 0, 0,
                 0,      0,      1, 0,
                 0,      0,      0, 1 };
    }

    inline constexpr static Matrix4<T> rotate(T const a, Vector3<T> const r) {
        auto cosa = cos(a);
        auto sina = sin(a);
        auto omcosa = 1 - cosa;

        return { cosa + (r.x * r.x) * omcosa,     r.y * r.x * omcosa + r.z * sina, r.z * r.x * omcosa - r.y * sina, 0,
                 r.x * r.y * omcosa - r.z * sina, cosa + (r.y * r.y) * omcosa,     r.z * r.y * omcosa + r.x * sina, 0,
                 r.x * r.z * omcosa + r.y * sina, r.y * r.z * omcosa - r.x * sina, cosa + (r.z * r.z) * omcosa,     0,
                 0,                               0,                               0,                               1 };
    }

    inline constexpr static Matrix4<T> scale(T const x, T const y, T const z) {
        return { x, 0, 0, 0,
                 0, y, 0, 0,
                 0, 0, z, 0,
                 0, 0, 0, 1 };
    }

    inline constexpr static Matrix4<T> scale(T const s) {
        return { s, 0, 0, 0,
                 0, s, 0, 0,
                 0, 0, s, 0,
                 0, 0, 0, 1 };
    }

    inline constexpr static Matrix4<T> lookAt(Vector3<T> const &pos, Vector3<T> const &target, Vector3<T> const &up = Vector3<T>::up()) {
        auto cD = beyrl::Vec3f(pos - target).normalize();
        auto cR = up.cross(cD).normalize();
        auto cU = cD.cross(cR).normalize();
        return Matrix4<T>{ cR.x, cU.x, cD.x, 0,
            cR.y, cU.y, cD.y, 0,
            cR.z, cU.z, cD.z, 0,
            0,    0,    0,    1 }
            * translate(-pos);
    }

};
typedef Matrix4<float> Mat4f;

}

template<typename T> std::ostream &operator<<(std::ostream &os, beyrl::Matrix4<T> const &mat) {
    os << "\u2308 " << mat[0]  << ", " << mat[1]  << ", " << mat[2]  << ", " << mat[3]  << " \u2309\n";
    os << "| "      << mat[4]  << ", " << mat[5]  << ", " << mat[6]  << ", " << mat[7]  << " |\n";
    os << "| "      << mat[8]  << ", " << mat[9]  << ", " << mat[10] << ", " << mat[11] << " |\n";
    os << "\u230a " << mat[12] << ", " << mat[13] << ", " << mat[14] << ", " << mat[15] << " \u230b";
    return os;
}
