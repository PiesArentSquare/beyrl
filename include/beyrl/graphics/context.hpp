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
    Window window(Window::Properties props);
    Model model(std::string const &objPath);
    Model model(void *verticies, size_t verticiesSize, unsigned indicies[], size_t indexCount, Model::layout const &layout);
    Texture texture(std::string const &path);
};

}