#ifndef SMARTNOVA_GL_PROGRAM_HPP
#define SMARTNOVA_GL_PROGRAM_HPP

#include <exception>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat3;
using glm::mat4;

template <template <typename, glm::precision> class matType,
          typename T, glm::precision P>
          ostream & operator<<(ostream & out, const matType<T, P> & x) {
            return out << glm::to_string(x);
          }

static const float PI = glm::pi<float>();
static const vec3 X = vec3(1, 0, 0), Y = vec3(0, 1, 0), Z = vec3(0, 0, 1);
static const mat4 I4 = mat4(1);

#ifdef _DEBUG
#  define Check smartnova::gl::GLErrorCheck(__FILE__, __LINE__)
#else
#  define Check
#endif

namespace smartnova { namespace gl {

void GLErrorCheck(string file, int line);

// ToDo: should be replaced with fs::filesystem_error
class ShaderException : public runtime_error {
  public:
    ShaderException(const string & msg) : runtime_error(msg) {}
    ShaderException(const fs::path & path, const string & msg) :
      runtime_error("\"" + path.filename().native() + "\": " + msg) {}
};

class ProgramException : public runtime_error {
  public:
    ProgramException(const string & msg) : runtime_error(msg) {}
    ProgramException(const fs::path & path, const string & msg) :
      runtime_error("\"" + path.filename().native() + "\": " + msg) {}
};

struct SNGL_APP_INFO {
  string title;
  int winWidth, winHeight;
  int majorVersion, minorVersion;
  int samples;
  union {
    struct {
      unsigned int    visible     : 1;
      unsigned int    fullscreen  : 1;
      unsigned int    vsync       : 1;
      unsigned int    cursor      : 1;
      unsigned int    stereo      : 1;
      unsigned int    debug       : 1;
    };
    unsigned int      all;
  } flags;
};

class Application {
  public:
    virtual void init(const string & title);
    virtual void init() {}
    virtual void startup() = 0;
    virtual void render(double currentTime) = 0;
    virtual void shutdown();
    virtual void run();

    virtual void onResize      (GLFWwindow *win, int w, int h);
    virtual void onKey         (GLFWwindow *win, int key, int scancode, int action, int mods);
    virtual void onMouseButton (GLFWwindow *win, int button, int action, int mods);
    virtual void onCursorPos   (GLFWwindow *win, double xpos, double ypos);
    virtual void onScroll      (GLFWwindow *win, double xoffset, double yoffset);

    virtual void getCursorPos  (GLFWwindow *win, double & xpos, double & ypos);

    virtual void onDebugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar &message);

  protected:
    Application();
    SNGL_APP_INFO info;
    static Application *app;
    GLFWwindow *window = nullptr;
};

#define DECLARE_MAIN(APP)                         \
int main(int argc, const char ** argv) {          \
  try {                                           \
    APP *app = new APP();                         \
    app->run();                                   \
    delete app;                                   \
    return EXIT_SUCCESS;                          \
  } catch (exception& e) {                        \
    cerr << "Caught exception \"" << e.what() << "\"\n"; \
  }                                               \
}

namespace Shader {
  enum Type {
    VS = GL_VERTEX_SHADER,
    TCS = GL_TESS_CONTROL_SHADER,
    TES = GL_TESS_EVALUATION_SHADER,
    GS = GL_GEOMETRY_SHADER,
    FS = GL_FRAGMENT_SHADER,
    CS = GL_COMPUTE_SHADER };

  static map<fs::path, Type> typeOfExt = map<fs::path, Type>({
      { fs::path(".vs"), VS }, { fs::path(".tcs"), TCS }, { fs::path(".tes"), TES },
      { fs:: path(".geom"), GS }, { fs::path(".gs"), GS }, { fs::path(".fs"),  FS  },
      { fs::path(".comp"), CS }, { fs::path(".cs"),  CS  } });

  static Type typeOf(const fs::path & path);

  void throwOnShaderError(GLuint shader, GLenum pname, const string &message);
  void throwOnShaderError(GLuint shader, GLenum pname, const fs::path &path, const string & message);
}

static map<GLenum, const char *> _type2Name =
map<GLenum, const char *>({
    { GL_FLOAT, "float" }, { GL_FLOAT_VEC2, "vec2" }, { GL_FLOAT_VEC3, "vec3" },
    { GL_FLOAT_VEC4, "vec4" }, { GL_DOUBLE, "double" }, { GL_INT, "int" },
    { GL_UNSIGNED_INT, "unsigned int" }, { GL_BOOL, "bool" }, { GL_FLOAT_MAT2, "mat2" },
    { GL_FLOAT_MAT3, "mat3" }, { GL_FLOAT_MAT4, "mat4" } });

class Program {
  private:
    GLuint handle;
    bool linked;
    map<string, GLint> uniformLocations;

    void throwOnProgramError(GLenum pname, const string & message);
    void throwOnProgramError(GLenum pname, const fs::path & path, const string & message);

    Program(const Program & other) {}
    Program & operator=(const Program &other) { return *this; }

  public:
    Program();
    ~Program();

    void compile(const fs::path & path) throw (ProgramException);
    void compile(const fs::path & path, Shader::Type type) throw (ProgramException);
    void compile(const string & source, Shader::Type type, const fs::path & path)
      throw (ProgramException);
    void load(const string &stem, vector<string> exts) throw (ProgramException);

    void link() throw (ProgramException);
    void validate() throw (ProgramException);
    void use() throw (ProgramException);

    GLuint getHandle();
    bool isLinked();

    void bindAttribLocation(GLuint location, const char * name);
    void bindFragDataLocation(GLuint location, const char * name);

    GLint uniformLocation(const char* name);

    void setUniform(const char * name, float x, float y, float z);
    void setUniform(const char * name, const vec2 & v);
    void setUniform(const char * name, const vec3 & v);
    void setUniform(const char * name, const vec4 & v);
    void setUniform(const char * name, const mat3 & m);
    void setUniform(const char * name, const mat4 & m);
    void setUniform(const char * name, float val);
    void setUniform(const char * name, int x);
    void setUniform(const char * name, bool x);
    void setUniform(const char * name, GLuint x);

    void printActiveUniforms();
    void printActiveUniformBlocks();
    void printActiveAttribs();
};

const char * getTypeString(GLenum type);
} } // namespace smartnova::gl

#endif
