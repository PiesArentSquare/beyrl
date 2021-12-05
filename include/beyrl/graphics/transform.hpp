#pragma once

#include <beyrl/math/matrix.hpp>

namespace beyrl {

class Transform {
    Vec3f m_position;
    Vec3f m_rotation;
    Vec3f m_scale = {1, 1, 1};

    Mat4f m_matrix;
    Mat4f m_normalMatrix;

    inline void generateMatrix() {
        m_matrix = Mat4f::translate(m_position)
            * Mat4f::rotateX(m_rotation.x) * Mat4f::rotateY(m_rotation.y) * Mat4f::rotateZ(m_rotation.z)
            * Mat4f::scale(m_scale);
        m_normalMatrix = Mat4f::transpose(Mat4f::inverse(m_matrix));
    }
public:

    Transform() : m_position(), m_rotation(), m_scale({1,1,1}) {
        generateMatrix();
    }

    Transform(Vec3f position, Vec3f rotation, float scale = 1) : m_position(position), m_rotation(rotation), m_scale({scale, scale, scale}) {
        generateMatrix();
    }

    Transform(Vec3f position, Vec3f rotation, Vec3f scale) : m_position(position), m_rotation(rotation), m_scale(scale) {
        generateMatrix();
    }

    inline Vec3f getPosition() { return m_position; }
    inline Vec3f getRotation() { return m_rotation; }
    inline Vec3f getScale() { return m_scale; }

    inline void setPosition(Vec3f position) { m_position = position; generateMatrix(); }
    inline void setRotation(Vec3f rotation) { m_rotation = rotation; generateMatrix(); }
    inline void setScale(Vec3f scale) { m_scale = scale; generateMatrix(); }
    inline void setScale(float scale) { m_scale = {scale, scale, scale}; generateMatrix(); }

    inline Mat4f getMatrix() const { return m_matrix; }
    inline Mat4f getNormalMatrix() const { return m_normalMatrix; }
};

}