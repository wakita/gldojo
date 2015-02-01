#version 410 core

uniform float time;
out vec3 vs_color;

void main(void) {
  const vec3 triangle_vertices[3] = vec3[3](
    vec3(0.25,  -0.25,  0.5),
    vec3(-0.25, -0.25,  0.5),
    vec3(0.0,    0.25,  0.5));
  
  float E  = exp(1);
  float PI = asin(1);

  float t = time;
  gl_Position = vec4(triangle_vertices[gl_VertexID], 1) * (sin(t / E) + 1.1) +
    vec4(cos(t), sin(t), 0, 1);

  float deg = t + (PI * 2 / 3) * gl_VertexID;
  vs_color = vec3((cos(deg) + 1) / 2, (sin(deg) + 1) / 1, .5);
}
