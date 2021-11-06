#include <beyrl/graphics/context.hpp>
#include <beyrl/graphics/window.hpp>

#include <stdexcept>
#include <iostream>

namespace beyrl {

RenderingContext::RenderingContext() {
    if (!glfwInit()) throw std::runtime_error("gl error: failed to initialize glfw");
    glfwSetErrorCallback([](int error_code, char const *desc) {
        std::cerr << "gl error: " << error_code << ": " << desc << '\n';
    });
}

RenderingContext::~RenderingContext() {
    glfwTerminate();
}

Window RenderingContext::window(Window::properties props) {
    Window window(props);
    glfwMakeContextCurrent(window.m_glwindow);
    if (!m_init) {
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
            throw std::runtime_error("gl error: failed to initialize glad");
    }
    window.setup();
    return window;
}

}