#version 430

layout (location=0) in vec2 VertexPosition;

void main() {
  gl_Position = vec4(VertexPosition, 0, 1);
}
