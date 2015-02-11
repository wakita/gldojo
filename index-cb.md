---
layout: page
title: SLCB2
permalink: /slcb2/
---

# OpenGL 4 Shading Language Cookbook - Second Edition

{% for post in site.categories.cb reversed %}
- [{{ post.title }}]({{ post.url | prepend: site.baseurl }}) --- {{ post.date | date: "%b %-d, %Y" }}
{% endfor %}

-----

[GLSB6 (OpenGL SuperBible 6th Edition)へ]({{site.baseurl}}/glsb6/)

-----

# 日々の話題

{% for post in site.categories.note reversed %}
- [{{ post.title }}]({{ post.url | prepend: site.baseurl }}) --- {{ post.date | date: "%b %-d, %Y" }}
{% endfor %}
