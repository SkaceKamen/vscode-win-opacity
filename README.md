## Features

Changes opacity of all Code windows to predefined value

![Screenshot](images/screen-1.png)

## Requirements

 * Windows 2000 or newer

## Extension Settings

This extension contributes the following settings:

* `winopacity.opacity`: window opacity in range of 0-255, where 0 is invisible window

## Development notes

It's important to run `rebuild` script after installing node modules.

```bash
npm install
npm run rebuild
```

This rebuilds native modules to be used in electron based applications.

## Credits

`drywolf` - part of code used to find vscode windows, https://github.com/drywolf/code-solution-manager/blob/0.0.1/extension-ui/browser.js

## Marketplace

https://marketplace.visualstudio.com/items?itemName=skacekachna.win-opacity