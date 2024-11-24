#pragma once

#include "transform.hpp"

namespace beyrl {

struct Projection {
    virtual ~Projection() = default;
    virtual Mat4f generateMatrix() const = 0;
};

struct Orthographic : public Projection {
    float left, right, top, bottom, near, far;
    
    Orthographic(float l = -1, float r = 1, float t = 1, float b = -1, float n = -1, float f = 1)
        : left(l), right(r), top(t), bottom(b), near(n), far(f) {}
    
    Mat4f generateMatrix() const override {
        return Mat4f::orthographic(left, right, top, bottom, near, far);
    }
};

struct Perspective : public Projection {
    float aspect, fov, near, far;
    
    Perspective(float aspect, float fov, float near, float far)
        : aspect(aspect), fov(fov), near(near), far(far) {}
    
    Mat4f generateMatrix() const override {
        return Mat4f::perspective(aspect, fov, near, far);
    }
};

class Camera {
    Vec3f m_position;
    Vec3f m_target;
    Vec3f m_up;

    std::shared_ptr<Projection> m_projection;
    Mat4f m_view;

    void generateViewMatrix() {
        m_view = Mat4f::lookAt(m_position, m_target, m_up);
    }

public:
    static Vec3f constexpr UP = {0, 1, 0};

    Camera(Vec3f const &position, float yaw, float pitch, Vec3f const &worldUp = UP, std::shared_ptr<Projection> proj = std::make_shared<Projection>(Orthographic{}))
        : m_position(position), m_target(cos(yaw) * cos(pitch), sin(pitch), sin(yaw) * cos(pitch)), m_up(worldUp), m_projection(proj)
    {
        generateViewMatrix();
    }

    Camera(Vec3f const &position, Vec3f const &targetPosition, Vec3f const &worldUp = UP, std::shared_ptr<Projection> proj = std::make_shared<Projection>(Orthographic{}))
        : m_position(position), m_target(targetPosition), m_up(worldUp), m_projection(proj)
    {
        generateViewMatrix();
    }

    inline Mat4f getViewMatrix() const { return m_view; }
    inline Mat4f getProjectionMatrix() const { return m_projection->generateMatrix(); }
    inline Vec3f getPosition() const { return m_position; }

    inline void setPosition(Vec3f position) {
        m_position = position;
        generateViewMatrix();
    }

    inline void setTarget(Vec3f target) {
        m_target = target;
        generateViewMatrix();
    }
    
    inline void setWorldUp(Vec3f up) {
        m_up = up;
        generateViewMatrix(); 
    }

    inline void setProjection(std::shared_ptr<Projection> proj) {
        m_projection = proj;
    }
};

}