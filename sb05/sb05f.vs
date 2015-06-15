#version 410 core

in vec4 Position;

out vec4 vs_color;

uniform mat4 ModelView;
uniform mat4 Projection;

void main(void) {
  gl_Position = Projection * ModelView * Position;
  vs_color = Position * 1.5 + vec4(0.5, 0.5, 0.5, 0.0);
}
