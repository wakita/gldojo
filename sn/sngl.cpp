#include <string>

#include "sngl.hpp"

// #include <GL/glext.h>

namespace sn { namespace gl {

void check(string file, int line) {
  GLenum err = glGetError();
  if (err == GL_NO_ERROR) return;
  cerr << "Error at line " << line << " in file " << file << ": " <<
    (err == GL_INVALID_ENUM ?    "Invalid enum value" :
     err == GL_INVALID_VALUE ?   "Invalid value" :
     err == GL_INVALID_OPERATION ? "Invalid operation" :
     err == GL_INVALID_FRAMEBUFFER_OPERATION ? "Invalid framebuffer operation" :
     err == GL_OUT_OF_MEMORY ?   "Out of memory" :
     err == GL_STACK_UNDERFLOW ? "Stack underflow" :
     err == GL_STACK_OVERFLOW ?  "Stack overflow" :
     /* Unrecognized error */    "Unknown error") << endl;
}

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
