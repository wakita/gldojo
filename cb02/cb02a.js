#!/usr/bin/env node

var C = require('const');

var red  = [ .8, .2, .2 ];
var blue = [ .0, .5, .8 ];

var config = {
  Project: 'cb02a',

  Look: {
    eye:   [ 0., 0., 2. ],
    left:  [ -0.10, 0., 2. ],
    right: [ 0.10, 0., 2. ],
    at: C.Origin,
    up: C.Y },

  shaders: [ 'cb02/cb02a.shaders' ],

  Torus: [ .7, .3, 50., 50. ],

  Light: [ 5., 5., 2., 1. ],

  Material: {
    Kd: [ .9, .5, .3 ],
    Ka: [ .9, .5, .3 ],
    Ks: [ .8, .8, .8 ],
    Shininess: 100. },

  MaterialL: {
    Kd: red,
    Ka: red,
    Ks: red,
    Shininess: 100. },

  MaterialR: {
    Kd: blue,
    Ka: blue,
    Ks: blue,
    Shininess: 100. },

  Light: {
    Ld: [ 1., 1., 1. ],
    La: [ .4, .4, .4 ],
    Ls: [ 1., 1., 1. ] },

  TorusMotion: {
    InitRot: [ -35., 35. ],
    Relocation: [ 0., 0., 0.01 ],
    RotY: 8
  }
};

exports.configure = function (c) {
  c.app = config;
  c.glfw.title = config.Project;
};
