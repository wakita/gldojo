#version 430

layout (location=0) in vec2 position_vs;
layout (location=3) in vec3 color_vs;

out vec3 color_fs;

void main() {
  gl_Position = vec4(position_vs, 0, 1);
  color_fs = color_vs;
}
