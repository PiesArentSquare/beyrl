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
        {{ -0.5f, -0.5f, 0.0f}, { 0.0f, 0.0f }},
        {{ -0.5f,  0.5f, 0.0f}, { 0.0f, 1.0f }},
        {{  0.5f,  0.5f, 0.0f}, { 1.0f, 1.0f }},
        {{  0.5f, -0.5f, 0.0f}, { 1.0f, 0.0f }}
    };
    unsigned indicies[] = {
        0, 1, 2,
        2, 3, 0
    };

    beyrl::Model model(verticies, sizeof(verticies), indicies, 6, layout);
    
    beyrl::Shader shader("res/shaders/vert.glsl", "res/shaders/frag.glsl");

    window.setResizeCallback([&](unsigned width, unsigned height) {
        shader.setUniform("u_projection", beyrl::Mat4f::perspective(static_cast<float>(width) / height, (3.14/180) * 35, 0.1, 1000));
    });

    beyrl::Transform camera({0, 0, -5}, {}, 1);
    shader.setUniform("u_view", camera.getMatrix());

    beyrl::Texture texture("res/textures/thumb.png");
    texture.setBlendMode(beyrl::Texture::BlendMode::Nearest, beyrl::Texture::BlendMode::Nearest);
    window.enableBlending(true);

    window.run([&]() {
        beyrl::Transform transform({}, {0, window.getTime(), 0}, 1);
        shader.setUniform("u_model", transform.getMatrix());
        
        texture.bind();
        window.render(model, shader);
    });
}
