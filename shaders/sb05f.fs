#version 410 core

out vec4 color;
in  vec4 vs_color;

void main(void) {
  color = vs_color;
}
