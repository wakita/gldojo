#include <cmath>
#include <cstdlib>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

static const GLchar *vs_source = R"VS(
#version 410 core

layout (location = 0) in vec4 offset;

void main(void) {
  const vec4 vertices[3] = vec4[3](
      vec4( 0.25, -0.25, 0.5, 1.0),
      vec4(-0.25, -0.25, 0.5, 1.0),
      vec4( 0.25,  0.25, 0.5, 1.0));

  gl_Position = vertices[gl_VertexID] + offset;
}
)VS";

static const GLchar *vs_source2 = R"VS2(
#version 410 core

void main(void) {
  gl_Position = vec4(0.0, 0.0, 0.5, 1.0);
}
)VS2";

static const GLchar *fs_source = R"FS(
#version 410 core

out vec4 color;

void main(void) {
  color = vec4(1.0, 1.0, 1.0, 0.5);
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
  GLuint vertex_array_object;
  glGenVertexArrays(1, &vertex_array_object);
  glBindVertexArray(vertex_array_object);

  GLfloat color[] = { 0, 0, 0, 1 };
  while (!glfwWindowShouldClose(window)) {
    double t = glfwGetTime();
    color[0] = (float)(sin(t)/2 + 0.5);
    color[1] = (float)(cos(t)/2 + 0.5);
    glClearBufferfv(GL_COLOR, 0, color);

    glUseProgram(rendering_program);

    GLfloat attrib[] = { (float)(sin(t) * 0.5), (float)(cos(t) * 0.6), 0.0f, 0.0f };
    glVertexAttrib4fv(0, attrib);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &vertex_array_object);
  glDeleteProgram(rendering_program);
  glDeleteVertexArrays(1, &vertex_array_object);

  glfwDestroyWindow(window);
  glfwTerminate();

  exit(EXIT_SUCCESS);
}
