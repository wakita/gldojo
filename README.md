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

- [src/test](src/test):
  [GLEW](src/test/glew.cpp),
  [GLFW](src/test/glfw.cpp),
  GLM ([glm.cpp](src/test/glm.cpp), [glm_sample.cpp](src/test/glm_sample.cpp))
  の簡単なサンプルコードです．

- 第二章: Our First OpenGL Program

    - [chap02a](src/chap02a.cpp): ウィンドウ消去

    - [chap02b](src/chap02b.cpp): ウィンドウの消去色を変化させた簡単なアニメーション

    - [chap02c](src/chap02c.cpp): 点の描画

- 第三章: Following the Pipeline

    - [chap03a](src/chap03a.cpp): Vertex shaderとFragment shaderを利用した例．背景色が変化するなか，白い三角形が弧を描くアニメーション．

    - [chap03b](src/chap03b.cpp): Vertex shaderを介してFragment shaderに三角形の色を与えることで色を変化させる例．

    - [chap03c](src/chap03c.cpp): Vertex shaderからFragment shaderへの値の伝達においてInterface Blockを利用した方法．

    - [chap03d](src/chap03d.cpp): Tessallation control shaderとTessallation evaluation shaderを追加し，三角形をワイヤーフレームで描画した例．

    - [chap03d1](src/chap03d1.cpp): chap3dを作る上で作成したコード．chap3dでは三角形が弧を描くがchap3d1ではウィンドウ中央に静止している．

    - [chap03e](src/chap03e.cpp): Geometry shaderを追加し，Tessell化した三角形の頂点を点描する例．

    - [chap03f](src/chap03f.cpp): Fragment shaderでピクセルの位置に応じて色を決定することで三角形にグラデーションを与える例．

    - [chap03g](src/chap03g.cpp): Fragment shaderへ与える色情報をVertex shaderを介してCPU側から与えようとした例だが，うまく動作しない．どうやらFragment ShaderにVertex shaderから与えているつもりの色情報が正しく届いていないようだ．原因は究明中．

- 第四章: Math for 3D Graphics

    - [chap04](src/chap04.cpp): この章は主に三次元グラフィックスに必要となる数学的基礎について紹介している．ベクトルと行列，四元数，各種変換，補間，Bezier曲線，スプライン曲線など．このソースコードでは主にGLMのAPIで関連するものをテストしている．SuperBibleではvmathパッケージで記述されていたものをGLMに翻訳した．

- 第五章: Data

    - [chap05a](src/chap05a.cpp): 複数のデータをシェーダーに送る方法．Vertex Array Object と Vector Buffer Objectを連携させる方法．例題としては，三角形の形状と色の情報をアプリケーション側から送るもの．

    - [chap05b](src/chap05b.cpp): シェーダ側で複数の種類のデータに構造体でまとめあげた場合の，アプリケーション側からのデータを送る方法．できあがるのはchap05aと同じ例題．

    - [chap05c](src/chap05c.cpp): uniformを用いる方法．この例では，VSにuniformとして与えた時刻をFSが参照していないので，あまり面白くはないが，使い方はわかるだろう．uniformを送るときも，VAOの操作は必須なことに注意．
