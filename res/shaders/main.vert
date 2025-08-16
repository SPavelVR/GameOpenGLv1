#version 330 core

layout (location = 0) in vec3 v_pos;
out vec4 a_color;

void main() {
    a_color = vec4(v_pos.x, v_pos.y, v_pos.z, 1.0f);
    gl_Position = vec4(v_pos, 1.0f);
}