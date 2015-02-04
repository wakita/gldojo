#version 410 core

// Uniform block in [shared] layout

layout (shared) uniform TransformBlock {
// Member                 alignment  offset  aligned offset  size
  float scale;            // 4       0       0               4
  vec3 translation;       // 16      4       16              16
  float rotation[3];      // 16      28      32              48 (= 16 * 3)
  mat4 projection_matrix; // 16      80      80              48
} transform;              // size = 128 (= 80 + 48)

void main() {
  const vec3 vertices[3] = vec3[3](
      vec3( 0.25, -0.25, 0.5),
      vec3(-0.25, -0.25, 0.5),
      vec3( 0.00,  0.25, 0.5));

  vec3 p = vertices[gl_VertexID];
  p = p + transform.translation;

  float s[3], c[3];
  for (int i = 0; i < 3; i++) {
    s[i] = sin(transform.rotation[i]); c[i] = cos(transform.rotation[i]);
  }
  p = mat3(1, 0, 0, 0, c[0], -s[0], 0, s[0], c[0]) * p;
  p = mat3(s[0], 0, c[0], 0, 1, 0, 0, c[0], -s[0]) * p;
  p = mat3(c[0], -s[0], 0, s[0], c[0], 0, 0, 0, 1) * p;

  gl_Position = transform.projection_matrix * vec4(p, 1);
}
