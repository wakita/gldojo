#!/usr/bin/env node

var C = require('const');

exports.configure = function (config) {
  require('cb02a').configure(config);
  var app = config.app;
  config.trace = true;
  config.glfw.visible = false;
  app.shaders = [ 'kw/kw6.shaders' ];
  config.glfw.title = app.Project = 'kw7';
};
