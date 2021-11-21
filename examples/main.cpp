#include <iostream>
#include <beyrl/beyrl.hpp>

int main() {
    beyrl::RenderingContext context;
    auto window = context.window({1280, 720, "Main Window"});

    beyrl::Model model("res/models/stall.obj");
    
    beyrl::Shader shader("res/shaders/vert.glsl", "res/shaders/frag.glsl");

    window.setResizeCallback([&](unsigned width, unsigned height) {
        shader.setUniform("u_projection", beyrl::Mat4f::perspective(static_cast<float>(width) / height, (3.14/180) * 35, 0.1, 1000));
    });

    beyrl::Texture texture("res/textures/stallTexture.png");
    texture.setBlendMode(beyrl::Texture::BlendMode::Nearest, beyrl::Texture::BlendMode::Nearest);
    window.enableBlending(true);

    float radius = 20;

    window.run([&]() {
        shader.setUniform("u_model", beyrl::Mat4f::identity());

        float camX = sin(window.getTime()) * radius;
        float camZ = cos(window.getTime()) * radius;

        auto camera = beyrl::Mat4f::lookAt({camX, 5, camZ}, {0, 2, 0}, {0, 1, 0});

        shader.setUniform("u_view", camera);
        
        texture.bind();
        window.render(model, shader);
    });
}
