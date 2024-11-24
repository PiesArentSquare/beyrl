#include <beyrl/graphics/texture.hpp>
#include <stb/stb_image.h>

#include "gl_context.hpp"

#include <iostream>

namespace beyrl {

Texture::Texture(std::string const &path) : m_floatTexture(false) {
    glGenTextures(1, &m_id);
    bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path.c_str(), &m_width, &m_height, &m_channels, 0);
    if (data) {

        int channel;

        switch(m_channels) {
            case 1:
                channel = GL_RED;
                break;
            case 3:
                channel = GL_RGB;
                break;
            case 4:
                channel = GL_RGBA;
                break;
            default:
                std::cerr << "texture error: image has unknown number of channels (expected 1, 3, or 4; got " << m_channels << ")\n";
                break;
        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, channel, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cerr << "texture error: failed to load texture\n";
    }
    stbi_image_free(data);
}

Texture::Texture(float *data, unsigned width, unsigned height)
    : m_width(width), m_height(height), m_channels(1), m_floatTexture(true)
{
    glGenTextures(1, &m_id);
    bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, m_width, m_height, 0, GL_RED, GL_FLOAT, data);
    setBlendMode(BlendMode::Bilinear, BlendMode::Bilinear, false);
}

Texture::~Texture() {}

void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::bind(int slot) const {
    if (GL_TEXTURE0 + slot < GL_ACTIVE_TEXTURE) {
        glActiveTexture(GL_TEXTURE0 + slot);
        bind();
    } else
        std::cerr << "texture error: specified slot is greater than allowed\n";
}

void Texture::updateTextureData(float *data) {
    bind();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, m_width, m_height, 0, GL_RED, GL_FLOAT, data);
}

int getMode(Texture::BlendMode mode) {
    switch(mode) {
    case Texture::BlendMode::Bilinear:
        return GL_LINEAR;
    case Texture::BlendMode::Nearest:
        return GL_NEAREST;
    default:
        throw std::runtime_error("illegal blend mode");
    }
}

int getMipmapMode(Texture::BlendMode mode) {
    switch(mode) {
        case Texture::BlendMode::Bilinear:
            return GL_LINEAR_MIPMAP_LINEAR;
        case Texture::BlendMode::Nearest:
            return GL_NEAREST_MIPMAP_NEAREST;
        default:
            throw std::runtime_error("illegal blend mode");
    }
}

void Texture::setBlendMode(Texture::BlendMode min, Texture::BlendMode mag, bool mipmap) {
    int minMode;
    if (mipmap)
        minMode = getMipmapMode(min);
    else
        minMode = getMode(min);
    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, getMode(mag));
}

}