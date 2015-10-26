#!/usr/bin/env node

var C = require('const');

exports.configure = function (config) {
  require('cb02a').configure(config);
  var app = config.app;
  config.trace = true;
  app.shaders = [ 'kw/kw6.shaders' ];
  app.Look = { eye:   [ 1.7, 2.0, 0.2 ], at: [0.6, 0.7, 0.8], up: C.Y };
  app.dim = 25;
  app.pointSize = 20;
  app.WorldLight = [ 5, 10, 20, 1 ];
  config.glfw.title = app.Project = 'kw6';
};
