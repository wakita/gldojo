#include <cmath>

#define _DEBUG
#include "Program.hpp"

using namespace smartnova::gl;

class Chapter05F1 : public Application {
  Program program;

  enum { vaCube };
  enum { baData };
  GLuint vao[1], buf[1], locModelView, locProjection;

  const int vxCube[24] = { // 立方体の頂点
    0, 0, 0,
    0, 1, 0,
    1, 1, 0,
    1, 0, 0,
    0, 0, 1,
    0, 1, 1,
    1, 1, 1,
    1, 0, 1 };

  const int fcCube[24] = { // 立方体の面
    3, 2, 1, 0,
    4, 5, 6, 7,
    5, 4, 0, 1,
    6, 5, 1, 2,
    7, 6, 2, 3,
    4, 7, 3, 0 };

  float Cube[3 * (6 * 2 * 3)]; // 立方体の形状

  void createCube() {
    float * p = Cube;

#   define push(i) { \
      for (int j = 0; j < 3; j++) { \
        *(p++) = vxCube[3 * i + j] / 2.f - .25f; \
      } \
    }

    // Prepare the geometry data for the cube.
    // Its placed in [-.25, +.25]^3
    for (int i = 0; i < 6; i++) { // for all faces
      push(fcCube[4 * i + 0]); push(fcCube[4 * i + 1]); push(fcCube[4 * i + 2]);
      push(fcCube[4 * i + 2]); push(fcCube[4 * i + 3]); push(fcCube[4 * i + 0])
    }
  }

  virtual void init() {
    // info.flags.stereo = GL_TRUE;
    Application::init("chap05f1: 立方体たちが螺旋を描く");
  }

  virtual void startup() {
    glGetError();
    program.load("sb05/sb05f", vector<string> { "vs", "fs" });

    locModelView = program.uniformLocation("ModelView");
    locProjection = program.uniformLocation("Projection");
    Check;

    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[vaCube]);
    Check;

    // Compute the geometry data and send it to the GPU via an array buffer
    createCube();
    glGenBuffers(1, buf);
    glBindBuffer(GL_ARRAY_BUFFER, buf[baData]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Cube), Cube, GL_STATIC_DRAW);
    glVertexAttribPointer(vaCube, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(vaCube);
    Check;

    // The front face is betermined by clockwise.
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    Check;

    // Use z-buffer
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    Check;

    onResize(window, info.winWidth, info.winHeight);
  }

  mat4 Projection = I4;

  virtual void onResize(GLFWwindow *win, int w, int h) {
    Application::onResize(win, w, h);
    Projection = glm::perspective(50.f, (float)w / h, 0.1f, 1000.f);
    updateProjection = true;
  }

  const mat4 Camera = glm::translate(I4, vec3(0, 0, -5));
  bool updateProjection = true;

  virtual void render(double time) {
    int fbufSize[4];
    glfwGetFramebufferSize(window, fbufSize, fbufSize+1);
    glViewport(0, 0, fbufSize[0], fbufSize[1]);

    static const GLfloat bgcolor[4] = { 0, 0.25, 0, 1 };
    static const GLfloat CleanDepth = 1.f;

    // Clear buffers
    glClearBufferfv(GL_COLOR, 0, bgcolor);
    glClearBufferfv(GL_DEPTH, 0, &CleanDepth);

    program.use();

    if (updateProjection) {
      glUniformMatrix4fv(locProjection, 1, GL_FALSE, glm::value_ptr(Projection));
      Check;
      updateProjection = false;
    }

    float t0 = (float)(time * PI * .1);

    for (float t = t0; t > 0; t -= 0.3) {
      mat4 Translation =
        glm::translate(I4, vec3(
              sin(2.1 * t) / 2,
              cos(1.7 * t) / 2,
              sin(1.3 * t) * cos(1.5 * t) * 2));

      mat4 Rotation = glm::rotate(3.f * t, Y) * glm::rotate(2.f * t, X);

      mat4 Scale = glm::scale(I4, vec3(.2));

      mat4 ModelView = Camera * Translation * Rotation * Scale;

      glUniformMatrix4fv(locModelView,  1, GL_FALSE, glm::value_ptr(ModelView));
      Check;

      glDrawArrays(GL_TRIANGLES, 0, 6 * 2 * 3);
      Check;
    }
  }
};

DECLARE_MAIN(Chapter05F1)
