#version 430

layout (location=0) out vec4 FragColor;

in vec4 color_fs;

void main() {
  FragColor = color_fs;
}
