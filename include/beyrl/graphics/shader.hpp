#pragma once

#include <string>
#include <unordered_map>

#include <beyrl/math/matrix.hpp>

namespace beyrl {

class Shader {
    unsigned m_id;
    mutable std::unordered_map<std::string, int> m_uniformLocations;

    int getUniformLocation(std::string const &name) const;
public:
    Shader(std::string const &vertexPath, std::string const &fragmentPath);
    Shader(Shader &&) = default;

    void bind() const;

    void setUniform(std::string const &name, bool value) const;
    void setUniform(std::string const &name, int value) const;
    void setUniform(std::string const &name, float value) const;
    void setUniform(std::string const &name, Vec2f value) const;
    void setUniform(std::string const &name, Vec3f value) const;
    void setUniform(std::string const &name, Vec4f value) const;
    void setUniform(std::string const &name, Vec2i value) const;
    void setUniform(std::string const &name, Vec2ui value) const;
    void setUniform(std::string const &name, Mat4f value) const;

};

}
