var C = require('const');

exports.configure = function (c) {
  c.app = {
    name: 'test',

    Look: {
      eye:   [ 0., 0., 2. ],
      left:  [ -0.30, 0., 2. ],
      right: [ 0.30, 0., 2. ],
      at: C.Origin,
      up: C.Y },

    Torus: [ .7, .3, 50., 50. ],

    WorldLight: [ 5., 5., 2., 1. ],

    Material: {
      Kd: [ .9, .5, .3 ],
      Ka: [ .9, .5, .3 ],
      Ks: [ .8, .8, .8 ],
      Shininess: 100. },

    MaterialL: {
      Kd: [ .9, .0, .0 ],
      Ka: [ .9, .0, .0 ],
      Ks: [ .9, .0, .0 ],
      Shininess: 100. },

    MaterialR: {
      Kd: [ .0, .0, .9 ],
      Ka: [ .0, .0, .9 ],
      Ks: [ .0, .0, .8 ],
      Shininess: 100. },

    Light: {
      Ld: [ 1., 1., 1. ],
      La: [ .4, .4, .4 ],
      Ls: [ 1., 1., 1. ] },

    InitRot: [ -35., 35. ]
  };
};
