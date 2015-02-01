#include <vector>

#ifndef __SN_SHADER_HPP__
#define __SN_SHADER_HPP__

namespace sn { namespace gl {

using std::string;

namespace shader {
GLuint load(string filename,
            GLenum shader_type = GL_FRAGMENT_SHADER,
#ifdef _DEBUG
            bool check_errors = true);
#else
            bool check_errors = false);
#endif

GLuint load(string base, string ext,
            GLenum shader_type = GL_FRAGMENT_SHADER,
#ifdef _DEBUG
            bool check_errors = true);
#else
            bool check_errors = false);
#endif

std::vector<GLuint> load(string base, std::vector<string> names,
#ifdef _DEBUG
            bool check_errors = true);
#else
            bool check_errors = false);
#endif
} // namespace sn::shader

namespace program {
  GLuint link(std::vector<GLuint> shaders,
              bool delete_shaders,
#ifdef _DEBUG
      bool check_errors = true);
#else
      bool check_errors = false);
#endif
} // namespace sn::program

} } // namespace sn::gl

#endif /* __SN_SHADER_HPP__ */
