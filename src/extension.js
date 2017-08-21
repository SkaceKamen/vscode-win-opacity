var vscode = require('vscode');
var native = require('./native')

/**
 * Loads opacity from configuration.
 * @return {number} opacity in range of 0-255 rounded to integer
 */
function getOpacity () {
  return vscode.workspace.getConfiguration('winopacity').opacity
}

/**
 * Changes opacity of all code windows to specified value.
 * @param {number} [opacity] opacity in range of 0-255
 */
function changeOpacity (opacity) {
  // Load opacity from configuration if not specified
  opacity = opacity || getOpacity()

  // Check the opacity value to be sure
  if (typeof opacity !== "number" || opacity < 0 || opacity > 255) {
    console.error('Opacity value is out of range! Opacity:', opacity)
    opacity = 255
  }

  // Round opacity value to integer
  opacity = opacity | 0

  // Change the opacity
  native.getCodeWindows().forEach(hwd => {
    native.setWindowOpacity(hwd, opacity)
  })
}

function activate () {
  // Change opacity to target value when opened
  changeOpacity ()

  // Change opacity each time configuration is changed
  vscode.workspace.onDidChangeConfiguration(() => {
    changeOpacity ()
  })
}

exports.activate = activate;
exports.deactivate = function () {};