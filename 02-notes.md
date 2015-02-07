---
layout: page
title: 日々の話題
permalink: /notes/
---

{% for post in site.categories.note reversed %}
- [{{ post.title }}]({{ post.url | prepend: site.baseurl }}) --- {{ post.date | date: "%b %-d, %Y" }}
{% endfor %}
