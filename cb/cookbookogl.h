#ifndef _GLSLCOOKBOOK_OGL
#define _GLSLCOOKBOOK_OGL

#define APIENTRY
#include <glbinding/gl43/boolean.h>
#include <glbinding/gl43/enum.h>
#include <glbinding/gl43/functions.h>
#include <glbinding/gl43/types.h>
using namespace gl43;

#define GLENUM(v) static_cast<GLenum>(v)
#define GLINT(v)  static_cast<GLint>(v)

#define GLM_FORCE_RADIANS

#endif
