#!/usr/bin/env node

var C = require('../config/common.json');

var config = {
  Project: 'cb02a',

  Look: {
    eye: [ 0., 0., 2. ],
    left: [ -.05, 0., 2. ],
    right: [ +.05, 0., 2. ],
    at: C.Origin,
    up: C.Y },

  Shaders: 'vs,fs'.split(',').pop(),

  Torus: [ .7, .3, 50., 50. ],

  WorldLight: [ 5., 5., 2., 1. ],

  Material: {
    Kd: [ .9, .5, .3 ],
    Ka: [ .9, .5, .3 ],
    Ks: [ .8, .8, .8 ],
    Shininess: 100. },

  Light: {
    Ld: [ 1., 1., 1. ],
    La: [ .4, .4, .4 ],
    Ls: [ 1., 1., 1. ] },

  InitRot: [ -35., 35. ]
};

require('fs').writeFileSync(config.Project + '.json', JSON.stringify(config));
