#version 410 core

uniform float time;

in vec3 vs_color;
out vec4 color;

void main(void) {
  color = vec4(vs_color * min(time / 100, 1), 1);
}
