module.exports = config => {
  config.set({
    frameworks: [
      'fixture',
      'jasmine',
      'jquery-3.3.1', // Matches the jQuery version used by our app.
      'sinon',
    ],

    files: [
      'src/**/*.js',
      'test/**/*.js',
      'test/**/*.html'
    ],

    preprocessors: {
      'test/**/*.html': ['html2js'],
      'src/**/*.js': ['coverage']
    },

    browsers: [
      'Firefox'
    ],

    reporters: [
      'dots',
      'coverage'
    ],

    coverageReporter: {
      dir: 'coverage',
      reporters: [
        { type: 'html', subdir: 'html' },
        { type: 'text-summary' }
      ]
    }
  })
}
