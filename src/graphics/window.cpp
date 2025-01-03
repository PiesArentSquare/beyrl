#include <beyrl/graphics/window.hpp>
#include <beyrl/graphics/shader.hpp>

#include "gl_context.hpp"

#include <iostream>

namespace beyrl {

Window::Window(Window::Properties props) {
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

void Window::render(Object const &object, Shader const &shader, Camera const &camera) {
    shader.bind();
    shader.setUniform("u_model", object.getMatrix());
    shader.setUniform("u_normalMatrix", object.getNormalMatrix());
    shader.setUniform("u_view", camera.getViewMatrix());
    shader.setUniform("u_projection", camera.getProjectionMatrix());
    object.m_model.bind();
    glDrawElements(GL_TRIANGLES, object.m_model.getVertCount(), GL_UNSIGNED_INT, 0);
}

void Window::setClear(Vec3f const &color) {
    glClearColor(color.x, color.y, color.z, 1.0f);
}

void Window::run(std::function<void()> runFunc) {
    prerun();
    while(isOpen()) {
        clear();
        runFunc();
        pollEvents();
    }
}

void Window::prerun() {
    glEnable(GL_DEPTH_TEST);
    resize(props.width, props.height);
}

void Window::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::pollEvents() {
    glfwSwapBuffers(static_cast<GLFWwindow *>(m_window));
    glfwPollEvents();
}

bool Window::isOpen() {
    return !glfwWindowShouldClose(static_cast<GLFWwindow *>(m_window));
}

float Window::getTime() const {
    return static_cast<float>(glfwGetTime());
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