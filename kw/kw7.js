#!/usr/bin/env node

exports.configure = function (config) {
  config.trace = true;
  config.glfw.title = config.app.Project = 'kw7: Showing various shader information';
};
