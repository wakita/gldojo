#!/usr/bin/env node

exports.configure = function (config) {
  config.app = {
    Project: 'kw1: 多角形',
    shaders: [ 'kw/kw1.shaders' ]
  };
  config.glfw.title = config.app.Project;
};
