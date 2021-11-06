#include <iostream>
#include <beyrl/beyrl.hpp>

struct vertex {
    beyrl::Vec3f position;
    beyrl::Vec2f uv;
};

int main() {
    beyrl::RenderingContext context;
    auto window = context.window({1280, 720, "Main Window"});

    constexpr vertex v{};
    auto layout = beyrl::layout(v.position, v.uv);

    vertex verticies[] = {
        {{ -0.5f, -0.5f, 0.0f}, {-1.0f, -1.0f }},
        {{ -0.5f,  0.5f, 0.0f}, {-1.0f,  1.0f }},
        {{  0.5f,  0.5f, 0.0f}, { 1.0f,  1.0f }},
        {{  0.5f, -0.5f, 0.0f}, { 1.0f, -1.0f }}
    };
    unsigned indicies[] = {
        0, 1, 2,
        2, 3, 0
    };

    beyrl::Model model(verticies, sizeof(verticies), indicies, 6, layout);
    
    beyrl::Shader shader("res/vert.glsl", "res/frag.glsl");

    window.run([&]() {
        window.render(model, shader);
    });
}
