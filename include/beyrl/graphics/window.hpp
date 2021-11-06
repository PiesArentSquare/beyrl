#pragma once
#include <vector>
#include "gl_context.hpp"
#include <functional>

namespace beyrl {

class Window {
    GLFWwindow *m_glwindow;

    friend class RenderingContext;
    Window();
    void setup();
public:
    ~Window();
    void run(std::function<void()>);
};

}