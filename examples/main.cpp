#include <iostream>
#include <beyrl/beyrl.hpp>

int main() {
    beyrl::RenderingContext context;
    auto window = context.window({1280, 720, "Main Window"});

    auto layout = beyrl::layout(beyrl::Vec3f{}, beyrl::Vec2f{});

    float verticies[] = {
    //  position             uv
        -0.5f, -0.5f, 0.0f,  -1.0f, -1.0f,
        -0.5f,  0.5f, 0.0f,  -1.0f,  1.0f,
         0.5f,  0.5f, 0.0f,   1.0f,  1.0f,
         0.5f, -0.5f, 0.0f,   1.0f, -1.0f
    };
    unsigned indicies[] = {
        0, 1, 2,
        2, 3, 0
    };

    beyrl::Model model(verticies, sizeof(verticies), indicies, 6, layout);

    window.run([&]() {
        model.bind();
    });
}