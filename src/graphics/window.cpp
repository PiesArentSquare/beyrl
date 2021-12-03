#include <beyrl/graphics/window.hpp>
#include <beyrl/graphics/shader.hpp>

#include "gl_context.hpp"

#include <iostream>

namespace beyrl {

Window::Window(Window::properties props) {
    m_window = glfwCreateWindow(props.width, props.height, props.name.c_str(), NULL, NULL);
    if (m_window == NULL) {
        glfwTerminate();
        throw std::runtime_error("gl error: failed to create gl window");
    }
    glfwSetWindowUserPointer(static_cast<GLFWwindow *>(m_window), this);
    glfwSetFramebufferSizeCallback(static_cast<GLFWwindow *>(m_window), [](auto *window, int width, int height) {
        Window *w = (Window *)glfwGetWindowUserPointer(window);
        w->resize(width, height);
    });
}

Window::~Window() {
    glfwDestroyWindow(static_cast<GLFWwindow *>(m_window));
}

void Window::setup() {
    resize(props.width, props.height);
}

void Window::resize(unsigned width, unsigned height) {
    glViewport(0, 0, width, height);
    props.width = width;
    props.height = height;
    if (resize_callback)
        resize_callback(width, height);
}

void Window::render(Object const &object, Shader const &shader) {
    shader.bind();
    shader.setUniform("u_model", object.getMatrix());
    shader.setUniform("u_normalMatrix", object.getNormalMatrix());
    object.m_model.bind();
    glDrawElements(GL_TRIANGLES, object.m_model.getVertCount(), GL_UNSIGNED_INT, 0);
}

void Window::setClear(Vec3f const &color) {
    glClearColor(color.x, color.y, color.z, 1.0f);
}

void Window::run(std::function<void()> runFunc) {
    glEnable(GL_DEPTH_TEST);
    resize(props.width, props.height);
    while(!glfwWindowShouldClose(static_cast<GLFWwindow *>(m_window))) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        runFunc();
        
        glfwSwapBuffers(static_cast<GLFWwindow *>(m_window));
        glfwPollEvents();
    }
}

float Window::getTime() const {
    return glfwGetTime();
}

void Window::enableBlending(bool enable) {
    if (enable) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    } else {
        glDisable(GL_BLEND);
    }
}

}