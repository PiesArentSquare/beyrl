#pragma once

#include "shader.hpp"

namespace beyrl {

class Material {
public:
    virtual ~Material() {}
    virtual void apply(Shader const &) const = 0;
};

class PhongMaterial final : public Material {
    Vec3f m_ambient;
    Vec3f m_diffuse;
    Vec3f m_specular;
    float m_shininess;

public:
    PhongMaterial(Vec3f ambient, Vec3f diffuse, Vec3f specular, float shininess)
        : m_ambient(ambient), m_diffuse(diffuse), m_specular(specular), m_shininess(shininess) {}
    ~PhongMaterial() = default;


    inline void apply(Shader const &shader) const override {
        shader.setUniform("u_material.ambient", m_ambient);
        shader.setUniform("u_material.diffuse", m_diffuse);
        shader.setUniform("u_material.specular", m_specular);
        shader.setUniform("u_material.shininess", m_shininess);
    }
};

class EmissionMaterial final : public Material {    
    Vec3f m_ambient;
    Vec3f m_diffuse;
    Vec3f m_specular;

public:
    EmissionMaterial(Vec3f ambient, Vec3f diffuse, Vec3f specular)
        : m_ambient(ambient), m_diffuse(diffuse), m_specular(specular) {}
    ~EmissionMaterial() = default;

    inline void apply(Shader const &shader) const override {
        shader.setUniform("u_light.ambient", m_ambient);
        shader.setUniform("u_light.diffuse", m_diffuse);
        shader.setUniform("u_light.specular", m_specular);
    }
};

}