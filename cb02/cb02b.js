#!/usr/bin/env node

var C = require('../config/common.json');

var config = {
  Project: 'cb02b',

  Look: { eye: [ 0., 0., 2. ], at: C.Origin, up: C.Y },

  Shaders: 'vs,fs'.split(',').pop(),

  Torus: [ .7, .3, 50., 50. ],

  LightPosition: [ 5., 5., 2., 1. ],

  Kd: [ .9, .5, .3 ],
  Ld: [ 1., 1., 1. ],

  InitRot: [ -35., 35. ]
};

require('fs').writeFileSync(config.Project + '.json', JSON.stringify(config));
