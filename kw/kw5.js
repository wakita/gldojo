#!/usr/bin/env node

exports.configure = function (config) {
  config.app = {
    Project: 'kw5: Picking',
    shaders: [ 'kw/kw5.shaders' ]
  };
  config.glfw.title = config.app.Project;
  config.glfw.windowSize = [ 1024, 1024 ];
};
