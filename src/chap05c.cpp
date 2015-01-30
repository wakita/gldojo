#include <cmath>
#include <cstdlib>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

static const GLchar *vs_source = R"VS(
#version 410 core

uniform float time;
out vec3 vs_color;

void main(void) {
  const vec3 triangle_vertices[3] = vec3[3](
    vec3(0.25,  -0.25,  0.5),
    vec3(-0.25, -0.25,  0.5),
    vec3(0.0,    0.25,  0.5));

  float t = time;
  gl_Position = vec4(triangle_vertices[gl_VertexID], 1) + vec4(cos(t), sin(t), 0, 1);

  float PI = asin(1);
  float deg= t + (PI * 2 / 3) * gl_VertexID;
  vs_color = vec3((cos(deg) + 1) / 2, (sin(deg) + 1) / 1, .5);
}
)VS";

static const GLchar *fs_source = R"FS(
#version 410 core

in vec3 vs_color;
out vec4 color;

void main(void) {
  color = vec4(vs_color, .5);
}
)FS";

void shaderInfoLog(GLuint shader, const GLchar *source) {
# define INFO_LOG_LEN 255
  GLchar infoLog[INFO_LOG_LEN];
  int len;

  glGetShaderInfoLog(shader, INFO_LOG_LEN, &len, infoLog);
  if (len > 0) {
    std::cout << infoLog << std::endl << source << std::endl;
    exit(EXIT_FAILURE);
  }
}

void compile_and_link(GLuint program, GLenum shader_type, const GLchar *source) {
  const GLchar *sources[] = { source };
  GLuint shader = glCreateShader(shader_type);
  glShaderSource(shader, 1, sources, NULL);
  glCompileShader(shader);
  shaderInfoLog(shader, source);
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

  GLFWwindow* window = glfwCreateWindow(640, 480, "", NULL, NULL);
  if (!window) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);
  glfwSwapInterval(1);

  glewExperimental = GL_TRUE;
  glewInit();

  GLuint rendering_program = compile_shaders();

  GLuint vao[1];
  glGenVertexArrays(1, vao);
  glBindVertexArray(vao[0]);

  GLint time_loc = glGetUniformLocation(rendering_program, "time");

  GLfloat background[] = { .6, .6, .6, 1 };

  while (!glfwWindowShouldClose(window)) {
    glClearBufferfv(GL_COLOR, 0, background);
    glUseProgram(rendering_program);

    float t = (float)glfwGetTime();
    glUniform1f(time_loc, t);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  exit(EXIT_SUCCESS);
}
