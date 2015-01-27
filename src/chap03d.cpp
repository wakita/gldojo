#include <cmath>
#include <cstdlib>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

static const GLchar *vs_source = R"VS(
#version 410 core

layout (location = 0) in vec4 offset;
layout (location = 1) in vec4 color;

out vec4 vs_color;

void main(void) {
  const vec4 vertices[] = vec4[](
      vec4( .25, -.25, .5, 1.0),
      vec4(-.25, -.25, .5, 1.0),
      vec4( .25,  .25, .5, 1.0));

  gl_Position = vertices[gl_VertexID] + offset;

  vs_color = color;
}
)VS";

static const GLchar *tcs_source = R"TSC(
#version 410 core

layout (vertices = 3) out;

void main(void) {
  if (gl_InvocationID == 0) {
    gl_TessLevelInner[0] = 5.0;

    gl_TessLevelOuter[0] = 5.0;
    gl_TessLevelOuter[1] = 5.0;
    gl_TessLevelOuter[2] = 5.0;
  }
  gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}
)TSC";

static const GLchar *tes_source = R"TES(
#version 410 core

layout (triangles, equal_spacing, cw) in;

void main(void) {
  gl_Position = (
      gl_TessCoord.x * gl_in[0].gl_Position +
      gl_TessCoord.y * gl_in[1].gl_Position +
      gl_TessCoord.z * gl_in[2].gl_Position);
}
)TES";

static const GLchar *fs_source = R"FS(
#version 410 core

in vec4 vs_color;

out vec4 color;

void main(void) {
  //color = vs_color;
  color = vec4(1., 1., 1., 1.);
}
)FS";

void shaderInfoLog(GLuint shader) {
# define INFO_LOG_LEN 255
  GLchar infoLog[INFO_LOG_LEN];
  int len;

  glGetShaderInfoLog(shader, INFO_LOG_LEN, &len, infoLog);
  if (len > 0) {
    std::cout << infoLog << std::endl;
    exit(EXIT_FAILURE);
  }
}

void compile_and_link(GLuint program, GLenum shader_type, const GLchar *source) {
  const GLchar *sources[] = { source };
  GLuint shader = glCreateShader(shader_type);
  glShaderSource(shader, 1, sources, NULL);
  glCompileShader(shader);
  shaderInfoLog(shader);
  glAttachShader(program, shader);
  glDeleteShader(shader);
}

GLuint build_shaders(void) {
  GLuint program = glCreateProgram();
  compile_and_link(program, GL_VERTEX_SHADER,          vs_source);
  compile_and_link(program, GL_TESS_CONTROL_SHADER,    tcs_source);
  compile_and_link(program, GL_TESS_EVALUATION_SHADER, tes_source);
  compile_and_link(program, GL_FRAGMENT_SHADER,        fs_source);
  glLinkProgram(program);
  return program;
}

void error_callback(int error, const char* description) {
  std::cout << description << std::endl;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if ((key == GLFW_KEY_Q || key == GLFW_KEY_ESCAPE) && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}

int main(void)
{
  if (!glfwInit()) return -1;
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
  if (!window) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  glewExperimental = GL_TRUE;
  glewInit();

  glfwSetKeyCallback(window, key_callback);

  GLuint rendering_program = build_shaders();

  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  GLfloat color[] = { 0, 0, 0, 0 };
  GLfloat offset[] = { 0, 0, 0, 0 };
  GLfloat tcolor[] = { 0, 0, .3f, 1.f };
  while (!glfwWindowShouldClose(window)) {
    double t = glfwGetTime();
    double s = sin(t), c = cos(t);
    color[0] = (float)(s * .4 + .4);
    color[1] = (float)(c * .4 + .4);
    glClearBufferfv(GL_COLOR, 0, color);

    // offset
    offset[0] = (float)(s * .5); offset[1] = (float)(c * .6);
    glVertexAttrib4fv(0, offset);
    // color
     glVertexAttrib4fv(1, tcolor);

    glUseProgram(rendering_program);
    glDrawArrays(GL_PATCHES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &vao);
  glDeleteProgram(rendering_program);

  glfwDestroyWindow(window);
  glfwTerminate();

  exit(EXIT_SUCCESS);
}
