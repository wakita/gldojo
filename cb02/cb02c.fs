#version 430

in vec3 FrontColor;
in vec3 BackColor;
in vec2 TexCoord;

layout (location = 0) out vec4 FragColor;

void main() {
  const float scale = 15.0;

  bvec2 toDiscard = greaterThan(fract(TexCoord * scale), vec2(0.2, 0.2));

  if (all(toDiscard)) discard;
  else FragColor = vec4(gl_FrontFacing ? FrontColor : BackColor, 1.0);
}
