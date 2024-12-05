#include <stdexcept>
#include <iostream>
#include <unordered_map>

#include <beyrl/graphics/context.hpp>
#include <beyrl/graphics/window.hpp>

#include "gl_context.hpp"

namespace beyrl {

RenderingContext::RenderingContext() {
    if (!glfwInit()) throw std::runtime_error("gl error: failed to initialize glfw");
    glfwSetErrorCallback([](int error_code, char const *desc) {
        std::cerr << "gl error: " << error_code << ": " << desc << '\n';
    });
}

RenderingContext::~RenderingContext() {
    for (auto vao : m_vaos)
        glDeleteVertexArrays(1, &vao);
    for (auto buffer : m_buffers)
        glDeleteBuffers(1, &buffer);
    for (auto texture : m_textures)    
        glDeleteTextures(1, &texture);

    glfwTerminate();
}

Window RenderingContext::window(Window::Properties props) {
    Window window(props);
    glfwMakeContextCurrent(static_cast<GLFWwindow *>(window.m_window));
    if (!m_init) {
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
            throw std::runtime_error("gl error: failed to initialize glad");
    }
    if (!props.vsync_enabled)
        glfwSwapInterval(0);
    window.setup();
    return window;
}

Model RenderingContext::model(std::string const &objPath) {
    Model model(objPath);
    m_vaos.push_back(model.m_vao);
    m_buffers.push_back(model.m_vbo);
    m_buffers.push_back(model.m_ibo);
    return model;
}

Model RenderingContext::model(void *verticies, size_t verticiesSize, unsigned indicies[], size_t indexCount, Model::layout const &layout) {
    Model model(verticies, verticiesSize, indicies, indexCount, layout);
    m_vaos.push_back(model.m_vao);
    m_buffers.push_back(model.m_vbo);
    m_buffers.push_back(model.m_ibo);
    return model;
}

}