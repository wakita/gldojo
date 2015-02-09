#include <iostream>
#include <cmath>

#define GLM_MESSAGES
#define GLM_FORCE_SIZE_FUNC // vec4.length() => vec4.size()

#define _DEBUG
#include "sngl.hpp"

namespace sn { namespace gl {

void f() {
  vec3 vVerts[] = {
    vec3(-.5f,  0.f,  0.f),
    vec3( .5f,  0.f,  0.f),
    vec3( .0f,  .5f,  0.f) };

  // Vector definition
  vec3 a(1.f, 2.f, 3.f);
  vec3 b(4.f, 5.f, 6.f);
  cout << "a = " << a << endl << "b = " << b << endl << endl;

  // Vector addition/subtraction
  vec3 c = b - a;
  cout << "a + b = " << (a + b) << endl;
  cout << "b - a = " << (b - a) << endl;
  b -= a;
  cout << "b -= a; b = " << b << endl << endl;

  // Dot product
  cout << "a = " << a << endl << "b = " << b << endl;
  cout << "a *. b = " << (dot(a, b)) << endl << endl;

  // Angle
  vec3 e1 = vec3(1, 0, 0), e2 = vec3(0, 1, 0), e3 = vec3(0, 0, 1);
  cout << "e1 x e2 = " << dot(e1, e2) << ", e1 x e1 = " << dot(e1, e1) << endl;
  cout << "angle(e1, e2) = " << angle(e1, e2) / PI * 180 << endl << endl;

  // Cross product
  cout << "a x b = " << cross(a, b) << endl;
  cout << "b x a = " << cross(b, a) << endl;
  cout << "a x b + b x a = " << cross(a, b) + cross(b, a) << endl << endl;

  cout << "e1 x e2 = " << cross(e1, e2) << endl;
  cout << "e2 x e3 = " << cross(e2, e3) << endl;
  cout << "e3 x e1 = " << cross(e3, e1) << endl << endl;

  // Length
  cout << "length(e1) = " << length(e1) << endl;
  cout << "length(e1 * 12) = " << length(e1 * 12) << endl;

  // Reflection & Refraction
  vec3 Light = -vec3(1, 1, 1);
  vec3 N     =  vec3(0, 0, 1);
  cout << "reflect((-1, -1, -1), N) = " << reflect(Light, N) << endl << endl;

  cout << "refract(L, N, -.1) = " << refract(Light, N, -.1f) << endl;
  cout << "refract(L, N, 0) = " << refract(Light, N, 0.f) << endl;
  cout << "refract(L, N, .1) = " << refract(Light, N, .1f) << endl;
  cout << "refract(L, N, .2) = " << refract(Light, N, .2f) << endl << endl;

  glm::mat3 A = glm::mat3(
      vec3(1, 2, 3),
      vec3(4, 5, 6),
      vec3(7, 8, 9));
  glm::mat2x3 B = glm::mat2x3(
      vec3(0, 1.5, 2),
      vec3(42, 0.877, 14));
  cout << A * B << endl;

  vec3 v = glm::ballRand(1.f);
  mat3 I = mat3(1.0);
  cout << "Identity = " << I << endl;
  cout << "I * v - v = " << I * v - v << endl;

  vec4 v4 = vec4(v, 1);
  mat4 I4 = mat4(1.0);
  cout << "v4 = " << v4 << endl;
  cout << "I4 * v4 - v4= " << I4 * v4 - v4 << endl << endl;

  // Translate matrix
  vec3 translateV = glm::ballRand(1.f);
  mat4 Translate = glm::translate(mat4(1.f), translateV);
  cout << "translateV = " << translateV << endl;
  cout << "Translate = " << Translate << endl << endl;
  cout << "Translate(1, 2, 3) = " << glm::translate(I4, vec3(1.f, 2.f, 3.f))
    << endl << endl;


  // Rotation matrix
  cout << "RotateX = " << mat3(glm::rotate(I4, PI/3, e1)) << endl;
  cout << "RotateY = " << mat3(glm::rotate(I4, PI/3, e2)) << endl;
  cout << "RotateZ = " << mat3(glm::rotate(I4, PI/3, e3))
    << endl << endl;

  // Scaling matrix
  mat4 Scale234 = glm::scale(I4, vec3(2.f, 3.f, 4.f));
  cout << "Scale234 = " << Scale234 << endl;
  cout << "Scale234 * I4 = " << Scale234 * vec4(1.f, 1.f, 1.f, 1.f)
    << endl << endl;

  // Compound Matrix
  mat4 Tr  = glm::translate(I4, vec3(4.f, 10.f, 28.f));
  mat4 Rot = glm::rotate(I4, PI/3, e1);
  vec4 p = vec4(1.f, 0.f, 0.f, 1.f);
  cout << Tr * (Rot * p) << endl;
  cout << (Tr * Rot) * p << endl << endl;

  // Model-View Transformation
  // Lookat Matrix: lookAt(eye, center, up)
  // Projection Transformation
  // frustrum(left, right, bottom, top, near, far)
  // perspective(fove, aspect, near, far)
  // Orthographic matrices
  // ortho(left, right, bottom, top, near, far)
  // ortho(left, right, bottom, top)
}

} } // namespace sn::gl

int main() { sn::gl::f(); }
