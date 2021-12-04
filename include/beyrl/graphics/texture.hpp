#pragma once

#include <string>

namespace beyrl {

class Texture {
    unsigned m_id;
    int m_width, m_height, m_channels;
public:

    enum class BlendMode {
        Bilinear,
        Nearest
    };

    Texture(std::string const &path);
    ~Texture();

    void bind() const;
    void bind(int slot) const;

    void setBlendMode(BlendMode min, BlendMode mag, bool mipmap = true);
};

}