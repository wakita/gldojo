exports.configure = function (config) {
  require('cb02a').configure(config);

  config.app.Project = 'Phong\'s ADS (Ambient, Diffuse, and Specular) shading';
  config.app.shaders = [ 'cb02/cb02a2.shaders' ];
  config.glfw.title = config.app.Project;
};
