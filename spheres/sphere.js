#!/usr/bin/env node

var TEST = 'P4';

var C = require('const');
var s = 10;

var titles = {
  P1: 'Simple drawing',
  P2: 'Instanced drawing',
  P3: 'Tessellated drawing',
  P4: 'Point sprite',
  P5: 'Texture mapping',
  I1: 'ReadPixel',
  I2: 'Send via Shader storage buffer',
  C1: 'Compute shader 1',
  C2: 'Compute shader 2' 
};

exports.configure = function (config) {
  config.glfw = {
    version: [ 4, 3 ],
    title: 'Spheres ' + TEST + ': ' + titles[TEST]
  };

  config.app = {
    TEST: TEST,
    shaders: [ 'spheres/SG' + TEST + '.shaders' ],
    Look: { eye: [ 0, 0, 3 ], at: C.Origin, up: C.Y },
    SIZE: s,
    PointSize: 300.0 / s,
    WorldLight: [ 5, 10, 20, 1 ]
  };
};
