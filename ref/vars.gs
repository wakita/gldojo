// GLSL Lang. Spec.
// 7.1 Built-in language variables

in gl_PerVertex {
  vec4  gl_Position;
  float gl_PointSize;
  float gl_ClipDistance[];
} gl_in[];

in int gl_PrimitiveIDIn;
in int gl_InvocationID;

out gl_PerVertex {
  vec4  gl_Position;
  float gl_PointSize;
  float gl_ClipDistance[];
};

out int gl_Primitive_ID;
out int gl_Layer;
out int gl_ViewPortIndex;

// Input variables

in float foo[]; // geometry shader input for vertex "out float foo;"
