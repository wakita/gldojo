#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>

void error_callback(int error, const char* description) {
  puts(description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}

int main(void)
{
  if (!glfwInit()) return -1;

  GLFWwindow* window = glfwCreateWindow(640, 480, "GLFW sample", NULL, NULL);
  if (!window) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  glfwSetKeyCallback(window, key_callback);


  while (!glfwWindowShouldClose(window)) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float ratio = width / (float) height;

    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ratio, ratio, -1, 1, 1, -1);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    double t = glfwGetTime();           // seconds since start
    glRotatef((float)t * 50, 0, 0, 1);  // the angle is given in Degree

    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0);
    glVertex3f(-0.6f, -0.4f, 0);
    glColor3f(0, 1, 0);
    glVertex3f(0.6f, -0.4f, 0);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0.6f, 0);
    glEnd();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  exit(EXIT_SUCCESS);
}
