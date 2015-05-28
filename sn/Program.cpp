#include <iostream>
#include <fstream>

//#define _DEBUG
#include "Program.hpp"

namespace smartnova { namespace gl {

void traceAPICalls() {
  setCallbackMask(CallbackMask::Unresolved | CallbackMask::BeforeAndAfter | CallbackMask::ParametersAndReturnValue);

  setUnresolvedCallback([](const AbstractFunction & f) {
        cerr << "Unresolved API (" << f.name() << ") was called" << endl;
      });

  setBeforeCallback([](const FunctionCall & call) {
        cerr << ">>> " << call.function->name();
      });

  setAfterCallback([](const FunctionCall & call) {
      cerr << "(";
      for (unsigned i = 0; i < call.parameters.size(); ++i) {
        cerr << call.parameters[i]->asString();
        if (i < call.parameters.size() - 1) cerr << ", ";
      }
      cerr << ")" << endl;
      });
}

void GLErrorCheck(string file, int line) {
  GLenum err = glGetError();
  if (err == GL_NO_ERROR) return;
  cerr << "Error at line " << line << " in file " << file << ": " <<
    (err == GL_INVALID_ENUM ? "Invalid enum value" :
     err == GL_INVALID_VALUE ? "Invalid value" :
     err == GL_INVALID_OPERATION ? "Invalid operation" :
     err == GL_INVALID_FRAMEBUFFER_OPERATION ? "Invalid framebuffer operation" :
     err == GL_OUT_OF_MEMORY ? "Out of memory" :
     err == GL_STACK_UNDERFLOW ? "Stack underflow" :
     err == GL_STACK_OVERFLOW ? "Stack overflow" :
     "Unknown error") << endl;
}

Application *Application::app;

Application::Application() {
  info.winWidth      = 800;
  info.winWidth      = 800;
  info.winHeight     = 600;
  info.majorVersion  = 4;
  info.minorVersion  = 1;
  // info.samples       = 0;
  info.flags.all     = 0;
  info.flags.visible = 1;
  info.flags.cursor  = 1;
  info.flags.debug   = 1;
}

void Application::init(const string & title) {
  app        = this;
  info.title = title;

  cerr << "Application::init [" << title << "]" << endl;

  if (!glfwInit()) {
    cerr << "Failed to initialize GLFW" << endl;
    exit(EXIT_FAILURE);
  }
  cerr << "glfwInit() done!" << endl;

  glfwSetErrorCallback([] (int error, const char* description) {
      cerr << "GLFW Error (" << error << "): " << description << endl; });

  glfwDefaultWindowHints();
# if defined(OS_Darwin)
  cerr << "Darwin" << endl;
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, info.majorVersion);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, info.minorVersion);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
  glfwWindowHint(GLFW_OPENGL_PROFILE,        GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_SAMPLES,               info.samples);
  glfwWindowHint(GLFW_STEREO,                info.flags.stereo);
  glfwWindowHint(GLFW_VISIBLE,               info.flags.visible);
# endif
  cerr << "glfwWindowHints done!" << endl;

  GLFWmonitor *monitor = nullptr;
  int swapInterval = 1;
  if (info.flags.fullscreen) {
    int monitor_count;
    GLFWmonitor**monitors = glfwGetMonitors(&monitor_count);
    monitor = monitors[0];
    if (info.winWidth == 0 || info.winHeight == 0) {
      const GLFWvidmode *videoMode = glfwGetVideoMode(monitor);
      info.winWidth  = videoMode->width;
      info.winHeight = videoMode->height;
    }
    swapInterval = info.flags.vsync;
  }

