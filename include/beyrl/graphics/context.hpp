#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include "window.hpp"

namespace beyrl {

class RenderingContext {
    bool m_init = false;
public:
    RenderingContext();
    ~RenderingContext();
    Window window(Window::properties props);
};

}