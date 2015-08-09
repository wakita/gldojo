#!/usr/bin/env node

var TEST = 'P1';

var C = require('const');
var SIZE = 30;
var STACKS = 24;

var titles = {
  P1V: 'Forall spheres { glDrawElements(GL_TRIANGLES) }; ADS/VS',
  P1F: 'Forall spheres { glDrawElements(GL_TRIANGLES) }; ADS/FS',
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
    title: 'Spheres ' + TEST + ': ' + titles[TEST],
    titles: titles
  };

  config.app = {
    TEST: TEST,
    STACKS: STACKS,
    shaders: [ 'spheres/SG' + TEST + '.shaders' ],

    SIZE: SIZE,
    PointSize: 0.9 / (SIZE == 1 ? 1 : (SIZE - 1)),

    Look: { eye: [ 0.5, 0.3, 3. ], at: C.Origin, up: C.Y },

    Material: {
      Kd: [ .9, .5, .3 ],
      Ka: [ .9, .5, .3 ],
      Ks: [ .8, .8, .8 ],
      Shininess: 100. },

    WorldLight: [ 5, 10, 20, 1 ],

    Light: {
      Ld: [ 1., 1., 1. ],
      La: [ .4, .4, .4 ],
      Ls: [ 1., 1., 1. ] },

    trace: false
  };
};
