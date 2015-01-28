#include <iostream>

#define GLM_MESSAGES
#define GLM_FORCE_SIZE_FUNC // vec4.length() => vec4.size()

#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 transform(
    glm::vec2 const & Orientation,
    glm::vec3 const & Translate,
    glm::vec3 const & Up) {
  glm::mat4 Projection = glm::perspective(45.f, 4.f / 3.0f, 0.1f, 100.f);
  glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.f), Translate);
  glm::mat4 ViewRotateX = glm::rotate(ViewTranslate, Orientation.y, Up);
  glm::mat4 View = glm::rotate(ViewRotateX, Orientation.x, Up);
  glm::mat4 Model = glm::mat4(1.f);

  return Projection * View * Model;
}

void test_length(glm::vec4 const & v) {
  std::cout << "vec4.size() = " << v.size() << std::endl; // => 4
}

// OpenGL interoperability
// glm/gxc/matrix_transform.hpp
//   mat4 rotate(m4, angle, axis3)
//   mat4 scale(m4, factors3)
//   mat4 translate(m4, translation3)
// glm/glm.hpp
//   mat4(1.0)              // glLoadIdentity
//   mat4 mat4()            // glLoadIdentity
//   mat4 * mat4            // glMultMatrix
//   transpose(mat4)        // glLoadTransposeMatrix
//   mat4 * transpose(mat4) // glMultTransposeMatrix
// glm/gtc/matrix_transform.hpp
//   frustum(left, right, bottom, top, zNear, zFar) // glFrustum
//   ortho(left, right, bottom, top, zNear, zFar)   // glOrtho

// GLU functions
// glm/gtc/matrix_transform.hpp
//   mat4 lookat(eye, center, up)
//   mat4 ortho(left, right, bottom, top)
//   mat4 perspective(fovy, aspect, zNear, zFar)
//   mat4 pickMatrix(center, delta, viewport)
//   vec3 project(obj, model, proj, viewport)
//   vec3 unProject(win, model, proj, viewport)

glm::vec3 computeNormal1(
    glm::vec3 const & a,
    glm::vec3 const & b,
    glm::vec3 const & c) {
  return glm::normalize(glm::cross(c - a, b - a));
}

#include <glm/gtx/fast_square_root.hpp>
// Much faster but less accurate alternative:
glm::vec3 computeNormal2(
    glm::vec3 const & a,
    glm::vec3 const & b,
    glm::vec3 const & c) {
  return glm::fastNormalize(glm::cross(c - a, b -  a));
}

#include <OpenGL/gl.h>
#include <glm/gtc/type_ptr.hpp>

void setUniformMVP(
    GLuint Location,
    glm::vec3 const & Translate,
    glm::vec3 const & Rotate) {
  glm::mat4 Projection = glm::perspective(45.f, 4.f / 3.f, .1f, 100.f);
  glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.f), Translate);
  glm::mat4 ViewRotateX = glm::rotate(ViewTranslate, Rotate.y, glm::vec3(-1.f, 0.f, 0.f));
  glm::mat4 View = glm::rotate(ViewRotateX, Rotate.x, glm::vec3(0.f, 1.f, 0.f));
  glm::mat4 Model = glm::scale(glm::mat4(1.f), glm::vec3(.5f));
  glm::mat4 MVP = Projection * View * Model;
  glUniformMatrix4fv(Location, 1, GL_FALSE, glm::value_ptr(MVP));
}

#include <glm/gtc/type_precision.hpp> // hvec2, i8vec2, i32vec2

void vectorTypes() {
  std::size_t const VertexCount = 4;

  // Float quad geometry
  std::size_t const PositionSizeF32 = VertexCount * sizeof(glm::vec2);
  glm::vec2 const PositionDataF32[VertexCount] = {
    glm::vec2(-1.f, -1.f),
    glm::vec2( 1.f, -1.f),
    glm::vec2( 1.f,  1.f),
    glm::vec2(-1.f,  1.f) };

  // Half-float quad geometry -- hvec2
  /*
  std::size_t const PositionSizeF16 = VertexCount * sizeof(glm::hvec2);
  glm::hvec2 const PositionDataF16[VertexCount] = {
    glm::hvec2(-1.f, -1.f),
    glm::hvec2( 1.f, -1.f),
    glm::hvec2( 1.f,  1.f),
    glm::hvec2(-1.f,  1.f) };

  // 8 bits signed integer quad geometry
  std::size_t const PositionSizeI8 = VertexCount * sizeof(glm::i8vec2);
  glm::hvec2 const PositionDataI8[VertexCount] = {
    glm::hvec2(-1, -1),
    glm::hvec2( 1, -1),
    glm::hvec2( 1,  1),
    glm::hvec2(-1,  1) };
  */

  // 32 bits signed integer quad geometry
  glm::i32vec2 const PositionDataI32[VertexCount] = {
    glm::i32vec2(-1, -1),
    glm::i32vec2( 1, -1),
    glm::i32vec2( 1,  1),
    glm::i32vec2(-1,  1) };

}

#include <glm/ext.hpp>

template <template <typename, glm::precision> class matType,
          typename T,
          glm::precision P>
std::ostream & operator<<(std::ostream & out, const matType<T, P> & x) {
  return out << glm::to_string(x);
}

int main() {
  glm::vec4 v1(1.f, 2.f, 3.f, 4.f);
  glm::vec4 v2(5.f, 6.f, 7.f, 8.f);
  test_length(v1); test_length(v2);
  std::cout << "v1: " << v1 << ", v2: " << v2 << std::endl;

  glm::mat3x4 m = glm::mat3x4(v1, v2, v1);
  std::cout << "m: " << m << std::endl;
}
