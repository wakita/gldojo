---
title: 準備
layout: default
permalink: preparation
category: chapter
---

主に必要な環境は OS X Yosemiteと標準的な開発環境, Homebrew, C++11, GLEW, GLFW3, GLM などです．

有名な[GLUTによる「手抜き」OpenGL入門](http://www.wakayama-u.ac.jp/~tokoi/opengl/libglut.html)にしたがって[GLUT](https://www.opengl.org/resources/libraries/glut/)を使おうかと思ったのですが，Appleはあまり熱心にGLUTをサポートしなさそうな雰囲気なのでGLUTに替えてGLFW3を使っています．SuperBibleはGLFW2にもとづいているのですが，[基盤部をGLFW3に移植](https://www.evernote.com/l/AAJ-L3QOKsBJl4hyrwkC19tFfm3mFXHfcWU)しました．あまりわかっていないのですが，GLEW ([The OpenGL Extension Wrangler Library](http://glew.sourceforge.net))も利用しています．これらのほかにビルドシステムとしてCMakeを，行列を扱うための数学ライブラリとしてGLMを利用しています．いずれもHomebrewで簡単にインストールできます．

# CMakeのインストール

システム非依存のビルドツールとしてCMakeを使っています．

    brew install cmake

私は今回初めてCMakeの使っています．不慣れなので，おかしい点が多々あると思います．

# GLFW3のインストール

Homebrewを通して，GLFW2とGLFW3という異なるバージョンをインストールすることができます．このような場合，homebrew/versions を tap してインストールします．

    brew tap homebrew/versions
    brew install glfw3

# GLEWのインストール

    brew install glew

# GLM ([OpenGL Mathematics](http://glm.g-truc.net/0.9.6/index.html))のインストール

    brew install glm