  cerr << "Trying to create a GLFW window...";
  if (!(window = glfwCreateWindow(
          info.winWidth, info.winHeight,
          info.title.c_str(),
          monitor, nullptr))) {
    cerr << "Failed to open window" << endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  cerr << "  done." << endl;

  Binding::addContextSwitchCallback([](ContextHandle handle) {
      cerr << "Activating context " << handle << endl;
      });

  cerr << "Initializing GLFW context...";
  glfwMakeContextCurrent(window);
  cerr << "  done." << endl;
  // glfwSwapInterval(swapInterval);

  cerr << "Registering callbacks...";
  // Register various callbacks
  glfwSetFramebufferSizeCallback(window,
      [] (GLFWwindow *win, int w, int h) {
      app->onFramebufferSize(win, w, h); });
  glfwSetWindowSizeCallback(window,
      [] (GLFWwindow *win, int w, int h) {
      app->onResize(win, w, h); });
  glfwSetKeyCallback(window,
      [] (GLFWwindow *win, int key, int scancode, int action, int mods) {
      app->onKey(win, key, scancode, action, mods); });
  glfwSetMouseButtonCallback(window,
      [] (GLFWwindow *win, int button, int action, int mods) {
      app->onMouseButton(win, button, action, mods); });
  glfwSetCursorPosCallback(window,
      [] (GLFWwindow *win, double xpos, double ypos) {
      app->onCursorPos(win, xpos, ypos); });
  glfwSetScrollCallback(window,
      [] (GLFWwindow *win, double xoffset, double yoffset) {
      app->onScroll(win, xoffset, yoffset); });
  cerr << "  done." << endl;

  glfwSetInputMode(window, GLFW_CURSOR,
      info.flags.cursor ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);

  glbinding::Binding::initialize();
# if defined(_DEBUG)
  cerr <<
    "OpenGL Version:  " << ContextInfo::version()  << endl <<
    "OpenGL Vendor:   " << ContextInfo::vendor()   << endl <<
    "OpenGL Renderer: " << ContextInfo::renderer() << endl <<
    "OpenGL Revision: " << Meta::glRevision() << " (gl.xml)" << endl <<
    "GLSL Version:    " << glGetString(GL_SHADING_LANGUAGE_VERSION) <<
    endl << endl;
  // cerr << "Extention: " << glGetString(GL_EXTENSIONS) << endl;
  Check;
# endif // _DEBUG

# if defined(_DEBUG)
  setCallbackMask(CallbackMask::Unresolved | CallbackMask::BeforeAndAfter | CallbackMask::ParametersAndReturnValue);
  cerr << "Setting callbacks for unresolved API calls...  ";
  setUnresolvedCallback([](const AbstractFunction & f) {
      cerr << "Unresolved API (" << f.name() << ") was called" << endl;
      });
  cerr << "Setting before&after callbacks for API calls...  ";
  setBeforeCallback([](const FunctionCall & call) {
      cerr << ">>> " << call.function->name();
      });
  setAfterCallback([](const FunctionCall & call) {
      cerr << "(";
      for (unsigned i = 0; i < call.parameters.size(); ++i) {
        cerr << call.parameters[i]->asString();
        if (i < call.parameters.size() - 1) cerr << ", ";
      }
      cerr << ")" << endl;
      });
  cerr << "done." << endl;
  Check;
# endif
}

void Application::shutdown() {
  glfwDestroyWindow(window);
  glfwTerminate();
  app->~Application();
}

void Application::run() {
  init();
  startup();

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    render(glfwGetTime());
    glfwSwapBuffers(window);
  }
  shutdown();
  exit(EXIT_SUCCESS);
}

void Application::onFramebufferSize(GLFWwindow *win, int w, int h) {
  onResize(win, w, h);
}

void Application::onResize(GLFWwindow *win, int w, int h) {
  info.winWidth = w; info.winHeight = h;
}

void Application::onKey(GLFWwindow *win, int key, int scancode, int action, int mods) {
  if ((key == GLFW_KEY_Q || key == GLFW_KEY_ESCAPE) && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

void Application::onMouseButton(GLFWwindow *win, int button, int action, int mods) {}
void Application::onCursorPos(GLFWwindow *win, double xpos, double ypos) {}
void Application::onScroll(GLFWwindow *win, double xoffset, double yoffset) {}

void Application::getCursorPos(GLFWwindow *window, double &xpos, double &ypos) {}

void Application::onDebugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar &message) {}

// Bug: Extract the extension!
static GLenum Shader::typeOf(const string &path) {
  const string::size_type i = path.rfind('.');
  return typeOfExt.find(path.substr(i))->second;
}

void Shader::throwOnShaderError(GLuint shader, GLenum pname, const string &message) {
  int result;
  glGetShaderiv(shader, pname, &result);
  if (result == false) {
    int length = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
    string log;
    if (length > 0) {
      char *_log = new char[length];
      int written = 0;
      glGetShaderInfoLog(shader, length, &written, _log);
      log = _log;
      delete[] _log;
    } else {
      log = "No further error information available, sorry.";
    }
    throw ShaderException(message + "\n" + log);
  }
}

void Program::throwOnProgramError(GLenum pname, const string &message) {
  int result;
  glGetProgramiv(handle, pname, &result);
  if (result == false) {
    int length = 0;
    glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &length);
    string log;
    if (length > 0) {
      char *_log = new char[length];
      int written = 0;
      glGetProgramInfoLog(handle, length, &written, _log);
      log = _log;
      delete [] _log;
    } else {
      log = "No further error information available, sorry.";
    }
    cerr << endl;
    throw ProgramException(message + "\n" + log);
  }
}

