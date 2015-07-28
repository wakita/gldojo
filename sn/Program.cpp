#include <iomanip>
#include <iterator>
#include <fstream>
#include <regex>
#include <sstream>

#define _DEBUG
#include "Utility.hpp"
#include "Program.hpp"

using json11::Json;

namespace smartnova { namespace gl {

SNGL_APP_INFO Application::info;
std::unique_ptr<GLFWwindow, GLFWwindowDeleter> Application::Window(nullptr);
std::unique_ptr<Application> Application::App(nullptr);

// Application *Application::app;

Application::Application() { }
Application::Application(json11::Json config) {
  C = config;
  A = config["app"];
}

void Application::initialize(json11::Json C) {
  cout << "Application::initialize(Json)" << endl;
  if (!glfwInit()) {
    cerr << "Failed to initialize GLFW" << endl;
    exit(EXIT_FAILURE);
  }

  glfwSetErrorCallback([] (int error, const char* description) {
    cerr << "GLFW Error (" << error << "): " << description << endl; });

  glfwDefaultWindowHints();

  int swapInterval = 1;

  json11::Json GLFW = C["glfw"];
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLFW["version"].array_items()[0].int_value());
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLFW["version"].array_items()[1].int_value());

  GLFWmonitor *monitor = nullptr;
  if (GLFW["fullscreen"].bool_value()) {
    cout << "fullscreen" << endl;
    int monitor_count;
    GLFWmonitor**monitors = glfwGetMonitors(&monitor_count);
    monitor = monitors[0];
    const GLFWvidmode *videoMode = glfwGetVideoMode(monitor);
    info.winWidth = videoMode->width;
    info.winHeight = videoMode->height;
  } else {
    if (GLFW[ "windowSize" ].is_array()) {
      json11::Json::array size = GLFW[ "windowSize" ].array_items();
      info.winWidth  = size[0].int_value();
      info.winHeight = size[1].int_value();
    } else {
      info.winWidth  = 800;
      info.winHeight = 600;
    }
  }

