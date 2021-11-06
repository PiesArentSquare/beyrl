#pragma once

#include <array>
#include <vector>
#include <utility>
#include <beyrl/graphics/gl_context.hpp>

#include <beyrl/math/vector.hpp>

namespace beyrl {


struct element {
    unsigned type;
    unsigned count;
    size_t offset;

    constexpr element() = default;
    constexpr element(unsigned t, unsigned c, size_t o) : type(t), count(c), offset(o) {}
};

template<size_t N>
class static_layout {

    template<typename T, typename... Ts, size_t S>
    friend consteval static_layout<S> layout(T t, Ts... ts);

    static consteval unsigned getGlType(Vec2f) { return GL_FLOAT; }
    static consteval unsigned getGlType(Vec2i) { return GL_INT; }
    static consteval unsigned getGlType(Vec2ui) { return GL_UNSIGNED_INT; }
        
    template<size_t S, typename T>
    static consteval void layout_impl(static_layout<S> &l, unsigned i, size_t offset, T t) {
        l.elements[i] = element{getGlType(t), T::count, offset};
        l.stride = offset + sizeof(T);
    }

    template<size_t S, typename T, typename... Ts>
    static consteval void layout_impl(static_layout<S> &l, unsigned i, size_t offset, T t, Ts... ts) {
        l.elements[i] = element{getGlType(t), T::count, offset};
        layout_impl(l, i + 1, l.elements[i].offset + sizeof(T), ts...);
    }

public:
    std::array<element, N> elements;
    size_t stride;

    constexpr static_layout() = default;
};

template<typename T, typename... Ts, size_t S = sizeof...(Ts) + 1>
consteval static_layout<S> layout(T t, Ts... ts) {
    static_layout<S> l = {};

    l.elements[0] = element(static_layout<S>::getGlType(t), T::count, 0);
    static_layout<S>::layout_impl(l, 1, sizeof(T), ts...);

    return l;
}

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

    void bind() const;
};

}