#!/usr/bin/env node

exports.configure = function (config) {
  require('sphere').configure(config);
  config.app.shaders = [ 'sphere/sphere02.shaders' ];
}
