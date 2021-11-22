#version 330 core

layout(location = 0) out vec4 color;

in vec2 texCoord;

uniform sampler2D tex;
uniform vec3 u_objectColor;
uniform vec3 u_lightColor;

void main() {
    color = vec4(u_lightColor * u_objectColor, 1.0);
}