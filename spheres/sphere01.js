#!/usr/bin/env node

exports.configure = function (config) {
  require('sphere').configure(config);
  config.glfw.version = [ 3, 0 ];
  config.glfw.title = 'Sphere01: Stone Age OpenGL';
}