  Window.reset(
      glfwCreateWindow(info.winWidth, info.winHeight,
        info.title.c_str(),
        monitor, nullptr));
  if (!Window.get()) {
    cerr << "Failed to open window" << endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  GLFWwindow *window = Window.get();

  glfwGetWindowSize(window, &info.winWidth, &info.winHeight);

# if defined(_DEBUG)
  glbinding::Binding::addContextSwitchCallback([](glbinding::ContextHandle handle) {
    cerr << "OpenGL.Marker[Notify](0): Activating context (" << handle << ")" << endl;
  });
# endif

  glfwMakeContextCurrent(window);
  // glfwSwapInterval(swapInterval);

  // Callbacks
  glfwSetFramebufferSizeCallback(
    window, [] (GLFWwindow *win, int w, int h) {
      App.get()->onFramebufferSize(win, w, h); });
  glfwSetWindowSizeCallback(
    window, [] (GLFWwindow *win, int w, int h) {
      App.get()->onResize(win, w, h); });
  glfwSetKeyCallback(
    window, [] (GLFWwindow *win, int key, int scancode, int action, int mods) {
      App.get()->onKey(win, key, scancode, action, mods); });
  glfwSetMouseButtonCallback(
    window, [] (GLFWwindow *win, int button, int action, int mods) {
      App.get()->onMouseButton(win, button, action, mods); });
  glfwSetCursorPosCallback(
    window, [] (GLFWwindow *win, double xpos, double ypos) {
      App.get()->onCursorPos(win, xpos, ypos); });
  glfwSetScrollCallback(
    window, [] (GLFWwindow *win, double xoffset, double yoffset) {
      App.get()->onScroll(win, xoffset, yoffset); });

  glfwSetInputMode(window, GLFW_CURSOR,
      GLFW[ "cursor" ].bool_value() ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);

# if defined(_DEBUG)
  cerr << "App.Marker[Notify](0): Initialization of GLFW completed" << endl;
# endif

  glbinding::Binding::initialize();

# if defined(_DEBUG)
  cerr << "App.Marker[Notify](0): OpenGL API binding completed" << endl;
  setDebugging(true);
# endif
}

void Application::initializeGLcontext() {
  info.winWidth      = 800;
  info.winHeight     = 600;
  info.majorVersion  = 4;
  info.minorVersion  = 1;
  // info.samples       = 0;
  info.flags.all     = 0;
  info.flags.visible = 1;
  info.flags.cursor  = 1;
  info.flags.debug   = 1;

  if (!glfwInit()) {
    cerr << "Failed to initialize GLFW" << endl;
    exit(EXIT_FAILURE);
  }

  glfwSetErrorCallback([] (int error, const char* description) {
    cerr << "GLFW Error (" << error << "): " << description << endl; });

  glfwDefaultWindowHints();

  int swapInterval = 1;

  GLFWmonitor *monitor = nullptr;
  if (info.flags.fullscreen) {
    int monitor_count;
    GLFWmonitor**monitors = glfwGetMonitors(&monitor_count);
    monitor = monitors[0];
    const GLFWvidmode *videoMode = glfwGetVideoMode(monitor);
    info.winWidth  = videoMode->width;
    info.winHeight = videoMode->height;
    swapInterval = info.flags.vsync;
  }

  Window.reset(
      glfwCreateWindow(info.winWidth, info.winHeight,
        info.title.c_str(),
        monitor, nullptr));
  if (!Window.get()) {
    cerr << "Failed to open window" << endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  GLFWwindow *window = Window.get();

  glfwGetWindowSize(window, &info.winWidth, &info.winHeight);

# if defined(_DEBUG)
  glbinding::Binding::addContextSwitchCallback([](glbinding::ContextHandle handle) {
    cerr << "OpenGL.Marker[Notify](0): Activating context (" << handle << ")" << endl;
  });
# endif

  glfwMakeContextCurrent(window);
  // glfwSwapInterval(swapInterval);

  // Callbacks
  glfwSetFramebufferSizeCallback(
    window, [] (GLFWwindow *win, int w, int h) {
      App.get()->onFramebufferSize(win, w, h); });
  glfwSetWindowSizeCallback(
    window, [] (GLFWwindow *win, int w, int h) {
      App.get()->onResize(win, w, h); });
  glfwSetKeyCallback(
    window, [] (GLFWwindow *win, int key, int scancode, int action, int mods) {
      App.get()->onKey(win, key, scancode, action, mods); });
  glfwSetMouseButtonCallback(
    window, [] (GLFWwindow *win, int button, int action, int mods) {
      App.get()->onMouseButton(win, button, action, mods); });
  glfwSetCursorPosCallback(
    window, [] (GLFWwindow *win, double xpos, double ypos) {
      App.get()->onCursorPos(win, xpos, ypos); });
  glfwSetScrollCallback(
    window, [] (GLFWwindow *win, double xoffset, double yoffset) {
      App.get()->onScroll(win, xoffset, yoffset); });

  glfwSetInputMode(window, GLFW_CURSOR,
      info.flags.cursor ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);

# if defined(_DEBUG)
  cerr << "App.Marker[Notify](0): Initialization of GLFW completed" << endl;
# endif

  glbinding::Binding::initialize();

# if defined(_DEBUG)
  cerr << "App.Marker[Notify](0): OpenGL API binding completed" << endl;
  setDebugging(true);
# endif
}

void GLErrorCheck() {
  GLenum err = glGetError();
  if (err == GL_NO_ERROR) return;
  cerr << "Error: " <<
    (err == GL_INVALID_ENUM ? "Invalid enum value" :
     err == GL_INVALID_VALUE ? "Invalid value" :
     err == GL_INVALID_OPERATION ? "Invalid operation" :
     err == GL_INVALID_FRAMEBUFFER_OPERATION ? "Invalid framebuffer operation" :
     err == GL_OUT_OF_MEMORY ? "Out of memory" :
     err == GL_STACK_UNDERFLOW ? "Stack underflow" :
     err == GL_STACK_OVERFLOW ? "Stack overflow" :
     "Unknown error") <<
    endl;
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
     "Unknown error") <<
    endl;
}

void Application::setTrace(bool trace) {
  if (trace != traceP) cerr << endl;
  traceP = trace;
}


const double MeasurementTime = 0.5;
int renderedFrames = 0;
double dueTime = -1;

void Application::showFPS(double t) {
  renderedFrames++;
  if (t > dueTime) {
    ostringstream s;
    s << info.title << " (fps: " << (int)(renderedFrames / MeasurementTime) << ")";
    glfwSetWindowTitle(Window.get(), s.str().c_str());

    renderedFrames = 0;
    dueTime = t + MeasurementTime;
  }
}

void Application::notify(const string & message) {
  glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_MARKER, 0, 
      GL_DEBUG_SEVERITY_NOTIFICATION, -1, message.c_str());
}

