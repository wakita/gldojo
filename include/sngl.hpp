#ifndef __SNGL_HPP__
#define __SNGL_HPP__

#include <iostream>

#include <GL/glew.h>

#define GLFW_NO_GLU 1
// #define GLFW_INCLUDE_GLCOREARB 1
#include "GLFW/glfw3.h"

namespace sn { namespace gl {

using std::cerr;
using std::endl;
using std::string;

class Application {
  public:
    Application() { app = this; }

    virtual ~Application() {}

    virtual void run() {
      glfwSetErrorCallback([] (int error, const char* description) {
            std::cerr << "Error: " << description << std::endl;
          });
      if (!glfwInit()) {
        cerr << "Failed to initialize GLFW" << endl;
        return;
      }

      init();

#ifdef _DEBUG
      // glfwOpenWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif // _DEBUG
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      glfwWindowHint(GLFW_SAMPLES, info.samples);
      glfwWindowHint(GLFW_STEREO, info.flags.stereo ? GL_TRUE : GL_FALSE);

      if (info.flags.fullscreen) {
        int monitor_count;
        GLFWmonitor** monitors = glfwGetMonitors(&monitor_count);
        GLFWmonitor* monitor = monitors[0];
        if (info.windowWidth == 0 || info.windowHeight == 0) {
          const GLFWvidmode * videoMode = glfwGetVideoMode(monitor);
          info.windowWidth  = videoMode->width;
          info.windowHeight = videoMode->height;
        }
        window = glfwCreateWindow(info.windowWidth, info.windowHeight, info.title.c_str(), monitor, NULL);
        glfwSwapInterval((int)info.flags.vsync);
      } else {
        if (!(window = glfwCreateWindow(info.windowWidth, info.windowHeight, info.title.c_str(), NULL, NULL))) {
          cerr << "Failed to open window" << endl;
          return;
        }
      }

      glfwMakeContextCurrent(window);
      glfwSwapInterval(1);

      glewExperimental = GL_TRUE;
      glewInit();

      glfwSetWindowTitle(window, info.title.c_str());

      glfwSetWindowSizeCallback(window, [] (
            GLFWwindow* win, int w, int h) {
            app->onResize(w, h);
          });

      glfwSetKeyCallback(window, [] (
            GLFWwindow* win, int key, int scancode, int action, int mods) {
            app->onKey(win, key, scancode, action, mods);
          });


      glfwSetMouseButtonCallback(window, [] (
            GLFWwindow* win, int button, int action, int mods) {
            app->onMouseButton(win, button, action, mods);
          });

      glfwSetCursorPosCallback(window, [] (
            GLFWwindow* win, double xpos, double ypos) {
            app->onCursorPos(win, xpos, ypos);
          });

      glfwSetScrollCallback(window, [] (
            GLFWwindow* win, double xoffset, double yoffset) {
            app->onScroll(win, xoffset, yoffset);
          });

      glfwSetInputMode(window, GLFW_CURSOR,
          info.flags.cursor ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);

      info.flags.stereo = (glfwGetWindowAttrib(window, GLFW_STEREO) ? 1 : 0);

#ifdef _DEBUG
      cerr << "VENDOR:   " << glGetString(GL_VENDOR)   << endl;
      cerr << "VERSION:  " << glGetString(GL_VERSION)  << endl;
      cerr << "RENDERER: " << glGetString(GL_RENDERER) << endl << endl;
#endif

      /*
      if (info.flags.debug) {
#       if defined(GL_DEBUG_OUTPUT_SYNCHRONOUS)
          glDebugMessageCallback(debug_callback, this);
          glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
#       elif defined(GL_ARB_debug_output)
          glDebugMessageCallbackARB(debug_callback, this);
          glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
#       endif
      }
      */

      startup();

      while (!glfwWindowShouldClose(window)) {
        render(glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
      }

      shutdown();

      glfwDestroyWindow(window);
      glfwTerminate();
    }

    virtual void init() {
      info.title = string("SuperBible6 Example");
      info.windowWidth = 800;
      info.windowHeight = 600;
      info.majorVersion = 4;
#ifdef __APPLE__
      info.minorVersion = 1;
#else
      info.minorVersion = 3;
#endif
      info.samples = 0;
      info.flags.all = 0;
      info.flags.cursor = 1;
#ifdef _DEBUG
      info.flags.debug = 1;
#endif
    }

    virtual void startup() { }
    virtual void render(double currentTime) { }
    virtual void shutdown() { }

    virtual void onResize(int w, int h) {
      info.windowWidth = w;
      info.windowHeight = h;
    }

    virtual void onKey(GLFWwindow *win, int key, int scancode, int action, int mods) {
      if ((key == GLFW_KEY_Q || key == GLFW_KEY_ESCAPE) && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
      }
    }

    virtual void onMouseButton(GLFWwindow *win, int button, int action, int mods) { }
    virtual void onCursorPos(GLFWwindow *win, double xpos, double ypos) { }
    virtual void onScroll(GLFWwindow *win, double xoffset, double yoffset) { }

    virtual void onDebugMessage(GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar* message) { }

    static void getCursorPos(GLFWwindow* window, double& xpos, double& ypos) {
      glfwGetCursorPos(window, &xpos, &ypos);
    }

  public:
    struct APPINFO {
      string title;
      int windowWidth;
      int windowHeight;
      int majorVersion;
      int minorVersion;
      int samples;
      union {
        struct {
          unsigned int    fullscreen  : 1;
          unsigned int    vsync       : 1;
          unsigned int    cursor      : 1;
          unsigned int    stereo      : 1;
          unsigned int    debug       : 1;
        };
        unsigned int        all;
      } flags;
    };

  protected:
    APPINFO     info;
    static      Application * app;
    GLFWwindow* window;

    void setVsync(bool enable) {
      info.flags.vsync = enable ? 1 : 0;
      glfwSwapInterval((int)info.flags.vsync);
    }

    static void APIENTRY debug_callback(GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar* message,
        GLvoid* userParam) {
      reinterpret_cast<Application *>(userParam)->onDebugMessage(source, type, id, severity, length, message);
    }
  };

}; };  // namespace sn::gl

#define DECLARE_MAIN(APP)                           \
int main(int argc, const char ** argv)              \
{                                                   \
    APP *app = new APP;                             \
    app->run();                                     \
    delete app;                                     \
    return 0;                                       \
}

#endif /* __SNGL_HPP__ */
