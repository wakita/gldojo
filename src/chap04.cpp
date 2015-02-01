#include <iostream>
#include <cmath>

#define GLM_MESSAGES
#define GLM_FORCE_SIZE_FUNC // vec4.length() => vec4.size()

#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

template <template <typename, glm::precision> class matType,
          typename T,
          glm::precision P>
std::ostream & operator<<(std::ostream & out, const matType<T, P> & x) {
  return out << glm::to_string(x);
}

#include <glm/gtc/matrix_transform.hpp>

#define PI ((float)(asin(1)*2))

int main() {
  glm::vec3 vVerts[] = {
    glm::vec3(-.5f,  0.f,  0.f),
    glm::vec3( .5f,  0.f,  0.f),
    glm::vec3( .0f,  .5f,  0.f) };

  // Vector definition
  glm::vec3 a(1.f, 2.f, 3.f);
  glm::vec3 b(4.f, 5.f, 6.f);
  std::cout << "a = " << a << std::endl << "b = " << b << std::endl << std::endl;

  // Vector addition/subtraction
  glm::vec3 c = b - a;
  std::cout << "a + b = " << (a + b) << std::endl;
  std::cout << "b - a = " << (b - a) << std::endl;
  b -= a;
  std::cout << "b -= a; b = " << b << std::endl << std::endl;

  // Dot product
  std::cout << "a = " << a << std::endl << "b = " << b << std::endl;
  std::cout << "a *. b = " << (dot(a, b)) << std::endl << std::endl;

  // Angle
  glm::vec3 e1 = glm::vec3(1, 0, 0), e2 = glm::vec3(0, 1, 0), e3 = glm::vec3(0, 0, 1);
  std::cout << "e1 x e2 = " << dot(e1, e2) << ", e1 x e1 = " << dot(e1, e1) << std::endl;
  std::cout << "angle(e1, e2) = " << angle(e1, e2) / PI * 180 << std::endl << std::endl;

  // Cross product
  std::cout << "a x b = " << cross(a, b) << std::endl;
  std::cout << "b x a = " << cross(b, a) << std::endl;
  std::cout << "a x b + b x a = " << cross(a, b) + cross(b, a) << std::endl << std::endl;

  std::cout << "e1 x e2 = " << cross(e1, e2) << std::endl;
  std::cout << "e2 x e3 = " << cross(e2, e3) << std::endl;
  std::cout << "e3 x e1 = " << cross(e3, e1) << std::endl << std::endl;

  // Length
  std::cout << "length(e1) = " << length(e1) << std::endl;
  std::cout << "length(e1 * 12) = " << length(e1 * 12) << std::endl;

  // Reflection & Refraction
  glm::vec3 Light = -glm::vec3(1, 1, 1);
  glm::vec3 N     =  glm::vec3(0, 0, 1);
  std::cout << "reflect((-1, -1, -1), N) = " << reflect(Light, N) << std::endl << std::endl;

  std::cout << "refract(L, N, -.1) = " << refract(Light, N, -.1f) << std::endl;
  std::cout << "refract(L, N, 0) = " << refract(Light, N, 0.f) << std::endl;
  std::cout << "refract(L, N, .1) = " << refract(Light, N, .1f) << std::endl;
  std::cout << "refract(L, N, .2) = " << refract(Light, N, .2f) << std::endl << std::endl;

  glm::mat3x3 A = glm::mat3x3(
      glm::vec3(1, 2, 3),
      glm::vec3(4, 5, 6),
      glm::vec3(7, 8, 9));
  glm::mat2x3 B = glm::mat2x3(
      glm::vec3(0, 1.5, 2),
      glm::vec3(42, 0.877, 14));
  std::cout << A * B << std::endl;

  glm::vec3 v = glm::ballRand(1.f);
  glm::mat3 I = glm::mat3(1.0);
  std::cout << "Identity = " << I << std::endl;
  std::cout << "I * v - v = " << I * v - v << std::endl;

  glm::vec4 v4 = glm::vec4(v, 1);
  glm::mat4 I4 = glm::mat4(1.0);
  std::cout << "v4 = " << v4 << std::endl;
  std::cout << "I4 * v4 - v4= " << I4 * v4 - v4 << std::endl << std::endl;

  // Translate matrix
  glm::vec3 translateV = glm::ballRand(1.f);
  glm::mat4x4 Translate = glm::translate(glm::mat4(1.f), translateV);
  std::cout << "translateV = " << translateV << std::endl;
  std::cout << "Translate = " << Translate << std::endl << std::endl;
  std::cout << "Translate(1, 2, 3) = " << glm::translate(I4, glm::vec3(1.f, 2.f, 3.f))
    << std::endl << std::endl;


  // Rotation matrix
  std::cout << "RotateX = " << glm::mat3(glm::rotate(I4, PI/3, e1)) << std::endl;
  std::cout << "RotateY = " << glm::mat3(glm::rotate(I4, PI/3, e2)) << std::endl;
  std::cout << "RotateZ = " << glm::mat3(glm::rotate(I4, PI/3, e3))
    << std::endl << std::endl;

  // Scaling matrix
  glm::mat4 Scale234 = glm::scale(I4, glm::vec3(2.f, 3.f, 4.f));
  std::cout << "Scale234 = " << Scale234 << std::endl;
  std::cout << "Scale234 * I4 = " << Scale234 * glm::vec4(1.f, 1.f, 1.f, 1.f)
    << std::endl << std::endl;

  // Compound Matrix
  glm::mat4 Tr  = glm::translate(I4, glm::vec3(4.f, 10.f, 28.f));
  glm::mat4 Rot = glm::rotate(I4, PI/3, e1);
  glm::vec4 p = glm::vec4(1.f, 0.f, 0.f, 1.f);
  std::cout << Tr * (Rot * p) << std::endl;
  std::cout << (Tr * Rot) * p << std::endl << std::endl;

  // Model-View Transformation
  // Lookat Matrix: lookAt(eye, center, up)
  // Projection Transformation
  // frustrum(left, right, bottom, top, near, far)
  // perspective(fove, aspect, near, far)
  // Orthographic matrices
  // ortho(left, right, bottom, top, near, far)
  // ortho(left, right, bottom, top)
}
