#version 430

layout (location=0) out vec4 Color;

in vec3 color_fs;

void main() {
  Color = vec4(color_fs, 1);
}
