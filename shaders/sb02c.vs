#version 410 core

out vec4 vs_color;

void main(void) {
  gl_Position = vec4(0.0, 0.0, 0.5, 1.0);
  vs_color = vec4(0.0, 0.0, 0.5, 1.0);
}
