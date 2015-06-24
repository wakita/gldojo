#!/usr/bin/env node

var C = require('../config/common.json');

var config = {
  Project: 'cb02c',

  Look: { eye: [ 0., 0., 7. ], at: C.Origin, up: C.Y },

  // Shaders: 'vs,fs'.split(',').pop(),

  Light: {
    Ld: [ 1., 1., 1. ],
    La: [ .4, .4, .4 ],
    Ls: [ 1., 1., 1. ] },

  Material: {
    Kd: [ .9, .5, .3 ],
    Ka: [ .9, .5, .3 ],
    Ks: [ .8, .8, .8 ],
    Shininess: 100. },
};

require('fs').writeFileSync(config.Project + '.json', JSON.stringify(config));
