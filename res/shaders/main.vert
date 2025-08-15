#version 330 core

layout (location = 0) in vec3 v_pos;
out vec4 a_color;

void main() {
    a_color = vec4(0.4f, 0.4f, 0.4f, 1.0f);
    gl_Position = vec4(v_pos, 1.0f);
}