void Application::setDebugging(bool debug) {
  using glbinding::ContextInfo;
  if (debug) {
    cerr <<
      "OpenGL Version:  " << ContextInfo::version()  << endl <<
      "OpenGL Vendor:   " << ContextInfo::vendor()   << endl <<
      "OpenGL Renderer: " << ContextInfo::renderer() << endl <<
      "OpenGL Revision: " << glbinding::Meta::glRevision() << " (gl.xml)" << endl <<
      "GLSL Version:    " << glGetString(GL_SHADING_LANGUAGE_VERSION) <<
      endl << endl;
    Check;

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback([](
        GLenum source, GLenum type, GLuint id,
        GLenum severity, GLsizei length, const GLchar *message, const void *userParam) {

#     pragma GCC diagnostic ignored "-Wswitch"
      const char *_source = "Unknown";
      switch (source) {
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   _source = "WinSys";         break;
        case GL_DEBUG_SOURCE_APPLICATION:     _source = "App";            break;
        case GL_DEBUG_SOURCE_API:             _source = "OpenGL";         break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: _source = "ShaderCompiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     _source = "3rdParty";       break;
        case GL_DEBUG_SOURCE_OTHER:           _source = "Other";          break;
      }
      const char *_type = "Unknown";
      switch (type) {
        case GL_DEBUG_TYPE_ERROR:               _type = "Error";       break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: _type = "Deprecated";  break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  _type = "Undefined";   break;
        case GL_DEBUG_TYPE_PORTABILITY:         _type = "Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         _type = "Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              _type = "Marker";      break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          _type = "PushGrp";     break;
        case GL_DEBUG_TYPE_POP_GROUP:           _type = "PopGrp";      break;
        case GL_DEBUG_TYPE_OTHER:               _type = "Other";       break;
      }
      const char *_severity = "Unknown";
      switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:         _severity = "High";   break;
        case GL_DEBUG_SEVERITY_MEDIUM:       _severity = "Med";    break;
        case GL_DEBUG_SEVERITY_LOW:          _severity = "Low";    break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: _severity = "Notify"; break;
      }
#     pragma GCC diagnostic warning "-Wswitch"
      cout << _source << "." << _type << "[" << _severity << "](" <<
        id << "): " << message << endl;
    }, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_MARKER, 0, 
                         GL_DEBUG_SEVERITY_NOTIFICATION, -1, "Start debugging");

    using glbinding::CallbackMask;

    glbinding::setCallbackMaskExcept(
      CallbackMask::Unresolved |
      CallbackMask::After |
      CallbackMask::ParametersAndReturnValue,
      { "glGetError", "glDebugMessageInsert" });

    glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_MARKER, 0, 
                         GL_DEBUG_SEVERITY_NOTIFICATION, -1, "Setting debugging related callbacks");

    glbinding::setUnresolvedCallback([](const glbinding::AbstractFunction & f) {
      cerr << "Unresolved API (" << f.name() << ") was called" << endl;
    });

    glfwSetErrorCallback([] (int error, const char* description) {
      ostringstream s;
      s << "GFLW error (" << error << "): " << description;
      glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_MARKER, 0, 
                           GL_DEBUG_SEVERITY_NOTIFICATION, -1, s.str().c_str());
    });
  } else {
    glbinding::setCallbackMask(glbinding::CallbackMask::None);
    glDebugMessageCallback([](GLenum source, GLenum type, GLuint id,
                              GLenum severity, GLsizei length, const GLchar *message,
                              const void *userParam) {}, nullptr);
    glfwSetErrorCallback(NULL);
    glDisable(GL_DEBUG_OUTPUT);
  }
}

void Application::init(const string & title) {
  if (info.title.empty()) info.title = title;
  App.reset(this);

  glbinding::setAfterCallback([this](const glbinding::FunctionCall & call) {
    GLErrorCheck();
    if (this->traceP) {
      ostringstream s;
      s << call.function->name() << "(";
      for (unsigned i = 0; i < call.parameters.size(); ++i) {
        s << call.parameters[i]->asString();
        if (i < call.parameters.size() - 1) s << ", ";
      }
      s << ") => " << call.returnValue;
      glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_MARKER, 0, 
                           GL_DEBUG_SEVERITY_NOTIFICATION, -1, s.str().c_str());
    }
  });
}