void Program::throwOnProgramError(GLenum pname, const string &path, const string &message) {
  throwOnProgramError(pname, path + ": " + message);
}

Program::Program() : handle(0), linked(false) {}

Program::~Program() {
  if (handle == 0) return;

  GLint nShaders = 0;
  glGetProgramiv(handle, GL_ATTACHED_SHADERS, &nShaders);

  GLuint *shaderNames = new GLuint[nShaders];
  glGetAttachedShaders(handle, nShaders, nullptr, shaderNames);

  for (int i = 0; i < nShaders; i++) glDeleteShader(shaderNames[i]);
  glDeleteProgram(handle);
  delete[] shaderNames;
}

void Program::compile(const string &source, GLenum type, const string &path)
  throw (ProgramException) {
    if (handle <= 0) {
      handle = glCreateProgram();
      if (handle == 0) throw ProgramException(path, "Unable to create shader program.");
    }

    GLuint shader = glCreateShader(type);
    Check;
    const char *c_code = source.c_str();
    glShaderSource(shader, 1, &c_code, nullptr);
    Check;
    glCompileShader(shader);
    Check;
    Shader::throwOnShaderError(shader, GL_COMPILE_STATUS,
        string("Shader compilation failed for \"") + path + "\"");
    glAttachShader(handle, shader);
  }

void Program::compile(const string &path, GLenum type)
  throw (ProgramException) {
    ifstream f(path.c_str());
    if (!f) throw ProgramException(path, "Unable to open a shader (" + path + ")");
    string code((istreambuf_iterator<char>(f)), istreambuf_iterator<char>());

    compile(code, type, path);
  }

void Program::compile(const string &path)
  throw (ProgramException) {
    compile(path, Shader::typeOf(path));
  }

void Program::load(const string &stem, vector<string> exts)
  throw (ProgramException) {
  const char *dir = getenv("SHADERS_DIR");
  const string base(dir ? dir : "shaders");
  for (const auto ext : exts)
    Program::compile(base + "/" + stem + "." + ext);
  Program::link();
}

void Program::link() throw (ProgramException) {
  if (linked) return;
  if (handle <= 0) throw ProgramException("Program has not been created.");

  glLinkProgram(handle);
  throwOnProgramError(GL_LINK_STATUS, "Program link failed.");
  uniformLocations.clear();
  linked = true;
}

void Program::use() throw (ProgramException) {
  if (handle <= 0 || (!linked)) throw ProgramException("Shader has not been linked");

  glUseProgram(handle);
}

GLuint Program::getHandle() { return handle; }
bool Program::isLinked() { return linked; }

void Program::bindAttribLocation(GLuint location, const char *name) {
  glBindAttribLocation(handle, location, name);
}

void Program::bindFragDataLocation(GLuint location, const char *name) {
  glBindFragDataLocation(handle, location, name);
}

void Program::setUniform(const char *name, const vec2 &v) {
  glUniform2f(uniformLocation(name), v.x, v.y);
}

void Program::setUniform(const char *name, const vec3 &v) {
  setUniform(name, v.x, v.y, v.z);
}

void Program::setUniform(const char *name, float x, float y, float z) {
  glUniform3f(uniformLocation(name), x, y, z);
}

#define SET_UNIFORM_M(suffix, T) \
  void Program::setUniform(const char *name, const T &m) { \
    glUniformMatrix##suffix(uniformLocation(name), 1, GL_FALSE, &m[0][0]); \
  }

SET_UNIFORM_M(3fv, mat3)
SET_UNIFORM_M(4fv, mat4)

#define SET_UNIFORM(suffix, T) \
void Program::setUniform(const char *name, const T x) { \
  glUniform##suffix(uniformLocation(name), x); \
}

SET_UNIFORM(1f,  float)
SET_UNIFORM(1i,  int)
SET_UNIFORM(1ui, GLuint)
SET_UNIFORM(1i, bool)

