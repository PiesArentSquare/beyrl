#pragma once
#include <vector>
#include <functional>
#include <string>

#include "object.hpp"
#include "shader.hpp"
#include "camera.hpp"

namespace beyrl {

class Window {
    void *m_window;

    std::function<void(unsigned, unsigned)> resize_callback;

    struct properties {
        unsigned width, height;
        std::string name;

        properties(unsigned w = 1280, unsigned h = 720, std::string title = "Beyrl") : width(w), height(h), name(std::move(title)) {}
    } props;

    friend class RenderingContext;
    Window(properties p);
    void setup();
    void resize(unsigned width, unsigned height);
public:
    ~Window();
    void run(std::function<void()>);
    void render(Object const &model, Shader const &shader, Camera const &camera);
    void setClear(Vec3f const &color);
    inline void setResizeCallback(std::function<void(unsigned width, unsigned height)> callback) { resize_callback = callback; }

    float getTime() const;

    inline unsigned getWidth() const { return props.width; }
    inline unsigned getHeight() const { return props.height; }

    void enableBlending(bool enable);
};

}