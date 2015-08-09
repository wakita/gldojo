#!/usr/bin/env node

var TEST = 'P1';

exports.configure = function (config) {
  config.glfw.title = 'Spheres ' + TEST + ': ' + config.glfw.titles[TEST];
  config.app.TEST = TEST;
  config.app.shaders = [ 'spheres/SGP1.shaders' ];
}
