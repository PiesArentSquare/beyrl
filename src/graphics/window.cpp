#include <beyrl/graphics/window.hpp>
#include <beyrl/graphics/shader.hpp>

#include <iostream>

namespace beyrl {

Window::Window() {
    m_glwindow = glfwCreateWindow(1280, 720, "Beyrl", NULL, NULL);
    if (m_glwindow == NULL) {
        glfwTerminate();
        throw std::runtime_error("gl error: failed to create gl window");
    }
}

Window::~Window() {
    glfwDestroyWindow(m_glwindow);
}

void Window::setup() {
    glViewport(0, 0, 1280, 720);

    glfwSetFramebufferSizeCallback(m_glwindow, [](auto *window, int width, int height) {
        glViewport(0, 0, width, height);
    });
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