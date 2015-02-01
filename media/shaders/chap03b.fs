#version 410 core

in vec4 vs_color;
out vec4 color;

void main(void) {
  color = vec4(vs_color);
}
