const fs = require('fs')
const path = require('path')
const glob = require('glob-fs')()
const distPath = path.resolve(__dirname, '../dist')

if (!fs.existsSync(distPath)) {
	fs.mkdirSync(distPath)
}

glob.readdirSync('*.vsix').forEach(file => {
	fs.renameSync(file, path.join(distPath, file))
})