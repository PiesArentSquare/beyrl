#pragma once

#include <string>

namespace beyrl {

class Window;

class RenderingContext {
    bool m_gladInit = false;
public:
    RenderingContext();
    ~RenderingContext();
    Window window(unsigned width, unsigned height, std::string const &name);
};

}