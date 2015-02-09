---
layout: page
---

OpenGLについてはずぶの素人の脇田がOpenGL SuperBible第6版で現代的なOpenGLを学び始めました．本を参考にしながら，Yosemiteでサンプルコードを作っています．YosemiteでサポートしているOpenGLのバージョンが4.1なのに対して，SuperBible の想定しているバージョンが4.3だったりして，ときどきはまっています．でも，ちょっと工夫すると大体，動くようです．ずぶの素人のやっていることなので，信頼性は怪しいです．何か見つかったらお知らせ下さい．

では，さっそく[道場に入門しましょう]({{site.baseurl}}/contents/)．（ちなみに道場主はぼくではなくてSuperBibleですからね）

関連するソースコードはこのサイトの元となった[GitHub repository](https://github.com/wakita/opengl-sb6-samples/)をご覧下さい．

-----

# 日々の話題

{% for post in site.categories.note reversed %}
- [{{ post.title }}]({{ post.url | prepend: site.baseurl }}) --- {{ post.date | date: "%b %-d, %Y" }}
{% endfor %}