void Application::init() {
  info.title = C["glfw"]["title"].string_value();
  init("");
}


void Application::shutdown() {
  setDebugging(false);
  glfwTerminate();
  App.get()->~Application();
}

void Application::run() {
  init();
  if (A["trace"].bool_value()) setTrace(true);
  startup();

  GLFWwindow *win = Window.get();
  onResize(win, info.winWidth, info.winHeight);

  bool maybeTracing = true;

  while (!glfwWindowShouldClose(win)) {
    glfwPollEvents();
    double t = glfwGetTime();
    render(t);
    glFinish();

    showFPS(t);
    glfwSwapBuffers(win);
    if (maybeTracing) {
      setTrace(false);
      maybeTracing = false;
    }
  }
  shutdown();
  exit(EXIT_SUCCESS);
}

void Application::onFramebufferSize(GLFWwindow *win, int w, int h) {
  onResize(win, w, h);
}

mat4 Projection(1);

void Application::onResize(GLFWwindow *win, int w, int h) {
  info.winWidth = w; info.winHeight = h;
  glViewport(0, 0, w, h);
  Projection = glm::perspective(glm::radians(70.0f), (float)w/h, 0.3f, 100.0f);
}

void Application::onKey(GLFWwindow *win, int key, int scancode, int action, int mods) {
  if ((key == GLFW_KEY_Q || key == GLFW_KEY_ESCAPE) && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(win, true);
  }
}

bool mousePressing = false, mouseDragging = false;

void Application::onMouseButton(GLFWwindow *win, int button, int action, int mods) {
  if (action == GLFW_RELEASE) {
    mouseReleased(win, button, action, mods);
    if (!mouseDragging) mouseClicked(win, button, action, mods);
    mousePressing = mouseDragging = false;
  } else if (action == GLFW_PRESS && !mousePressing) {
    mousePressed(win, button, action, mods);
    mousePressing = true;
  } else {
    std::cerr << "Unknown mouse operation (" << action << ")" << std::endl;
  }
}
void Application::mousePressed (GLFWwindow *win, int button, int action, int mods) {}
void Application::mouseReleased(GLFWwindow *win, int button, int action, int mods) {}
void Application::mouseClicked (GLFWwindow *win, int button, int action, int mods) {}

void Application::mouseDragged(GLFWwindow *win, double xpos, double ypos) {}
void Application::mouseMoved  (GLFWwindow *win, double xpos, double ypos) {}
void Application::onCursorPos (GLFWwindow *win, double xpos, double ypos) {
  if (mousePressing) mouseDragged(win, xpos, ypos);
  else mouseMoved(win, xpos, ypos);
}
void Application::onScroll(GLFWwindow *win, double xoffset, double yoffset) {}

void Application::getCursorPos(GLFWwindow *window, double &xpos, double &ypos) {}

UniformSpec::UniformSpec(string _name, GLenum _type, GLint _location) {
  name = _name;
  type = _type;
  location = _location;
}

// Bug: Extract the extension!
static GLenum Shader::typeOf(const string &path) {
  const string::size_type i = path.rfind('.');
  return typeOfExt.find(path.substr(i+1))->second;
}

