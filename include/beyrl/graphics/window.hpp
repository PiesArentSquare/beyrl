#pragma once
#include <vector>
#include <functional>
#include <string>

#include "gl_context.hpp"

namespace beyrl {

class Window {
    GLFWwindow *m_glwindow;

    struct properties {
        unsigned width, height;
        std::string name;

        properties(unsigned w = 1280, unsigned h = 720, std::string title = "Beyrl") : width(w), height(h), name(std::move(title)) {}
    } props;

    friend class RenderingContext;
    Window(properties p);
    void setup();
    void resize(unsigned width, unsigned height);
public:
    ~Window();
    void run(std::function<void()>);
};

}