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

    ~Shader();

    void bind() const;

    void setUniform(std::string const &name, bool value) const;
    void setUniform(std::string const &name, int value) const;
    void setUniform(std::string const &name, float value) const;
    void setUniform(std::string const &name, Vec2f const &value) const;
    void setUniform(std::string const &name, Vec3f const &value) const;
    void setUniform(std::string const &name, Vec4f const &value) const;
    void setUniform(std::string const &name, Vec2i const &value) const;
    void setUniform(std::string const &name, Vec2ui const &value) const;
    void setUniform(std::string const &name, Mat4f const &value) const;

};

}
