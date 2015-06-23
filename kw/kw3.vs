#version 430

layout (location=0) in vec4 VertexPosition;

out vec4 c;
out float r_tcs;

void main() {
  c = vec4(VertexPosition);
  gl_Position = c;
  r_tcs = VertexPosition.w;
}
