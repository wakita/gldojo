#!/usr/bin/env node

var TEST = 'P1';

var C = require('const');
var SIZE = 100;
var STACKS = 24;

titles = {
  P1: 'drawElements; ADS/VS',
  P2: 'drawElementsInstanced; ADS/VS',
  P3: 'drawVector; Tessallation; ADS/TS',
  P4: 'drawVector; Point sprite; ADS/FS'
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

    Look: { eye: [ 0.5, 0.3, 5. ], at: C.Origin, up: C.Y },

    Material: {
      Kd: [ .9, .5, .3 ],
      Ka: [ .9, .5, .3 ],
      Ks: [ .8, .8, .8 ],
      Shininess: 100. },

    WorldLight: [ 5, 10, 20, 1 ],

    Light: {
      Position: [ 5, 10, 20, 1 ],
      Ld: [ 1., 1., 1. ],
      La: [ .4, .4, .4 ],
      Ls: [ 1., 1., 1. ] },

    trace: false
  };

  config.after = function (TEST) {
    this.glfw.title = TEST + ': ' + this.glfw.titles[TEST];
    this.app.TEST = TEST;
    this.app.shaders = [ 'spheres/SG' + TEST + '.shaders' ];
  };
};
