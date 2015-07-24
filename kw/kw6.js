#!/usr/bin/env node

var C = require('const');

exports.configure = function (config) {
  require('cb02a').configure(config);
  var app = config.app;
  config.trace = true;
  app.shaders = [ 'kw/kw6.shaders' ];
  app.Look = { eye:   [ 2, 2, 1.0 ], at: C.Origin, up: C.Y };
  app.dim = 60;
  app.pointSize = 5;
  app.WorldLight = [ 5, 10, 20, 1 ];
  config.glfw.title = app.Project = 'kw6';
};
