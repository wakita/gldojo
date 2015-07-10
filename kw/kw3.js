#!/usr/bin/env node

var bits = 5;

exports.configure = function (config) {
  config.app = {
    Project: 'kw3: 四角形',
    shaders: [ 'kw/kw3.shaders' ],
    bits: bits
  };
  config.glfw.title = config.app.Project;
  config.glfw.windowSize = [ 1 << bits, 1 << bits ];
};
