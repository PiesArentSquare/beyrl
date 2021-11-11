#version 330 core

layout(location = 0) out vec4 color;

in vec2 uv;

uniform sampler2D tex;

void main() {
    // color = vec4(0.1, 0.05, 0.25, 1.0);
    color = texture(tex, uv);
}