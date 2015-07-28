#!/usr/bin/env node

var C = require('const');

exports.configure = function (config) {
  with (config) {
    glfw.version = [ 4, 3 ];
    glfw.title = config.app.Project;

    app.Project = 'kw8: object pick test';
    app.shaders = [ 'kw/kw8.shaders' ];
    app.Look = { eye: [ 0, 0, 3 ], at: C.Origin, up: C.Y };
    app.DIM = 2;
    app.PointSize = 300 / app.DIM;
    app.WorldLight = [ 5, 10, 20, 1 ];
    app.trace = false;
  }

  JSON.stringify(config, null, 2);
};
