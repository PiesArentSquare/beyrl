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

Window::~Window() {}

void Window::run() {
    glViewport(0, 0, 1280, 720);

    glfwSetFramebufferSizeCallback(m_glwindow, [](auto *window, int width, int height) {
        glViewport(0, 0, width, height);
    });


    // vao/vbo
    unsigned vao;
    glGenVertexArrays(1, &vao);

    unsigned vbo;
    glGenBuffers(1, &vbo);

    unsigned ibo;
    glGenBuffers(1, &ibo);

    float verticies[] = {
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f
    };
    unsigned indicies[] = {
        0, 1, 2,
        2, 3, 0
    };

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    Shader shader("res/vert.glsl", "res/frag.glsl");

    while(!glfwWindowShouldClose(m_glwindow)) {
        glClearColor(1.0, 0.8, 0.3, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.bind();
        glBindVertexArray(vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        glfwSwapBuffers(m_glwindow);
        glfwPollEvents();
    }
}

}