void Program::printActiveUniforms() {
  GLint numUniforms = 0;
  glGetProgramInterfaceiv(handle, GL_UNIFORM, GL_ACTIVE_RESOURCES, &numUniforms);

  GLenum properties[] = {GL_NAME_LENGTH, GL_TYPE, GL_LOCATION, GL_BLOCK_INDEX};
  cout << "Active uniforms:" << endl;
  for (int i = 0; i < numUniforms; ++i) {
    GLint results[4];
    glGetProgramResourceiv(handle, GL_UNIFORM, i, 4, properties, 4, nullptr, results);
    if (results[3] != -1) continue;
    GLint nameBufSize = results[0] + 1;
    char *name = new char[nameBufSize];
    glGetProgramResourceName(handle, GL_UNIFORM, i, nameBufSize, nullptr, name);
    cout << results[2] << " " << name << " " << getTypeString(results[1]) << endl;
    delete [] name;
  }
}

void Program::printActiveUniformBlocks() {
  GLint numBlocks = 0;

  glGetProgramInterfaceiv(handle, GL_UNIFORM_BLOCK, GL_ACTIVE_RESOURCES, &numBlocks);
  GLenum blockProps[] = {GL_NUM_ACTIVE_VARIABLES, GL_NAME_LENGTH};
  GLenum blockIndex[] = {GL_ACTIVE_VARIABLES};
  GLenum props[] = {GL_NAME_LENGTH, GL_TYPE, GL_BLOCK_INDEX};

  for(int block = 0; block < numBlocks; ++block) {
    GLint blockInfo[2];
    glGetProgramResourceiv(handle, GL_UNIFORM_BLOCK, block, 2, blockProps, 2, nullptr, blockInfo);
    GLint numUnis = blockInfo[0];

    char *blockName = new char[blockInfo[1]+1];
    glGetProgramResourceName(handle, GL_UNIFORM_BLOCK, block, blockInfo[1]+1, nullptr, blockName);
    cout << "Uniform block \"" << blockName << "\":" << endl;
    delete [] blockName;

    GLint *unifIndexes = new GLint[numUnis];
    glGetProgramResourceiv(handle, GL_UNIFORM_BLOCK, block, 1, blockIndex, numUnis, nullptr, unifIndexes);

    for( int unif = 0; unif < numUnis; ++unif ) {
      GLint uniIndex = unifIndexes[unif];
      GLint results[3];
      glGetProgramResourceiv(handle, GL_UNIFORM, uniIndex, 3, props, 3, nullptr, results);

      GLint nameBufSize = results[0] + 1;
      char *name = new char[nameBufSize];
      glGetProgramResourceName(handle, GL_UNIFORM, uniIndex, nameBufSize, nullptr, name);
      cout << "    " << name << " (" << getTypeString(results[1]) << ")" << endl;
      delete [] name;
    }

    delete [] unifIndexes;
  }
}

void Program::printActiveAttribs() {
  GLint numAttribs;
  glGetProgramInterfaceiv( handle, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &numAttribs);

  GLenum properties[] = {GL_NAME_LENGTH, GL_TYPE, GL_LOCATION};

  printf("Active attributes:\n");
  for( int i = 0; i < numAttribs; ++i ) {
    GLint results[3];
    glGetProgramResourceiv(handle, GL_PROGRAM_INPUT, i, 3, properties, 3, nullptr, results);

    GLint nameBufSize = results[0] + 1;
    char *name = new char[nameBufSize];
    glGetProgramResourceName(handle, GL_PROGRAM_INPUT, i, nameBufSize, nullptr, name);
    cout << results[2] << " " << name << " (" << getTypeString(results[1]) << ")" << endl;
    delete [] name;
  }
}

void Program::validate() throw (ProgramException) {
  if (! isLinked()) throw ProgramException("Program is not linked");
  throwOnProgramError(GL_VALIDATE_STATUS, "Program failed to validate.");
}

int Program::uniformLocation(const char *name) {
  if (uniformLocations.find(name) == uniformLocations.end())
    uniformLocations[name] = glGetUniformLocation(handle, name);
  return uniformLocations[name];
}

const char *getTypeString(GLint type) { // There are many more types than are covered here, but
  // these are the most common in these examples.
  switch ((GLenum)type) {
    case GL_FLOAT:
      return "float";
    case GL_FLOAT_VEC2:
      return "vec2";
    case GL_FLOAT_VEC3:
      return "vec3";
    case GL_FLOAT_VEC4:
      return "vec4";
    case GL_DOUBLE:
      return "double";
    case GL_INT:
      return "int";
    case GL_UNSIGNED_INT:
      return "unsigned int";
    case GL_BOOL:
      return "bool";
    case GL_FLOAT_MAT2:
      return "mat2";
    case GL_FLOAT_MAT3:
      return "mat3";
    case GL_FLOAT_MAT4:
      return "mat4";
    default:
      return "?";
  }
}

} } // namespace smartnova::gl
