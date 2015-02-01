#version 410 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec4 vs_color;

void main(void) {
  gl_Position = vec4(position, 1);
  vs_color = vec4(color, 1);
}
