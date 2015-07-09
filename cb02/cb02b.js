#!/usr/bin/env node

exports.configure = function (config) {
  require('cb02a').configure(config);

  config.app.Project = 'cb02b';
  config.app.shaders = [ 'cb02/cb02b.shaders' ];
  config.glfw.title = config.app.Project;
};
