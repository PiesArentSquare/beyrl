#include <beyrl/graphics/window.hpp>
#include <beyrl/graphics/shader.hpp>

#include <iostream>

namespace beyrl {

Window::Window(Window::properties props) {
    m_glwindow = glfwCreateWindow(props.width, props.height, props.name.c_str(), NULL, NULL);
    if (m_glwindow == NULL) {
        glfwTerminate();
        throw std::runtime_error("gl error: failed to create gl window");
    }
    glfwSetWindowUserPointer(m_glwindow, this);
    glfwSetFramebufferSizeCallback(m_glwindow, [](auto *window, int width, int height) {
        Window *w = (Window *)glfwGetWindowUserPointer(window);
        w->resize(width, height);
    });
}

Window::~Window() {
    glfwDestroyWindow(m_glwindow);
}

void Window::setup() {
    resize(props.width, props.height);
}

void Window::resize(unsigned width, unsigned height) {
    glViewport(0, 0, width, height);
    props.width = width;
    props.height = height;
}

void Window::render(Model const &model, Shader const &shader) {
    shader.bind();
    model.bind();
    glDrawElements(GL_TRIANGLES, model.getVertCount(), GL_UNSIGNED_INT, 0);

}

void Window::run(std::function<void()> runFunc) {
    while(!glfwWindowShouldClose(m_glwindow)) {
        glClearColor(1.0, 0.8, 0.3, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        runFunc();
        
        glfwSwapBuffers(m_glwindow);
        glfwPollEvents();
    }
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