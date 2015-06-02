/**
 * chap05b: 構造体の配列をシェーダに渡す例です．
 *
 * 本来は chap05a と同じものになります．
 *
 * この例では，データの構造体 (VertrexData) を宣言し，その配列によって三角形の各頂点の
 * 座標と色のデータ (vertex) を用意し，それをシェーダにまとめて送ろうとしています．この
 * ときに，受け取る vs 側は二つの変数 position と color で受け取ろうとしているので，
 * 適宜，構造体の中身を分配しなくてはなりません．このために，構造体の表現を分析し
 * それにしたがってデータを送るようにしています．
 **/

#include <cmath>
#define _DEBUG
#include <Program.hpp>

using namespace smartnova::gl;

struct VertexData {
  GLfloat x, y, z;  // Position
  GLfloat r, g, b;  // Color
};

const VertexData vertex[] = {
  {  0.25, -0.25,  0.5,  1.0,  0.0,  0.0 },
  { -0.25, -0.25,  0.5,  0.0,  1.0,  0.0 },
  {  0.0,   0.25,  0.5,  0.0,  0.0,  1.0 } };
const int N_TRIANGLES = sizeof(vertex) / sizeof(VertexData);

class Chapter05B : public Application {

  virtual void init() {
    Application::init("構造体の配列をシェーダに渡す例です．でもバグってます．");
  }

  enum VertexArrays  { Position, Color };
  enum VertexBuffers { Vertex, N_VBO = Vertex + 1 };
  Program program;

  virtual void startup() {
    program.load("sb05/sb05b", vector<string> { "vs", "fs" });
    program.use();

    GLuint vao; glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo[N_VBO]; glGenBuffers(N_VBO, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[Vertex]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

    glVertexAttribPointer(Position, N_TRIANGLES,
        GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLfloat *)offsetof(VertexData, x));
    glEnableVertexAttribArray(Position);

    glVertexAttribPointer(Color, N_TRIANGLES,
        GL_FLOAT, GL_FALSE, sizeof(VertexData), (GLfloat *)offsetof(VertexData, r));
    glEnableVertexAttribArray(Color);
  }

  GLfloat bgcolor[4] = { .2, .2, 0, 1 };

  virtual void render(double t) {
    bgcolor[2] = (float)(sin(t) + 1) / 2;
    glClearBufferfv(GL_COLOR, 0, bgcolor);
    glDrawArrays(GL_TRIANGLES, 0, N_TRIANGLES);
  }
};

DECLARE_MAIN(Chapter05B)
