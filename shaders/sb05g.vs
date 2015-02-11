#version 410 core

struct vertex {
  vec4 position;
  vec3 color;
};

layout buffer my_vertices {
  vertex vertices[];
};

uniform mat4 Transform;

out VS_OUT {
  vec3 color;
} vs_out;

void main(void) {
  vertex v = vertices[gl_VertexID];
  gl_Position = Transform * v.position;
  vs_out.color = v.color;
}
