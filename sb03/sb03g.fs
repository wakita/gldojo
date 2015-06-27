#version 410 core

in  vec4 color_fs;
out vec4 color;

void main(void) {
  color = color_fs;
}
