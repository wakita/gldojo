# Mavericks用のOpenGL SuperBibleサンプルコード

OpenGL SuperBible第6版で現代的なOpenGLを学び始めました．本を参考にMavericksでサンプルコードを作っています．ずぶの素人のやっていることなので，信頼性は？？？です．ちゃんと動いていないコードもあります．

# 準備

以下ではHomebrewが利用できること，したがってXcodeとそのコマンド行インタフェイスもインストールされていることを仮定しています．

有名な[GLUTによる「手抜き」OpenGL入門](http://www.wakayama-u.ac.jp/~tokoi/opengl/libglut.html)にしたがって[GLUT](https://www.opengl.org/resources/libraries/glut/)を使おうかと思ったのですが，Appleはあまり熱心にGLUTをサポートしなさそうな雰囲気なのでGLUTに替えてGLFW3を使っています．あまりわかっていないのですが，GLEW ([The OpenGL Extension Wrangler Library](http://glew.sourceforge.net))も利用しています．これらのほかにビルドシステムとしてCMakeを，行列を扱うための数学ライブラリとしてGLMを利用しています．いずれもHomebrewで簡単にインストールできます．

- CMakeのインストール．システム非依存のビルドツールとしてCMakeを使っています．今回がCMakeの使い始めです．不慣れなので，おかしい点が多々あると思います．

- GLFW3のインストール．Homebrewを通して，GLFW2とGLFW3という異なるバージョンをインストールすることができます．このような場合，homebrew/versions を tap してインストールします．

        brew tap homebrew/versions
        brew install glfw3

- GLEWのインストール

        brew install glew

- GLM ([OpenGL Mathematics](http://glm.g-truc.net/0.9.6/index.html))のインストール

        brew install glm

# ソースコード

- CMakeLists.txt: CMakeの設定

- [bin/init](bin/init): CMakeのプロジェクトを初期化するためのスクリプトです．私はこのGitプロジェクトはDropbox上に置き，CMakeのビルドはDropbox外のディレクトリ($HOME/projects/glfw)で行っているのですが，そのための設定です．

- [src/](src/): SuperBible に沿ったサンプルコード

- [src/test](src/test): GLFW, GLM, GLEWの簡単なサンプルコードです．

- 第二章: Our First OpenGL Program

    - [chap2a](src/chap2a.cpp): ウィンドウ消去

    - [chap2b](src/chap2b.cpp): ウィンドウの消去色を変化させた簡単なアニメーション

    - [chap2c](src/chap2c.cpp): 点の描画

- 第三章: Following the Pipeline

    - [chap3a](src/chap3a.cpp): Vertex shaderとFragment shaderを利用した例．背景色が変化するなか，白い三角形が弧を描くアニメーション．

    - [chap3b](src/chap3b.cpp): Vertex shaderを介してFragment shaderに三角形の色を与えることで色を変化させる例．

    - [chap3c](src/chap3c.cpp): Vertex shaderからFragment shaderへの値の伝達においてInterface Blockを利用した方法．

    - [chap3d](src/chap3d.cpp): Tessallation control shaderとTessallation evaluation shaderを追加し，三角形をワイヤーフレームで描画した例．

    - [chap3d1](src/chap3d1.cpp): chap3dを作る上で作成したコード．chap3dでは三角形が弧を描くがchap3d1ではウィンドウ中央に静止している．

    - [chap3e](src/chap3e.cpp): Geometry shaderを追加し，Tessell化した三角形の頂点を点描する例．

    - [chap3f](src/chap3f.cpp): Fragment shaderでピクセルの位置に応じて色を決定することで三角形にグラデーションを与える例．

    - [chap3g](src/chap3g.cpp): Fragment shaderへ与える色情報をVertex shaderを介してCPU側から与えようとした例だが，うまく動作しない．どうやらFragment ShaderにVertex shaderから与えているつもりの色情報が正しく届いていないようだ．原因は究明中．
