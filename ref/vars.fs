in  vec4  gl_FragCoord;
in  bool  gl_FrontFacing;
in  float gl_ClipDistance[];
in  vec2  gl_PointCoord;
in  int   gl_PrimitiveID;
in  int   gl_SampleID;
in  vec2  gl_SamplePosition;
in  int   gl_SampleMaskIn[];
in  int   gl_Layer;
in  int   gl_ViewportIndex;

out float gl_FragDepth;
out int   gl_SampleMask[];

/**

## Input variables (can be flat/noperspective/centroid/sample)

- interpolation qualifier
    - flat
    - noperspective
    - auxiliary qualifier
        - centroid
        - sample?
    - Note: integer/integer vector/double types must be qualified with "flat"
- error
    - boolean type
    - opaque type
*/

in vec3 normal;
centroid in vec2 TexCoord;
invariant centroid in vec4 Color;
noperspective in float temperature;
flat in vec3 myColor;
noperspective centroid in vec2 myTexCoord;

/**
# Output variables

## Error

- boolean type
- double, vector, matrix
- structure
- opaque
**/

out vec4 FragmentColor;
out uint Luminosity;
