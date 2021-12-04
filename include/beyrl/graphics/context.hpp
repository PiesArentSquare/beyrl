#pragma once

#include <string>
#include <vector>
#include <memory>

#include "window.hpp"
#include "texture.hpp"

namespace beyrl {

class RenderingContext {
    bool m_init = false;

    std::vector<unsigned> m_vaos;
    std::vector<unsigned> m_buffers;
    std::vector<unsigned> m_textures;

public:
    RenderingContext();
    ~RenderingContext();
    Window window(Window::properties props);
    Model model(std::string const &objPath);
    Texture texture(std::string const &path);
};

}