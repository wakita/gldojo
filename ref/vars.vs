// GLSL Lang. Spec.
// 7.1 Built-in language variables

in  int gl_VertexID;
in  int gl_InstanceID;

out gl_PerVertex {
  vec4  gl_Position;
  float gl_PointSize;
  float gl_ClipDistance[];
};

/**
An example of input variable declaration

    in vec4 position;
    in vec3 normal;
    in vec2 texCoord[4];

**/

/**
An example of output variable declaration

    out vec3 normal;
    centroid out vec2 TexCoord;
    invariant centroid out vec4 Color;
    noperspective out float temperature;
    flat out vec4 myColor;
    noperspective centroid out vec2 myTexCoord;
    sample out vec4 perSampleColor
**/
