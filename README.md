
# win10-toast

**Windows 10 Toast Notifications API simplified, and prebuilt with [NodeRT](https://github.com/NodeRT/NodeRT).**

## Installation

```
npm install win10-toast
```

## Quickstart

[![](https://raw.githubusercontent.com/MarkTiedemann/win10-toast/master/images/example.png)](https://www.youtube.com/watch?v=OQSNhk5ICTI)

```js

const toast = require('win10-toast')({
    title: 'Double Rainbow',
    text:  'Ohhhh, wow! OMG! OMG, double rainbow all the way across the sky!',
    appId: 'double-rainbow.org',
    icon:  'rainbow.png'
})

toast.on('activated', ... )
toast.on('userCanceled', ... )
toast.on('timedOut',  ... )

```

## Notes

- Toast [options](https://blogs.msdn.microsoft.com/tiles_and_toasts/2015/07/02/adaptive-and-interactive-toast-notifications-for-windows-10/) on the Windows Developer Blog
- Toast [sound options](https://msdn.microsoft.com/library/windows/apps/br230842) in the Windows Dev Center
- [Rainbow icon](http://www.flaticon.com/free-icon/rainbow_189166) by [Roundicons](http://www.flaticon.com/authors/roundicons) under Flaticon Basic License

## Development

- [Prerequesites](https://github.com/NodeRT/NodeRT#nodert-prerequisites)
- Building: Open Powershell as an administrator and run: `.\build.ps1`
- Todos: Document API

## License

[WTFPL](http://www.wtfpl.net/) – Do What the F*ck You Want to Public License.

Made with :heart: by [@MarkTiedemann](https://twitter.com/MarkTiedemannDE).
