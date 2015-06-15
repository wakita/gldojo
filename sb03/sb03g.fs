#version 410 core

in vec4 vs_color;

out vec4 color;

void main(void) {
  color = vs_color;
  /*
  float s = sin(gl_FragCoord.x * .25);
  float c = cos(gl_FragCoord.y * .25);
  color = vec4(s * .5 + .5, c * .5 + .5, s * c, 1.0);
  */
}
