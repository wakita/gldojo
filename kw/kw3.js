#!/usr/bin/env node

exports.configure = function (config) {
  config.app = {
    Project: 'kw3: 四角形',
    shaders: [ 'kw/kw3.shaders' ]
  };
  config.glfw.title = config.app.Project;
};
