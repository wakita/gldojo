---
layout: page
---

OpenGLについてはずぶの素人の脇田が[OpenGL SuperBible第6版](http://www.openglsuperbible.com)と[OpenGL 4 Shading Language Cookbook, Second Edition](https://www.packtpub.com/game-development/opengl-4-shading-language-cookbook-second-edition)で現代的なOpenGLを学び始めました．本を参考にしながら，Yosemiteでサンプルコードを作っています．YosemiteでサポートしているOpenGLのバージョンが4.1なのに対して，SuperBible の想定しているバージョンが4.3だったりして，ときどきはまっています．でも，ちょっと工夫すると大体，動くようです．ずぶの素人のやっていることなので，信頼性は怪しいです．何か見つかったらお知らせ下さい．

では，さっそく道場に入門しましょう．（ちなみに道場主はぼくではなくて[SuperBible]({{site.baseurl}}/glsb6)と[Cookbook]({{site.baseurl}}/slcb2)ですからね）

関連するソースコードはこのサイトの元となった[GitHub repository](https://github.com/wakita/gldojo/)をご覧下さい．

-----

# 日々の話題

{% for post in site.categories.note %}
- [{{ post.title }}]({{ post.url | prepend: site.baseurl }}) --- {{ post.date | date: "%b %-d, %Y" }}
{% endfor %}
