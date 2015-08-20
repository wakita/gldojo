#!/usr/bin/env node

exports.configure = function (config) {
  config.app.trace = false;
  config.after('P3');
}
