console.log('Loading addon')
const addon = require('../build/Release/win_opacity');
console.log('Running function:')
console.log(addon.applyAlpha(255));
console.log('done')