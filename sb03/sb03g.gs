#version 410 core

layout (triangles) in;
layout (points, max_vertices = 3) out;

in  vec4 color_gs[];
out vec4 color_fs;

void main(void) {
  for (int i = 0; i < gl_in.length(); i++) {
    gl_Position = gl_in[i].gl_Position;
    color_fs = color_gs[gl_InvocationID];
    EmitVertex();
  }
}
