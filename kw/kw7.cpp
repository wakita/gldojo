// Reference: https://gist.github.com/Groovounet/7258805

#include <stdlib.h>

#include "Program.hpp"

using namespace smartnova::gl;

using std::cout;
using std::endl;

typedef vector<GLenum> Targets;

class KW7: public Application {
  public: KW7(Json config): Application(config) {}

  virtual void init() {
    Application::init();
  }

  void show(vector<GLenum> targets) {
    GLint v;
    for (auto target: targets) {
      glGetIntegerv(target, &v);
      cout << "    " << target << ": " << v << endl;
    }
  }

  void show(vector<GLenum> targets, int i) {
    for (auto target: targets) {
      cout << "    " << target << ": ";
      for (int j = 0; j < i; j++) {
        GLint v;
        glGetIntegeri_v(target, j, &v);
        if (j > 0) cout << ", ";
        cout << v;
      }
      cout << endl;
    }
  }

  virtual void startup() {
    cout <<
      "OpenGL Version:  " << glbinding::ContextInfo::version()  << endl <<
      "OpenGL Vendor:   " << glbinding::ContextInfo::vendor()   << endl <<
      "OpenGL Renderer: " << glbinding::ContextInfo::renderer() << endl <<
      "OpenGL Revision: " << glbinding::Meta::glRevision() << " (gl.xml)" << endl <<
      "GLSL Version:    " << glGetString(GL_SHADING_LANGUAGE_VERSION) <<
      endl << endl;

    cout << "GPU memory" << endl;
    show(vector<GLenum>({
          gl::GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX,
          gl::GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX,
          gl::GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX,
          gl::GL_GPU_MEMORY_INFO_EVICTION_COUNT_NVX,
          gl::GL_GPU_MEMORY_INFO_EVICTED_MEMORY_NVX }));

    cout << endl << "Generic limits" << endl;
    show(vector<GLenum>({
          GL_MAX_SUBROUTINES,
          GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS,
          GL_MAX_COMBINED_ATOMIC_COUNTERS,
          GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS,
          GL_MAX_PROGRAM_TEXEL_OFFSET,
          GL_MIN_PROGRAM_TEXEL_OFFSET,
          GL_MAX_COMBINED_UNIFORM_BLOCKS,
          GL_MAX_UNIFORM_BUFFER_BINDINGS,
          GL_MAX_UNIFORM_BLOCK_SIZE,
          GL_MAX_UNIFORM_LOCATIONS,
          GL_MAX_VARYING_COMPONENTS,
          GL_MAX_VARYING_VECTORS,
          GL_MAX_VARYING_FLOATS,
          GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS,
          GL_MAX_SHADER_STORAGE_BLOCK_SIZE,
          GL_MAX_COMBINED_SHADER_OUTPUT_RESOURCES,
          GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT,
          GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT,
          GL_NUM_PROGRAM_BINARY_FORMATS,
          GL_NUM_SHADER_BINARY_FORMATS,
          GL_PROGRAM_BINARY_FORMATS }));

    cout << endl << "Vertex shader information" << endl;
    show(Targets({
          GL_MAX_VERTEX_ATOMIC_COUNTERS,
          GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS,
          GL_MAX_VERTEX_ATTRIBS,
          GL_MAX_VERTEX_OUTPUT_COMPONENTS,
          GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
          GL_MAX_VERTEX_UNIFORM_COMPONENTS,
          GL_MAX_VERTEX_UNIFORM_VECTORS,
          GL_MAX_VERTEX_UNIFORM_BLOCKS,
          GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS }));

    cout << endl << "Geometry shader information" << endl;
    show(Targets({
          GL_MAX_GEOMETRY_ATOMIC_COUNTERS,
          GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS,
          GL_MAX_GEOMETRY_INPUT_COMPONENTS,
          GL_MAX_GEOMETRY_OUTPUT_COMPONENTS,
          GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS,
          GL_MAX_GEOMETRY_UNIFORM_BLOCKS,
          GL_MAX_GEOMETRY_UNIFORM_COMPONENTS,
          GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS,
          GL_MAX_VERTEX_STREAMS }));

    cout << endl << "Tessellation control shader information" << endl;
    show(Targets({
          GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS,
          GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS,
          GL_MAX_TESS_CONTROL_INPUT_COMPONENTS,
          GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS,
          GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS,
          GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS,
          GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS,
          GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS }));

    cout << endl << "Tessellation evaluation shader information" << endl;
    show(Targets({
          GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS,
          GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS,
          GL_MAX_TESS_EVALUATION_INPUT_COMPONENTS,
          GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS,
          GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS,
          GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS,
          GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS,
          GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS }));

    cout << endl << "Fragment shader information" << endl;
    show(Targets({
          GL_MAX_FRAGMENT_ATOMIC_COUNTERS,
          GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS,
          GL_MAX_FRAGMENT_INPUT_COMPONENTS,
          GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
          GL_MAX_FRAGMENT_UNIFORM_VECTORS,
          GL_MAX_FRAGMENT_UNIFORM_BLOCKS,
          GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS,
          GL_MAX_DRAW_BUFFERS,
          GL_MAX_DUAL_SOURCE_DRAW_BUFFERS }));

    cout << endl << "Computation shader limits" << endl;
    show(vector<GLenum>({
          GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS,
          GL_MAX_COMPUTE_UNIFORM_BLOCKS,
          GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS,
          GL_MAX_COMPUTE_IMAGE_UNIFORMS,
          GL_MAX_COMPUTE_UNIFORM_COMPONENTS,
          GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS,
          GL_MAX_COMPUTE_ATOMIC_COUNTERS,
          GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS,
          GL_MAX_COMPUTE_SHARED_MEMORY_SIZE,
          GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS }));
    show(vector<GLenum>({
          GL_MAX_COMPUTE_WORK_GROUP_COUNT,
          GL_MAX_COMPUTE_WORK_GROUP_SIZE }),
        3);

    cout << endl << "Pulling information" << endl;
    show(Targets({
          GL_MAX_ELEMENTS_INDICES,
          GL_MAX_ELEMENTS_VERTICES,
          GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET,
          GL_MAX_VERTEX_ATTRIB_BINDINGS,
          GL_MAX_ELEMENT_INDEX }));

    cout << endl << "Rasterizer information" << endl;
    show(Targets({
          GL_SUBPIXEL_BITS,
          GL_MAX_CLIP_DISTANCES,
          GL_MAX_VIEWPORTS,
          GL_VIEWPORT_SUBPIXEL_BITS }));

    // GLfloat MAX_VIEWPORT_DIMS
    // GLfloat VIEWPORT_BOUNDS_RANGE[2] 

    cout << endl << "Framebuffer information" << endl;
    show(Targets({
          GL_MAX_COLOR_ATTACHMENTS,
          GL_MAX_FRAMEBUFFER_WIDTH,
          GL_MAX_FRAMEBUFFER_HEIGHT,
          GL_MAX_FRAMEBUFFER_LAYERS,
          GL_MAX_FRAMEBUFFER_SAMPLES,
          GL_MAX_RENDERBUFFER_SIZE,
          GL_MAX_SAMPLE_MASK_WORDS }));

    cout << endl << "Buffer information" << endl;
    show(Targets({
          GL_MAX_TRANSFORM_FEEDBACK_BUFFERS,
          GL_MIN_MAP_BUFFER_ALIGNMENT }));

    cout << endl << "Texture information" << endl;
    show(Targets({
          GL_MAX_TEXTURE_IMAGE_UNITS,
          GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
          GL_MAX_TEXTURE_LOD_BIAS,
          GL_MAX_TEXTURE_SIZE,
          GL_MAX_RECTANGLE_TEXTURE_SIZE,
          GL_MAX_3D_TEXTURE_SIZE,
          GL_MAX_ARRAY_TEXTURE_LAYERS,
          GL_MAX_CUBE_MAP_TEXTURE_SIZE,
          GL_MAX_COLOR_TEXTURE_SAMPLES,
          GL_MAX_DEPTH_TEXTURE_SAMPLES,
          GL_MAX_INTEGER_SAMPLES,
          GL_MAX_TEXTURE_BUFFER_SIZE,
          GL_NUM_COMPRESSED_TEXTURE_FORMATS }));
      // GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT

    cout << endl << "Program information" << endl;
    show(Targets({
          GL_MAX_SUBROUTINES,
          GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS,
          GL_MAX_COMBINED_ATOMIC_COUNTERS,
          GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS,
          GL_MAX_PROGRAM_TEXEL_OFFSET,
          GL_MIN_PROGRAM_TEXEL_OFFSET,
          GL_MAX_COMBINED_UNIFORM_BLOCKS,
          GL_MAX_UNIFORM_BUFFER_BINDINGS,
          GL_MAX_UNIFORM_BLOCK_SIZE,
          GL_MAX_UNIFORM_LOCATIONS,
          GL_MAX_VARYING_COMPONENTS,
          GL_MAX_VARYING_VECTORS,
          GL_MAX_VARYING_FLOATS,
          GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS,
          GL_MAX_SHADER_STORAGE_BLOCK_SIZE,
          GL_MAX_COMBINED_SHADER_OUTPUT_RESOURCES,
          GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT,
          GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT,
          GL_NUM_PROGRAM_BINARY_FORMATS,
          GL_NUM_SHADER_BINARY_FORMATS,
          GL_PROGRAM_BINARY_FORMATS }));

    exit(0);
  }

  virtual void render(double t) { }
};

GLMAIN(KW7)
