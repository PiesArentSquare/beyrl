#pragma once

#include <string>

namespace beyrl {

class Texture {
    unsigned m_id;
    int m_width, m_height, m_channels;
    bool m_floatTexture;
public:

    enum class BlendMode {
        Bilinear,
        Nearest
    };

    Texture(std::string const &path);
    // TODO: make this more general purpose
    Texture(float *data, unsigned width, unsigned height);
    ~Texture();

    void bind() const;
    void bind(int slot) const;

    void updateTextureData(float *data);

    void setBlendMode(BlendMode min, BlendMode mag, bool mipmap = true);
};

}