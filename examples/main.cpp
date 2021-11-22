#include <iostream>
#include <beyrl/beyrl.hpp>

int main() {
    beyrl::RenderingContext context;
    auto window = context.window({1280, 720, "Main Window"});
    
    beyrl::Shader shader("res/shaders/vert.vs", "res/shaders/frag.fs");
    beyrl::Shader lightShader("res/shaders/light.vs", "res/shaders/light.fs");

    beyrl::Model model("res/models/cube.obj");
    beyrl::Model light("res/models/cube.obj");

    window.setResizeCallback([&](unsigned width, unsigned height) {
        shader.setUniform("u_projection", beyrl::Mat4f::perspective(static_cast<float>(width) / height, (3.14/180) * 35, 0.1, 1000));
        lightShader.setUniform("u_projection", beyrl::Mat4f::perspective(static_cast<float>(width) / height, (3.14/180) * 35, 0.1, 1000));
    });

    beyrl::Vec3f lightPos(1.2f, 1.0f, 2.0f);
    
    shader.setUniform("u_objectColor", beyrl::Vec3f{1.0f, 0.5f, 0.32f});
    shader.setUniform("u_lightColor", beyrl::Vec3f{1.0f, 1.0f, 1.0f});

    shader.setUniform("u_model", beyrl::Mat4f::identity());
    lightShader.setUniform("u_model", beyrl::Transform(lightPos, {}, 0.2f).getMatrix());

    float radius = 10;

    window.run([&]() {

        float camX = sin(window.getTime()) * radius;
        float camZ = cos(window.getTime()) * radius;

        auto camera = beyrl::Mat4f::lookAt({camX, 2, camZ}, {0, 0, 0}, {0, 1, 0});

        shader.setUniform("u_view", camera);
        lightShader.setUniform("u_view", camera);

        window.render(model, shader);
        window.render(light, lightShader);
    });
}
