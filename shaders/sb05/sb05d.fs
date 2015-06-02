#version 410 core

uniform Parameter {
  float time;
  float alpha;
} params;

in float vs_theta;
out vec4 color;

void main(void) {
  float t = vs_theta + params.time;
  float c = cos(t), s = sin(t);
  color = vec4((c + 1) / 2, (s + 1) / 2, .5, params.alpha);
}
