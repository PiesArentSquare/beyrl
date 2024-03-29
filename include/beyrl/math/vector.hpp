#pragma once

#include <iostream>
#include <math.h>

namespace beyrl {

#define BRL_ORDERSWAP(r, l, sign) inline friend r<T> operator sign(const l<T> &lhs, const r<T> &rhs) { return rhs sign lhs; }
#define BRL_OSGROUP(r, l) BRL_ORDERSWAP(r, l, +) BRL_ORDERSWAP(r, l, -) BRL_ORDERSWAP(r, l, *)

template<typename T> struct Vector2 {
    T x, y;

    static unsigned const count = 2;

    constexpr Vector2(T const x = 0, T const y = 0) : x(x), y(y) {}

    inline Vector2<T> &operator+=(Vector2<T> const &rhs) { x += rhs.x; y += rhs.y; return *this; }
    inline Vector2<T> &operator-=(Vector2<T> const &rhs) { x -= rhs.x; y -= rhs.y; return *this; }
    inline Vector2<T> &operator*=(T const rhs)          { x *= rhs; y *= rhs;     return *this; }

    inline Vector2<T> operator+(Vector2<T> const &rhs) const { return Vector2<T>(*this) += rhs; }
    inline Vector2<T> operator-(Vector2<T> const &rhs) const { return Vector2<T>(*this) -= rhs; }
    inline Vector2<T> operator*(T const rhs)          const { return Vector2<T>(*this) *= rhs; }

    inline Vector2<T> operator-() const { return {-x, -y}; }

    inline T operator*(Vector2<T> const &rhs) const { return x * rhs.x + y * rhs.y; }

    constexpr inline T mag() const { return sqrt(this->x * this->x + this->y * this->y); }
    constexpr inline Vector2<T> normalize() {
        auto m = this->mag();
        this->x /= m; 
        this->y /= m;
        return *this;
    }
    
};

template<typename T> struct Vector3 : public Vector2<T> {
    T z;

    static unsigned const count = 3;

    constexpr Vector3(T const x = 0, T const y = 0, T const z = 0) : Vector2<T>(x, y), z(z) {}
    constexpr Vector3(Vector2<T> const &xy, T const z = 0) : Vector2<T>(xy), z(z) {}

    inline Vector3<T> &operator+=(Vector3<T> const &rhs) { this->Vector2<T>::operator+=(rhs); z += rhs.z; return *this; }
    inline Vector3<T> &operator-=(Vector3<T> const &rhs) { this->Vector2<T>::operator-=(rhs); z -= rhs.z; return *this; }
    inline Vector3<T> &operator*=(T const rhs)          { this->Vector2<T>::operator*=(rhs); z *= rhs;   return *this; }

    inline Vector3<T> operator+(Vector3<T> const &rhs) const { return Vector3<T>(*this) += rhs; }
    inline Vector3<T> operator-(Vector3<T> const &rhs) const { return Vector3<T>(*this) -= rhs; }
    inline Vector3<T> operator*(T const rhs)          const { return Vector3<T>(*this) *= rhs; }

    inline Vector3<T> operator-() const { return {-this->x, -this->y, -z}; }

    inline T operator*(Vector3<T> const &rhs) const { return this->Vector2<T>::operator*(rhs) + z * rhs.z; }

    inline Vector3<T> cross (Vector3<T> const &rhs) const { return {this->y * rhs.z - this->z * rhs.y, this->z * rhs.x - this->x * rhs.z, this->x * rhs.y - this->y * rhs.x}; }
    
    BRL_OSGROUP(Vector3, Vector2)

    constexpr inline T mag() const { return sqrt(this->x * this->x + this->y * this->y + this->z * this->z); }
    constexpr inline Vector3<T> normalize() {
        auto m = this->mag();
        this->x /= m; 
        this->y /= m;
        this->z /= m;
        return *this;
    }

    constexpr inline static Vector3<T> up() { return {0, 1, 0}; }
};

template<typename T> struct Vector4 : public Vector3<T> {
    T w;
    
    static unsigned const count = 4;

    constexpr Vector4(T const x = 0, T const y = 0, T const z = 0, T const w = 0) : Vector3<T>(x, y, z), w(w) {}
    constexpr Vector4(Vector2<T> const &xy, T const z = 0, T const w = 0) : Vector3<T>(xy, z), w(w) {}
    constexpr Vector4(Vector3<T> const &xyz, T const w = 0) : Vector3<T>(xyz), w(w) {}

    inline Vector4<T> &operator+=(Vector4<T> const &rhs) { this->Vector3<T>::operator+=(rhs); w += rhs.w; return *this; }
    inline Vector4<T> &operator-=(Vector4<T> const &rhs) { this->Vector3<T>::operator-=(rhs); w -= rhs.w; return *this; }
    inline Vector4<T> &operator*=(T const rhs)          { this->Vector3<T>::operator*=(rhs); w *= rhs;   return *this; }

    inline Vector4<T> operator+(Vector4<T> const &rhs) const { return Vector4<T>(*this) += rhs; }
    inline Vector4<T> operator-(Vector4<T> const &rhs) const { return Vector4<T>(*this) -= rhs; }
    inline Vector4<T> operator*(T const rhs)          const { return Vector4<T>(*this) *= rhs; }
    
    inline Vector4<T> operator-() const { return {-this->x, -this->y, -this->z, -w}; }

    inline T operator*(Vector4<T> const &rhs) const { return this->Vector3<T>::operator*(rhs) + w * rhs.w; }
    
    BRL_OSGROUP(Vector4, Vector2)
    BRL_OSGROUP(Vector4, Vector3)

    constexpr inline T mag() const { return sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w); }
    constexpr inline Vector3<T> normalize() {
        auto m = this->mag();
        this->x /= m; 
        this->y /= m;
        this->z /= m;
        this->w /= m;
        return *this;
    }
};

#undef BRL_ORDERSWAP
#undef BRL_OSGROUP

using Vec2f = Vector2<float>;
using Vec3f = Vector3<float>;
using Vec4f = Vector4<float>;
using Vec2i = Vector2<int>;
using Vec2ui = Vector2<unsigned>;
}

template<typename T> std::ostream &operator<<(std::ostream &os, beyrl::Vector2<T> const &vec) {
    os << '[' << vec.x << ", " << vec.y << ']';
    return os;
}

template<typename T> std::ostream &operator<<(std::ostream &os, beyrl::Vector3<T> const &vec) {
    os << '[' << vec.x << ", " << vec.y << ", " << vec.z << ']';
    return os;
}

template<typename T> std::ostream &operator<<(std::ostream &os, beyrl::Vector4<T> const &vec) {
    os << '[' << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ']';
    return os;
}
