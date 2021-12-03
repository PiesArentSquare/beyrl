#pragma once

#include <string>
#include <vector>
#include <memory>

#include "window.hpp"

namespace beyrl {

class RenderingContext {
    bool m_init = false;

    std::vector<unsigned> m_vaos;
    std::vector<unsigned> m_buffers;

public:
    RenderingContext();
    ~RenderingContext();
    Window window(Window::properties props);
    Model model(std::string const &objPath);
};

}