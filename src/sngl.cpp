#include <string>

#include "sngl.hpp"

// #include <GL/glext.h>

namespace sn { namespace gl {

  Application * Application::app = 0;

  void * GetProcAddress(const char * funcname) {
    return GetProcAddress(funcname);
  }

  int IsExtensionSupported(const char * extname) {
    GLint numExtensions;
    GLint i;

    glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);

    for (i = 0; i < numExtensions; i++) {
      const GLubyte * e = glGetStringi(GL_EXTENSIONS, i);
      if (!strcmp((const char *)e, extname)) {
        return 1;
      }
    }

    return 0;
  }

}; }; // namespace sn::gl
