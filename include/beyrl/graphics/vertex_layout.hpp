#pragma once

#include <array>
#include <utility>

#include <beyrl/math/vector.hpp>

namespace beyrl {

enum class vectype {
    Float,
    Int,
    UInt
};

struct element {
    vectype type;
    unsigned count;
    size_t offset;

    constexpr element() = default;
    constexpr element(vectype t, unsigned c, size_t o) : type(t), count(c), offset(o) {}
};

template<size_t N>
class static_layout {

    static constexpr vectype getType(Vec2f) { return vectype::Float; }
    static constexpr vectype getType(Vec2i) { return vectype::Int; }
    static constexpr vectype getType(Vec2ui) { return vectype::UInt; }

    template<typename T, typename... Ts, size_t S>
    friend constexpr static_layout<S> layout(T t, Ts... ts);

    template<typename T>
    friend constexpr static_layout<1> layout(T t);
        
    template<size_t S, typename T>
    static constexpr void layout_impl(static_layout<S> &l, unsigned i, size_t offset, T t) {
        l.elements[i] = element{getType(t), T::count, offset};
        l.stride = offset + sizeof(T);
    }

    template<size_t S, typename T, typename... Ts>
    static constexpr void layout_impl(static_layout<S> &l, unsigned i, size_t offset, T t, Ts... ts) {
        l.elements[i] = element{getType(t), T::count, offset};
        layout_impl(l, i + 1, l.elements[i].offset + sizeof(T), ts...);
    }

public:
    std::array<element, N> elements;
    size_t stride;

    constexpr static_layout() = default;
};

template<typename T, typename... Ts, size_t S = sizeof...(Ts) + 1>
constexpr static_layout<S> layout(T t, Ts... ts) {
    static_layout<S> l = {};

    l.elements[0] = element(static_layout<S>::getType(t), T::count, 0);
    static_layout<S>::layout_impl(l, 1, sizeof(T), ts...);

    return l;
}

template<typename T>
constexpr static_layout<1> layout(T t) {
    static_layout<1> l{};
    l.elements[0] = element(static_layout<1>::getType(t), T::count, 0);
    return l;
}

}