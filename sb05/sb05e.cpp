/**
 * - uniform block に関する std140レイアウトとsharedレイアウトの違いについての調査
 *
 * https://www.evernote.com/l/AAIg2cF646NCvZWxOeN_uEgvfvqUd5lvDVY
 **/

#include <cstdlib>
#include <iostream>
#define _DEBUG
#include "Program.hpp"

#define UCPARAM(param) { \
  GLint v; \
  glGetIntegerv(GL_MAX_##param##_UNIFORM_COMPONENTS, &v); \
  cout << "  " << #param << ": " << v << endl; \
}

using namespace smartnova::gl;

class Chapter05E : public Application {

  virtual void init() {
    info.flags.visible = 0;
    Application::init("Chapter05E");
  }

  void setValuesToProgram(Program &program) {
    program.use();
    GLuint _program = program.getHandle();

    static const GLchar * uNames[] = {
      "TransformBlock.scale",
      "TransformBlock.translation",
      "TransformBlock.rotation",
      "TransformBlock.projection_matrix" };

#   define N_UNAME 4
    GLuint uIndices[N_UNAME]; // Uniform Indices
    // Uniform { Offsets, Array Strides, Matrix Strides }
    GLint  uOffset[N_UNAME], aStride[N_UNAME], mStride[N_UNAME];

    glGetUniformIndices(_program, N_UNAME, uNames, uIndices);
    glGetActiveUniformsiv(_program, N_UNAME, uIndices, GL_UNIFORM_OFFSET,
        (GLint *)uOffset);
    glGetActiveUniformsiv(_program, N_UNAME, uIndices, GL_UNIFORM_ARRAY_STRIDE,
        (GLint *)aStride);
    glGetActiveUniformsiv(_program, N_UNAME, uIndices, GL_UNIFORM_MATRIX_STRIDE,
        (GLint *)mStride);

    cout << "float scale: offset = "      << uOffset[0] << endl;
    cout << "vec3 translation: offset = " << uOffset[1] << endl;
    cout << "vec3 rotation: offset = "    << uOffset[2]
         << ", array stride = "           << aStride[2] << endl;
    cout << "mat4 projection: offset = "  << uOffset[3]
         << ", matrix stride = "          << mStride[3] << endl << endl;

    enum { uSCALE, uTranslation, uRotation, uProjection };
    unsigned char * buffer = (unsigned char *)malloc(4096);
#   define IF(buffer, i) ((float *)(buffer + uOffset[i]))

    // scale = 3.0
    *IF(buffer, uSCALE) = 3.0f;
    // translation = { 1, 2, 3 }

    float * bTranslation = IF(buffer, uTranslation);
    bTranslation[0] = 1.f;
    bTranslation[1] = 2.f;
    bTranslation[2] = 3.f;

    // rotation = { 30, 40, 60 }
    const GLfloat rot[] = { 30, 40, 60 };
    float * bRotation = IF(buffer, uRotation);
    for (int i = 0; i < 3; i++) {
      *bRotation = rot[i];
      bRotation += aStride[uRotation] / sizeof(float);
    }
    cout << "sizeof(rotation): "
      << (bRotation - IF(buffer, uRotation)) * sizeof(float) << endl;

    const GLfloat proj[] = {
      1, 2, 3, 4,
      9, 8, 7, 6,
      2, 4, 6, 8,
      1, 3, 5, 7 };

    float * bProjection = IF(buffer, uProjection);
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        bProjection[j] = proj[i * 4 + j];
      }
      bProjection += mStride[uProjection] / sizeof(float);
    }
    cout << "sizeof(projection): "
      << (bProjection - IF(buffer, uProjection)) * sizeof(float) << endl << endl;
  }

  Program program1, program2;

  virtual void startup() {
    cout << "MAX_**_UNIFORM_COMPONENTS" << endl;
    UCPARAM(VERTEX);
    UCPARAM(TESS_CONTROL);
    UCPARAM(TESS_EVALUATION);
    UCPARAM(GEOMETRY);
    UCPARAM(FRAGMENT);
    cout << endl;

    program1.load("sb05/sb05e1", vector<string> { "vs" });
    program2.load("ssb05/b05e2", vector<string> { "vs" });

    cout << "Analyzing uniform block structure in [std140] layout" << endl;
    setValuesToProgram(program1);

    cout << "Analyzing uniform block structure in [shared] layout" << endl;
    setValuesToProgram(program2);

    exit(0);
  }

  virtual void render(double t) {}
};

DECLARE_MAIN(Chapter05E)
