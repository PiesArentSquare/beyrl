#pragma once

#include "shader.hpp"
#include "texture.hpp"

namespace beyrl {

class Material {
public:
    virtual ~Material() {}
    virtual void apply(Shader const &) const = 0;
    virtual void bind() const {}
};

class PhongMaterial final : public Material {
    Texture m_diffuse;
    Texture m_specular;
    float m_shininess;

public:
    PhongMaterial(Texture diffuse, Texture specular, float shininess)
        : m_diffuse(diffuse), m_specular(specular), m_shininess(shininess) {}
    ~PhongMaterial() = default;

    inline void apply(Shader const &shader) const override {
        shader.setUniform("u_material.diffuse", 0);
        shader.setUniform("u_material.specular", 1);
        shader.setUniform("u_material.shininess", m_shininess);
    }

    inline void bind() const override {
        m_diffuse.bind();
        m_specular.bind(1);
    }
};

}