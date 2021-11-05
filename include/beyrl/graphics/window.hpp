#pragma once
#include <vector>
#include "gl_context.hpp"

namespace beyrl {

class Window {
    GLFWwindow *m_glwindow;
    Window();
    friend class RenderingContext;
public:
    ~Window();
    void run();
};

}