---
layout: page
title: GLSB6
permalink: /glsb6/
---

# OpenGL SuperBible 6th Edition

{% for post in site.categories.sb reversed %}
- [{{ post.title }}]({{ post.url | prepend: site.baseurl }}) --- {{ post.date | date: "%b %-d, %Y" }}
{% endfor %}

-----

[SLCB2 (OpenGL 4 Shading Language Cookbook - Second Edition)へ，]({{site.baseurl}}/slcb2/)

-----

# 日々の話題

{% for post in site.categories.note reversed %}
- [{{ post.title }}]({{ post.url | prepend: site.baseurl }}) --- {{ post.date | date: "%b %-d, %Y" }}
{% endfor %}
