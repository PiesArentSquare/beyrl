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

void Window::run(std::function<void()> runFunc) {
    Shader shader("res/vert.glsl", "res/frag.glsl");

    while(!glfwWindowShouldClose(m_glwindow)) {
        glClearColor(1.0, 0.8, 0.3, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.bind();
        runFunc();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        glfwSwapBuffers(m_glwindow);
        glfwPollEvents();
    }
}

}