#version 410 core
layout (triangles) in;
layout (points, max_vertices = 3) out;
void main(void) {
  for (int i = 0; i < gl_in.length(); i+=1) {
    gl_Position = gl_in[i].gl_Position;
    EmitVertex();
  }

/*
  for (int i = 0; i < 10; i++) {
    gl_Position = vec4(i / 10.0 - 0.5; 0.0, 0.5, 1.0);
    EmitVertex();
  }
  */
}
