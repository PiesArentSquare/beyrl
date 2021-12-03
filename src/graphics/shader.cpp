#include <iostream>
#include <sstream>
#include <fstream>

#include <beyrl/graphics/shader.hpp>

#include "gl_context.hpp"

namespace beyrl {

std::string readFile(std::string const &path) {
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::string result;
    try {
        file.open(path);
        std::stringstream ss;
        ss << file.rdbuf();
        file.close();
        result = ss.str();

    } catch (std::ifstream::failure e) {
        std::cout << "file error: unable to read file '" << path << "'\n";
    }
    return std::move(result);
}

unsigned compileShader(char const *source, GLenum type, std::string const &name) {
    unsigned shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    int result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char *log = (char*) alloca(length * sizeof(char));
        glGetShaderInfoLog(shader, length, &length, log);

        std::cerr << "gl error: shader '" << name << "' compilation failed\n" << log << '\n';
        glDeleteShader(shader);
        return 0;
    }
    return shader;

}

Shader::Shader(std::string const &vertPath, std::string const &fragPath) {
    auto vertSource = readFile(vertPath);
    auto fragSource = readFile(fragPath);

    m_id = glCreateProgram();

    auto vertShader = compileShader(vertSource.c_str(), GL_VERTEX_SHADER, vertPath);
    auto fragShader = compileShader(fragSource.c_str(), GL_FRAGMENT_SHADER, fragPath);

    glAttachShader(m_id, vertShader);
    glAttachShader(m_id, fragShader);
    glLinkProgram(m_id);
    glValidateProgram(m_id);

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
}

Shader::~Shader() {
    glDeleteProgram(m_id);
}

void Shader::bind() const {
    glUseProgram(m_id);
}

int Shader::getUniformLocation(std::string const &name) const {
    if (m_uniformLocations.find(name) != m_uniformLocations.end())
        return m_uniformLocations[name];
    else {
        int location = glGetUniformLocation(m_id, name.c_str());
        if (location == -1) std::cout << "gl error: could not find uniform '" << name << "'\n";
        m_uniformLocations[name] = location;
        return location;
    }
}

void Shader::setUniform(std::string const &name, bool value) const {
    bind();
    glUniform1i(getUniformLocation(name), static_cast<int>(value));
}

void Shader::setUniform(std::string const &name, int value) const {
    bind();
    glUniform1i(getUniformLocation(name), value);
}

void Shader::setUniform(std::string const &name, float value) const {
    bind();
    glUniform1i(getUniformLocation(name), value);
}

void Shader::setUniform(std::string const &name, Vec2f const &value) const {
    bind();
    glUniform2f(getUniformLocation(name), value.x, value.y);
}

void Shader::setUniform(std::string const &name, Vec3f const &value) const {
    bind();
    glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
}

void Shader::setUniform(std::string const &name, Vec4f const &value) const {
    bind();
    glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w);
}

void Shader::setUniform(std::string const &name, Vec2i const &value) const {
    bind();
    glUniform2i(getUniformLocation(name), value.x, value.y);
}

void Shader::setUniform(std::string const &name, Vec2ui const &value) const {
    bind();
    glUniform2ui(getUniformLocation(name), value.x, value.y);
}

void Shader::setUniform(std::string const &name, Mat4f const &value) const {
    bind();
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &value.elements[0]);
}

}
