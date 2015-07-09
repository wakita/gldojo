#!/usr/bin/env node

exports.configure = function (config) {
  config.app = {
    Project: 'kw2: 一頂点から三角形',
    shaders: [ 'kw/kw2.shaders' ]
  };
  config.glfw.title = config.app.Project;
};
