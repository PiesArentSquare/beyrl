#pragma once

#include "transform.hpp"

namespace beyrl {

class Camera {
    Vec3f m_position;
    Vec3f m_target;
    Vec3f m_up;

    Mat4f m_matrix;

    void generateMatrix() {
        m_matrix = Mat4f::lookAt(m_position, m_target, m_up);
    }

public:
    Camera(Vec3f const &position, float yaw, float pitch, Vec3f const &worldUp = {0, 1, 0}) : m_position(position), m_target(cos(yaw) * cos(pitch), sin(pitch), sin(yaw) * cos(pitch)), m_up(worldUp) {
        generateMatrix();
    }

    Camera(Vec3f const &position, Vec3f const &targetPosition, Vec3f const &worldUp = {0, 1, 0}) : m_position(position), m_target(targetPosition), m_up(worldUp) {
        generateMatrix();
    }

    inline Mat4f getMatrix() const { return m_matrix; }
    inline Vec3f getPosition() const { return m_position; }
};

}