#include <cmath>
#include <cstdlib>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

static const GLchar *vs_source = R"VS(
#version 410 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

out vec4 vs_color;

void main(void) {
  gl_Position = position;
  vs_color = color;
}
)VS";

static const GLchar *fs_source = R"FS(
#version 410 core

in vec4 vs_color;
out vec4 color;

void main(void) {
  // color = vec4(0.7, 1.0, 1.0, 0.5);
  color = vs_color;
}
)FS";

struct vertex_data {
  float x, y, z;  // Position
  float r, g, b;  // Color
};

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

GLuint compile_shaders(void) {
  GLuint program = glCreateProgram();
  compile_and_link(program, GL_VERTEX_SHADER,   vs_source);
  compile_and_link(program, GL_FRAGMENT_SHADER, fs_source);
  glLinkProgram(program);
  return program;
}

void error_callback(int error, const char* description) {
  std::cout << description << std::endl;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
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

  GLuint rendering_program = compile_shaders();

  GLuint vao[2];
  glGenVertexArrays(2, vao);
  glBindVertexArray(vao[0]);
  glBindVertexArray(vao[1]);

  const vertex_data vdata[] = {
    {  0.25, -0.25,  0.5,  1.0,  0.0,  0.0 },
    { -0.25, -0.25,  0.5,  0.0,  1.0,  0.0 },
    {  0.0,   0.25,  0.5,  0.0,  0.0,  1.0 } };

  GLuint buffers[1];
  glGenBuffers(1, buffers);

  glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vdata), vdata, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_data), (void*)offsetof(vertex_data, x));
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_data), (void*)offsetof(vertex_data, r));
  glEnableVertexAttribArray(1);

  GLfloat color[] = { .2, .2, .5, 1};

  while (!glfwWindowShouldClose(window)) {
    double t = glfwGetTime();

    color[2] = (float)(sin(t) * .5 + .5);
    glClearBufferfv(GL_COLOR, 0, color);

    glUseProgram(rendering_program);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteProgram(rendering_program);
  glDeleteBuffers(1, buffers);

  glfwDestroyWindow(window);
  glfwTerminate();

  exit(EXIT_SUCCESS);
}
