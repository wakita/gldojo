#define _CRT_SECURE_NO_WARNINGS 1

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <GL/glew.h>

namespace sn {

using std::cerr;
using std::endl;
using std::string;
using std::vector;
  
namespace gl { namespace shader {

extern
GLuint load(string filename, GLenum shader_type, bool check_errors) {
    GLuint shader = 0;

    std::ifstream f(filename.c_str());
    string content((std::istreambuf_iterator<char>(f)),
        std::istreambuf_iterator<char>());
    if (check_errors) {
      std::cerr << filename << endl;
      std::cerr << content << endl;
    }
    const GLchar* source = content.c_str();

    shader = glCreateShader(shader_type);
    if (!shader) goto fail_shader_alloc;
    glShaderSource(shader, 1, &source, NULL);

    glCompileShader(shader);

    if (check_errors) {
      GLint status = 0;
      glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

      if (!status) {
        char info[4096];
        glGetShaderInfoLog(shader, 4096, NULL, info);
        cerr << filename << endl << "info: " << info << endl;
        goto fail_compile_shader;
      }
    }

    return shader;

fail_compile_shader:
    glDeleteShader(shader);

fail_shader_alloc:;
fail_source_alloc:
    return shader;
}

extern
GLuint load(string base, string ext, GLenum shader_type, bool check_errors) {
  string path = base + "." + ext + ".glsl";
  return load(path, shader_type, check_errors);
}

extern
vector<GLuint> load(string base, vector<string> names, bool check_errors) {
  vector<GLuint> shaders {};
  for (const auto name : names) {
    vector<GLuint>::size_type pos = name.find_last_of('.');
    string ext = name.substr(pos);
    GLenum shader_type =
      ext == ".vs"  ? GL_VERTEX_SHADER :
      ext == ".tcs" ? GL_TESS_CONTROL_SHADER :
      ext == ".tes" ? GL_TESS_EVALUATION_SHADER :
      ext == ".gs"  ? GL_GEOMETRY_SHADER :
      ext == ".fs"  ? GL_FRAGMENT_SHADER :
      /* defaults */  GL_COMPUTE_SHADER;
    shaders.push_back(load(base + name, shader_type, check_errors));
  }
  return shaders;
}

} // namespace sn::gl::shader

namespace program {

GLuint link(vector<GLuint> shaders,
            bool delete_shaders,
            bool check_errors) {
  GLuint program = glCreateProgram();
  for (auto shader : shaders) glAttachShader(program, shader);
  glLinkProgram(program);

  if (check_errors) {
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);

    if (!status) {
      char info[4096];
      glGetProgramInfoLog(program, 4096, NULL, info);
      cerr << "Error (" << check_errors << "): " << info << endl;
      glDeleteProgram(program);
      return 0;
    }
  }

  if (delete_shaders) {
    for (auto shader : shaders) glDeleteShader(shader);
  }

  return program;
}

} // namespace sn::gl::program

} } // namespace sn::gl
