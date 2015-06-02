#include "Program.hpp"

using namespace smartnova::gl;

const GLchar *unames[] = { "Blob.InnerColor",  "Blob.OuterColor", "Blob.InnerRadius", "Blob.OuterRadius" };

GLfloat outerColor[] = { 0.0f, 0.0f, 0.0f,  0.0f };
GLfloat innerColor[] = { 1.0f, 1.0f, 0.75f, 1.0f };
GLfloat innerRadius  = 0.25f, outerRadius = 0.45f;

const float positions[] = {
  -0.8f, -0.8f,  0.0f,
   0.8f, -0.8f,  0.0f,
   0.8f,  0.8f,  0.0f,
  -0.8f, -0.8f,  0.0f,
   0.8f,  0.8f,  0.0f,
  -0.8f,  0.8f,  0.0f };

const float texcoord[] = {
  0.0f, 0.0f,
  1.0f, 0.0f,
  1.0f, 1.0f,
  0.0f, 0.0f,
  1.0f, 1.0f,
  0.0f, 1.0f };

class CB01E : public Application {
  virtual void init() {
    Application::init("cb01e: Basic Scene (Uniform block)");
  }

  Program program;
  // Attribute vector defined in the VS shader
  GLuint vao;
  enum { Position, Texcoord, N_VBO = Texcoord + 1 };

  // Uniform block defined in the FS shader
  enum uvar { InnerColor, OuterColor, InnerRadius, OuterRadius, N_UNIFORM = OuterRadius + 1 };
  
  virtual void startup() {
    program.load("cb01/cb01e", vector<string> { "vs", "fs" });
    program.use();
    GLuint ph = program.getHandle();

    { // Uniform block preparation
      setTrace(true);
      GLuint ubIndex = glGetUniformBlockIndex(ph, "Blob");
      GLsizei ubSize;
      glGetActiveUniformBlockiv(ph, ubIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &ubSize);
      GLubyte ub[ubSize];

      GLuint uIndex[N_UNIFORM]; GLint  uOffset[N_UNIFORM];
      glGetUniformIndices(ph, N_UNIFORM, unames, uIndex);
      glGetActiveUniformsiv(ph, N_UNIFORM, uIndex, GL_UNIFORM_OFFSET, uOffset);

      // Store data within the FS-uniform block buffer at the appropriate offsets
      memcpy(ub + uOffset[InnerColor],  innerColor,   sizeof(innerColor));
      memcpy(ub + uOffset[OuterColor],  outerColor,   sizeof(outerColor));
      memcpy(ub + uOffset[InnerRadius], &innerRadius, sizeof(innerRadius));
      memcpy(ub + uOffset[OuterRadius], &outerRadius, sizeof(outerRadius));

      // Create the uniform buffer object and copy the data
      GLuint ubo; glGenBuffers(1, &ubo); glBindBuffer(GL_UNIFORM_BUFFER, ubo);
      glBufferData(GL_UNIFORM_BUFFER, ubSize, ub, GL_DYNAMIC_DRAW);

      // Bind the buffer object to the uniform block
      glBindBufferBase(GL_UNIFORM_BUFFER, 1, ubo);

      // We don't need this if we specify the binding within the shader
      // glUniformBlockBinding(ph, ubIndex, 0);
    }

    { // Vertex array preparation
      glBindVertexArray(vao);

      glEnableVertexAttribArray(Position);
      glEnableVertexAttribArray(Texcoord);

      GLuint vbo[N_VBO]; glGenBuffers(N_VBO, vbo);
      glBindBuffer(GL_ARRAY_BUFFER, vbo[Position]);
      glBindBuffer(GL_ARRAY_BUFFER, vbo[Texcoord]);

      glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
      glVertexAttribPointer(Position, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

      glBufferData(GL_ARRAY_BUFFER, sizeof(texcoord), texcoord, GL_STATIC_DRAW);
      glVertexAttribPointer(Texcoord, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    setTrace(false);
  }

  float angle = 0.f;

  virtual void render(double t) {
    angle = t;

    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
  }
};

DECLARE_MAIN(CB01E)
