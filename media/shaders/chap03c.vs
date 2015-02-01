#version 410 core

layout (location = 0) in vec2 offset;
layout (location = 1) in vec3 color;

out VS_OUT {
  vec3 color;
} vs_out;

void main(void) {
  const vec4 vertices[3] = vec4[3](
      vec4( 0.25, -0.25, 0.5, 1.0),
      vec4(-0.25, -0.25, 0.5, 1.0),
      vec4( 0.00,  0.25, 0.5, 1.0));

  gl_Position = vertices[gl_VertexID] + vec4(offset, 0, 0);

  vs_out.color = color;
}
