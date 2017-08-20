# win-opacity

## Features

Changes opacity of all Code windows to predefined value

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

this rebuilds native modules to be used in electron based appliactions.