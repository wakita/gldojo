---
layout: page
title: 目次
permalink: /contents/
---

{% for post in site.categories.chapter reversed %}
- [{{ post.title }}]({{ post.url | prepend: site.baseurl }}) --- {{ post.date | date: "%b %-d, %Y" }}
{% endfor %}

-----

# 日々の話題

{% for post in site.categories.note reversed %}
- [{{ post.title }}]({{ post.url | prepend: site.baseurl }}) --- {{ post.date | date: "%b %-d, %Y" }}
{% endfor %}
