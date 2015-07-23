#pragma once

#include <exception>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glbinding/ContextInfo.h>
#include <glbinding/Version.h>
#include <glbinding/callbacks.h>
#include <glbinding/Meta.h>
#include <glbinding/Binding.h>
#include <glbinding/gl43/gl.h>
using namespace gl43;

#define GLM_FORCE_CXX11
#define GLM_EXT_INCLUDED
#define GLM_FORCE_RADIANS
#define GLM_FORCE_SIZE_FUNC // vec4.length() => vec4.size()
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

#include <json11.hpp>

# ifdef _DEBUG
#   define Check smartnova::gl::GLErrorCheck(__FILE__, __LINE__)
# else
#   define Check
# endif

#include "Utility.hpp"

using smartnova::util::ProgramException;

namespace smartnova {
  
  namespace gl {

// https://gist.github.com/Bigcheese/5148643
struct GLFWwindowDeleter {
  void operator ()(GLFWwindow *window) {
    glfwDestroyWindow(window);
  }
};

void GLErrorCheck(string file, int line);

// void traceAPICalls();

class ShaderException : public runtime_error {
  public:
    ShaderException(const string & msg) : runtime_error(msg) {}
    ShaderException(const string & path, const string & msg) :
      runtime_error("\"" + path + "\": " + msg) {}
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

/**
 * @brief ApplicationクラスはOpenGLアプリケーションの抽象クラスです．
 **/

class Application {
  public:
    static  void initializeGLcontext();
    static  void initialize(json11::Json);
    virtual void init();
    virtual void startup() = 0;
    virtual void render(double currentTime) = 0;
    virtual void shutdown();
    virtual void run();

    virtual void onFramebufferSize(GLFWwindow *win, int w, int h);
    virtual void onResize      (GLFWwindow *win, int w, int h);
    virtual void onKey         (GLFWwindow *win, int key, int scancode, int action, int mods);
    virtual void onMouseButton (GLFWwindow *win, int button, int action, int mods);
    virtual void onCursorPos   (GLFWwindow *win, double xpos, double ypos);
    virtual void onScroll      (GLFWwindow *win, double xoffset, double yoffset);

    virtual void getCursorPos  (GLFWwindow *win, double & xpos, double & ypos);

  protected:
    static SNGL_APP_INFO info;
    static std::unique_ptr<GLFWwindow, GLFWwindowDeleter> Window;
    static std::unique_ptr<Application> App;
    mat4 Projection;
    json11::Json C, A;

    /**
     * @brief デフォルトコンストラクタ
     */
    Application();
    Application(json11::Json config);
    /**
     * @brief 初期化：GLFWウィンドウを取得してglbindingを初期化する．
     * @param title ウィンドウのタイトル
     * GLFWの設定値を定めてGLFWのウィンドウを取得したのちにglbindingを初期化する．
     */
    virtual void init(const string & title);
    void notify(const string & message);
    void setTrace(bool);
    void showFPS(double t);

  private:
    static void setDebugging(bool);
    bool traceP = false;
};

#define GLMAIN(APP)                             \
int main(int argc, char const * const argv[]) { \
  try {                                         \
    json11::Json C = smartnova::util::readConfig(); \
    Application::initialize(C);                 \
    std::unique_ptr<APP> app(new APP(C));       \
    app.get()->run();                           \
    return EXIT_SUCCESS;                        \
  } catch (exception &e) {                      \
    std::cerr <<                                \
      "Caught exception:" << std::endl << "    " << e.what() << std::endl; \
  }                                             \
}

#define DECLARE_MAIN(APP)                         \
int main(int argc, const char ** argv) {          \
  try {                                           \
    Application::initializeGLcontext();           \
    APP *app = new APP();                         \
    app->run();                                   \
    delete app;                                   \
    return EXIT_SUCCESS;                          \
  } catch (exception& e) {                        \
    cerr << "Caught exception \"" << e.what() << "\"\n"; \
  }                                               \
}

namespace Shader {
  static map<string, GLenum> typeOfExt = map<string, GLenum>({
      { string("vs"),   GL_VERTEX_SHADER },
      { string("tcs"),  GL_TESS_CONTROL_SHADER },
      { string("tes"),  GL_TESS_EVALUATION_SHADER },
      { string("geom"), GL_GEOMETRY_SHADER },
      { string("gs"),   GL_GEOMETRY_SHADER },
      { string("fs"),   GL_FRAGMENT_SHADER  },
      { string("comp"), GL_COMPUTE_SHADER },
      { string("cs"),   GL_COMPUTE_SHADER  } });

  static GLenum typeOf(const string & path);

  void throwOnShaderError(GLuint shader, GLenum pname, const string &message);
  void throwOnShaderError(GLuint shader, GLenum pname, const string &path, const string & message);
}

class UniformSpec {
  public:
    string name;
    GLenum type;
    GLint location;

    UniformSpec();
    UniformSpec(string n, GLenum type, GLint location);
};

class Program {
  private:
    GLuint handle;
    bool linked;

    void throwOnProgramError(GLenum pname, const string & message);
    void throwOnProgramError(GLenum pname, const string & path, const string & message);

    Program(const Program & other) {}
    Program & operator=(const Program &other) { return *this; }

    map<string, GLint> uniformLocations;
    map<string, std::unique_ptr<UniformSpec>> uniforms;
    list<string> uniformBlocks;

    void analyzeActiveUniforms();
    void analyzeActiveUniformBlocks();

  public:
    Program();
    ~Program();

    void compile(const string & path) throw (ProgramException);
    void compile(const string & path, GLenum type) throw (ProgramException);
    void compile(const string & source, GLenum type, const string & path)
      throw (ProgramException);
    void load(const json11::Json &shaderset) throw (ProgramException);
    void load(const json11::Json &shaderset, const int) throw (ProgramException);
    void load(const string &stem, vector<string> exts) throw (ProgramException);
    void load(const string &stem, string exts) throw (ProgramException);
    // static void loadall(vector<Program> &, const json11::Json&) throw (ProgramException);

    void link() throw (ProgramException);
    void validate() throw (ProgramException);
    void use() throw (ProgramException);

    GLuint getHandle();
    bool isLinked();

    void bindAttribLocation(GLuint location, const char * name);
    void bindFragDataLocation(GLuint location, const char * name);

    GLint uniformLocation(const char* name);

    void setUniform(const string &spec, const json11::Json &x);
    void setUniforms(const string &name, const json11::Json &x);
    void setUniformBlock(const string &block, const json11::Json &x);

    void setUniform(const char * name, float x, float y, float z);
    void setUniform(const char * name, double x, double y, double z);
    void setUniform(const char * name, const vec2 & v);
    void setUniform(const char * name, const vec3 & v);
    void setUniform(const char * name, const vec4 & v);
    void setUniform(const char * name, const mat3 & m);
    void setUniform(const char * name, const mat4 & m);
    void setUniform(const char * name, double x);
    void setUniform(const char * name, float x);
    void setUniform(const char * name, int x);
    void setUniform(const char * name, bool x);
    void setUniform(const char * name, GLuint x);

    void setUniform(const string &name, const string &type, json11::Json&x);

    void printActiveUniforms();
    void printActiveUniformBlocks();
    void printActiveAttribs();
};

const char * getTypeString(GLint type);
} } // namespace smartnova::gl
