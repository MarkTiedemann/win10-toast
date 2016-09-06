'use strict'

const toast = require('.')({
    title: 'Double Rainbow',
    text: 'Ohhhh, wow! OMG! OMG, double rainbow all the way across the sky!',
    appId: 'double-rainbow.org',
    icon: __dirname + '\\images\\rainbow.png'
})

toast.on('activated', () => console.log('activated'))
toast.on('userCanceled', () => console.log('userCanceled'))
toast.on('timedOut', () => console.log('timedOut'))
