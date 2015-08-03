#!/usr/bin/env node

var C = require('const');
var s = 10;

exports.configure = function (config) {
  config.glfw = {
    version: [ 4, 3 ],
    title: 'Sphere'
  }
  config.app = {
    Look: { eye: [ 0, 0, 3 ], at: C.Origin, up: C.Y },
    SIZE: s,
    PointSize: 300.0 / s,
    WorldLight: [ 5, 10, 20, 1 ]
  };
}
