// GLSL Lang. Spec.
// 7.1 Built-in language variables

// Work group dimensions

in    uvec3 gl_NumWorkGroups;
  // The total number of global work items in each dimension of the work group that will execute the compute shader.
  // gl_NumWorkGroups = (num_groups_x, num_groups_y, num_groups_z);

const uvec3 gl_WorkGroupSize;
  // The local work-group size of the shader.
  // gl_WorkGroupSize = (local_size_x, local_size_y, local_size_z);

// Work group and invocation IDs

in    uvec3 gl_WorkGroupID;
  // Three-dimensional index of the global work gropu that the current invocation is executing in.
  // [0:gl_NumWorkGroups.x - 1, 0:gl_NumWorkGroups.y - 1, 0:gl_NumWorkGroups.z]

// Derived variables

in    uvec3 gl_GlobalInvocationID;
  // gl_GlobalInvocationID = gl_WorkGroupID * gl_WorkGroupSize + gl_LocalInvocationID;

in    uint  gl_LocalInvocationID;
  // gl_LocalInvocationID =
  //   gl_LocalInvocationID.z * gl_WorkGroupSize.x * gl_WorkGroupSize.y +
  //   gl_LocalInvocationID.y * gl_WorkGroupSize.x +
  //   gl_LocalINvocationID.x;

// derived variables
in    uvec3 gl_GlobalInvocationID;
in    uint  gl_LocalInvocationID;
