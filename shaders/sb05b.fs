#version 410 core

in vec4 vs_color;
out vec4 color;

void main(void) {
  color = vec4(0.7, 1.0, 1.0, 0.5);
  // color = vs_color;
}
