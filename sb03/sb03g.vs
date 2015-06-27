#version 410 core

layout (location = 0) in vec2 offset;

out vec4 color_tcs;

void main(void) {
  const vec4 vertices[] = vec4[](
      vec4( .25, -.25, .5, 1.0),
      vec4(-.25, -.25, .5, 1.0),
      vec4( .00,  .25, .5, 1.0));


  gl_Position = vertices[gl_VertexID] + vec4(offset, 0, 0);
  color_tcs = vec4(0, 0, 1, 1.0);
}
