#pragma once

#include <beyrl/math/matrix.hpp>

namespace beyrl {

class Transform {
    Vec3f m_position;
    Vec3f m_rotation;
    float m_scale = 1;

    Mat4f m_matrix;

    inline void generateMatrix() {
        m_matrix = Mat4f::translate(m_position)
            * Mat4f::rotateX(m_rotation.x) * Mat4f::rotateY(m_rotation.y) * Mat4f::rotateZ(m_rotation.z)
            * Mat4f::scale(m_scale);
    }
public:

    Transform(Vec3f position = {}, Vec3f rotation = {}, float scale = 1) : m_position(position), m_rotation(rotation), m_scale(scale) {
        generateMatrix();
    }

    inline Vec3f getPosition() { return m_position; }
    inline Vec3f getRotation() { return m_rotation; }
    inline float getScale() { return m_scale; }

    inline void setPosition(Vec3f position) { m_position = std::move(position); generateMatrix(); }
    inline void setRotation(Vec3f rotation) { m_rotation = std::move(rotation); generateMatrix(); }
    inline void setPosition(float scale) { m_scale = scale; generateMatrix(); }

    inline Mat4f getMatrix() const { return m_matrix; }

};

}