#version 430

layout (location=0) in vec2 VertexPosition;
layout (location=3) in vec3 VertexColor;

out vec3 Color;

void main() {
  gl_Position = vec4(VertexPosition, 0, 1);
  Color = VertexColor;
}
