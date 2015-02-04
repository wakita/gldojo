#version 410 core

uniform Parameter {
  float time;
  float alpha;
} params;

out float vs_theta;

void main(void) {
  const vec3 triangle_vertices[3] = vec3[3](
    vec3(0.25,  -0.25,  0.5),
    vec3(-0.25, -0.25,  0.5),
    vec3(0.0,    0.25,  0.5));

  float t = params.time;
  float c = cos(t), s = sin(t);

  gl_Position = vec4(triangle_vertices[gl_VertexID], 1) +
    vec4(c / 2, s / 2, 0, 0);
  vs_theta = acos(-1) * gl_VertexID * 2 / 3;
}
