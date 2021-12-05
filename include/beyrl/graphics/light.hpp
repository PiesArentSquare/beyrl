#pragma once

#include "shader.hpp"

namespace beyrl {

class Light {
    Vec3f m_ambient;
    Vec3f m_diffuse;
    Vec3f m_specular;

protected:
    Light(Vec3f ambient, Vec3f diffuse, Vec3f specular) : m_ambient(ambient), m_diffuse(diffuse), m_specular(specular) {}

public:
    virtual ~Light() {}

    // temporary
    virtual void apply(Shader const &shader) const {
        shader.setUniform("u_light.base.ambient", m_ambient);
        shader.setUniform("u_light.base.diffuse", m_diffuse);
        shader.setUniform("u_light.base.specular", m_specular);
    }
};

class DirectionalLight final : public Light {
    Vec3f m_direction;

public:
    DirectionalLight(Vec3f direction, Vec3f ambient, Vec3f diffuse, Vec3f specular) : Light(ambient, diffuse, specular), m_direction(direction) {}
    ~DirectionalLight() = default;

    void apply(Shader const &shader) const override {
        Light::apply(shader);
        shader.setUniform("u_light.direction", m_direction);
    }
};

class PointLight final : public Light {
    Vec3f m_position;
    float m_linear;
    float m_quadratic;
public:
    PointLight(Vec3f position, float linear, float quadratic, Vec3f ambient, Vec3f diffuse, Vec3f specular)
        : Light(ambient, diffuse, specular), m_position(position), m_linear(linear), m_quadratic(quadratic) {}
    ~PointLight() = default;
    
    void apply(Shader const &shader) const override {
        Light::apply(shader);
        shader.setUniform("u_light.position", m_position);
        shader.setUniform("u_light.linear", m_linear);
        shader.setUniform("u_light.quadratic", m_quadratic);
    }

};

class SpotLight final : public Light {
    Vec3f m_position;
    Vec3f m_direction;
    float m_cutoff;
    float m_outerCutoff;
public:
    SpotLight(Vec3f position, Vec3f direction, float cutoff, float outerCutoff, Vec3f ambient, Vec3f diffuse, Vec3f specular)
        : Light(ambient, diffuse, specular), m_position(position), m_direction(direction), m_cutoff(cutoff), m_outerCutoff(outerCutoff) {}
    ~SpotLight() = default;
    
    void apply(Shader const &shader) const override {
        Light::apply(shader);
        shader.setUniform("u_light.position", m_position);
        shader.setUniform("u_light.direction", m_direction);
        shader.setUniform("u_light.cutoff", m_cutoff);
        shader.setUniform("u_light.outerCutoff", m_outerCutoff);
    }
};

}