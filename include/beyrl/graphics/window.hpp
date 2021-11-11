#pragma once
#include <vector>
#include <functional>
#include <string>

#include "model.hpp"
#include "shader.hpp"

namespace beyrl {

class Window {
    void *m_window;

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
    void render(Model const &model, Shader const &shader);

    void enableBlending(bool enable);
};

}