void Shader::throwOnShaderError(GLuint shader, GLenum pname, const string &message) {
  int result;
  glGetShaderiv(shader, pname, &result);
  if (result == false) {
    int length = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
    string log;
    if (length > 0) {
      unique_ptr<GLchar[]> _log(new GLchar[length]);
      GLchar *log = _log.get();
      int written = 0;
      glGetShaderInfoLog(shader, length, &written, log);
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
      GLchar* _log = new GLchar[length];
      int written = 0;
      glGetProgramInfoLog(handle, length, &written, _log);
      log = _log;
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

  std::unique_ptr<GLuint> shaderNames(new GLuint[nShaders]);
  glGetAttachedShaders(handle, nShaders, nullptr, shaderNames.get());

  for (int i = 0; i < nShaders; i++) glDeleteShader(shaderNames.get()[i]);
  glDeleteProgram(handle);
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
        string("Shader compilation failed for \"") + path + "\":\n" + c_code);
    glAttachShader(handle, shader);
  }

void Program::compile(const string &path, GLenum type)
  throw (ProgramException) {
    compile(smartnova::util::readFile(path), type, path);
  }

void Program::compile(const string &path)
  throw (ProgramException) {
    compile(path, Shader::typeOf(path));
  }

void Program::load(const json11::Json &shaderset)
  throw (ProgramException) {
    for (auto &kv: shaderset.object_items()) {
      const string type = kv.first;
      GLenum t = Shader::typeOfExt.find(type)->second;
      const string source = kv.second.string_value();
      compile(source, Shader::typeOfExt.find(type)->second, string("<shaderset>.") + type);
    }
    Program::link();

    analyzeActiveUniforms();
    analyzeActiveUniformBlocks();
# if defined(_DEBUG)
    printActiveUniformBlocks();
    printActiveUniforms();
# endif
  }

void Program::load(const json11::Json &shaders, const int i)
  throw (ProgramException) {
    load(shaders.array_items()[i]);
}

void Program::load(const string &stem, vector<string> exts)
  throw (ProgramException) {
  const char *dir = getenv("SHADERS_DIR");
  const string base(dir ? dir : ".");
  for (const auto ext : exts)
    Program::compile(base + "/" + stem + "." + ext);
  Program::link();

  analyzeActiveUniforms();
  analyzeActiveUniformBlocks();
# if defined(_DEBUG)
    printActiveUniformBlocks();
    printActiveUniforms();
# endif
}

void Program::load(const string &stem, string exts)
  throw (ProgramException) {
    const char *dir = getenv("SHADERS_DIR");
    const string base(dir ? dir : ".");
    const std::regex words_rx("\\w+");
    for (std::sregex_iterator i = std::sregex_iterator(exts.begin(), exts.end(), words_rx);
        i != std::sregex_iterator(); ++i) {
      Program::compile(base + "/" + stem + "." + (*i).str());
    }
    Program::link();

    analyzeActiveUniforms();
    analyzeActiveUniformBlocks();
# if defined(_DEBUG)
    printActiveUniformBlocks();
    printActiveUniforms();
# endif
  }

/*
void Program::loadall(const vector<Program> &programs, const json11::Json &shaders)
  throw (ProgramException) {
    int i = 0;
    for (auto shader : shaders.array_items()) {
      Program program;
      program.load(shader);
      progs[i] = program;
      i++;
    }
}
*/

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

void Program::setUniform(const char * name, const glm::ivec2 &v) {
  glUniform2i(uniformLocation(name), v.x, v.y);
}

void Program::setUniform(const char * name, const glm::ivec3 &v) {
  glUniform3i(uniformLocation(name), v.x, v.y, v.z);
}

void Program::setUniform(const char * name, const glm::ivec4 &v) {
  glUniform4i(uniformLocation(name), v.x, v.y, v.z, v.w);
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

void Program::setUniform(const char *name, double x, double y, double z) {
  glUniform3f(uniformLocation(name), (float)x, (float)y, (float)z);
}

void Program::setUniform(const char *name, const vec4 &v) {
  glUniform4f(uniformLocation(name), v.x, v.y, v.z, v.w);
}

#define SET_UNIFORM_M(suffix, T) \
  void Program::setUniform(const char *name, const T &m) { \
    glUniformMatrix##suffix(uniformLocation(name), 1, GL_FALSE, &m[0][0]); \
  }

SET_UNIFORM_M(3fv, mat3)
SET_UNIFORM_M(4fv, mat4)

void Program::setUniform(const char *name, const double x) {
  glUniform1f(uniformLocation(name), (float)x);
}

#define SET_UNIFORM(suffix, T) \
void Program::setUniform(const char *name, const T x) { \
  glUniform##suffix(uniformLocation(name), x); \
}

SET_UNIFORM(1f,  float)
SET_UNIFORM(1i,  int)
SET_UNIFORM(1ui, GLuint)
SET_UNIFORM(1i,  bool)

#define FV(x) ((GLfloat)(x.number_value()))

void Program::setUniform(const string &name, const json11::Json &x) {
  UniformSpec *spec = uniforms[name].get();
  GLuint loc = spec->location;
  const char *name_ = name.c_str();
# pragma GCC diagnostic ignored "-Wswitch"
  switch (spec->type) {
    case GL_FLOAT:
      glUniform1f(loc, (GLfloat)x.number_value());
      break;
    case GL_FLOAT_VEC2:
      {
        auto v = x.array_items();
        glUniform2f(loc, FV(v[0]), FV(v[1]));
      }
      break;
    case GL_FLOAT_VEC3:
      {
        auto v = x.array_items();
        glUniform3f(loc, FV(v[0]), FV(v[1]), FV(v[2]));
      }
      break;
    case GL_FLOAT_VEC4:
      {
        auto v = x.array_items();
        glUniform4f(loc, FV(v[0]), FV(v[1]), FV(v[2]), FV(v[3]));
      }
      break;
  }
# pragma GCC diagnostic warning "-Wswitch"
}

void Program::setUniforms(const string &name, const json11::Json &x) {
  for (const auto &kv : x.object_items()) {
    setUniform(name + "." + kv.first, kv.second);
  }
}

void Program::setUniformBlock(const string &block, const json11::Json &x) {
}

void Program::analyzeActiveUniforms() {
  GLint numUniforms = 0;
  glGetProgramInterfaceiv(handle, GL_UNIFORM, GL_ACTIVE_RESOURCES, &numUniforms);
  GLenum properties[] = { GL_NAME_LENGTH, GL_TYPE, GL_LOCATION, GL_BLOCK_INDEX };
  GLint info[sizeof(properties)/sizeof(GLenum)];
  for (int i = 0; i < numUniforms; i++) {
    glGetProgramResourceiv(handle, GL_UNIFORM, i, 4, properties, 4, nullptr, info);
    if (info[3] != -1) continue;
    GLint s = info[0] + 1;
    unique_ptr<char[]> name_(new char[s]);
    glGetProgramResourceName(handle, GL_UNIFORM, i, s, nullptr, name_.get());
    string name(name_.get());
    std::unique_ptr<UniformSpec> us(new UniformSpec(name, (GLenum)info[1], info[2]));
    uniforms[name] = std::move(us);
  }
}

void Program::printActiveUniforms() {
  if (uniforms.size() == 0) return;
  cout << "Active uniforms:" << endl;
  for (auto it = begin(uniforms); it != end(uniforms); it++) {
    UniformSpec *spec = it->second.get();
    cout << "    " << spec->name << "::" << spec->type << "@" << spec->location << endl;
  }
}

void Program::analyzeActiveUniformBlocks() {
  GLint nBlocks = 0;
  glGetProgramInterfaceiv(handle, GL_UNIFORM_BLOCK, GL_ACTIVE_RESOURCES, &nBlocks);

  GLenum properties[] = { GL_NAME_LENGTH };
  GLenum indices[] = { GL_ACTIVE_VARIABLES };
  for (int b = 0; b < nBlocks; b++) {
    GLint info[sizeof(properties)/sizeof(GLenum)];
    glGetProgramResourceiv(handle, GL_UNIFORM_BLOCK, b, 1, properties, 1, nullptr, info);
    unique_ptr<char[]> name_(new char[info[0] + 1]);
    glGetProgramResourceName(handle, GL_UNIFORM_BLOCK, b, info[0]+1, nullptr, name_.get());
    uniformBlocks.push_back(string(name_.get()));
  }
}

void Program::printActiveUniformBlocks() {
  if (uniformBlocks.size() == 0) return;
  cout << "Active uniform blocks:" << endl;
  for (auto it = begin(uniformBlocks); it != end(uniformBlocks); it++) {
    cout << "    " << *it << endl;
  }
}

void Program::printActiveAttribs() {
  GLint numAttribs;
  glGetProgramInterfaceiv(handle, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &numAttribs);

  GLenum properties[] = { GL_NAME_LENGTH, GL_TYPE, GL_LOCATION };

  printf("Active attributes:\n");
  for (int i = 0; i < numAttribs; ++i) {
    GLint results[3];
    glGetProgramResourceiv(handle, GL_PROGRAM_INPUT, i, 3, properties, 3, nullptr, results);

    GLint nameBufSize = results[0] + 1;
    unique_ptr<char[]> name_(new char[nameBufSize]);
    glGetProgramResourceName(handle, GL_PROGRAM_INPUT, i, nameBufSize, nullptr, name_.get());
    cout << setw(5) << showpos << left << results[2] << name_.get() << " (" << getTypeString(results[1]) << ")" << endl;
  }
  cout << endl;
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
