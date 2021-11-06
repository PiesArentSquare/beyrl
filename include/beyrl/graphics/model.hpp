#pragma once

#include "vertex_layout.hpp"
#include <vector>

namespace beyrl {

class Model {
    unsigned m_vertCount;
    unsigned m_vao, m_vbo, m_ibo;

    struct layout {
        std::vector<element> elements;
        size_t stride;

        template<size_t N>
        layout(static_layout<N> l) : elements(l.elements.begin(), l.elements.end()), stride(l.stride) {}
    };

    void bindVAO() const;
    void bindVBO() const;
    void bindIBO() const;

public:
    Model(float verticies[], size_t verticiesSize, unsigned indicies[], size_t indexCount, layout const &layout);
    ~Model();

    void bind() const;
};

}