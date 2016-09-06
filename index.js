'use strict'

const EventEmitter = require('events')

const dom = require('./prebuilt/windows.data.xml.dom')
const notifications = require('./prebuilt/windows.ui.notifications')

module.exports = ({

    appId = 'AppId',
    title = 'Title',
    text = 'Text',
    icon = '',

    sound = 'Default',
    silent = false,
    duration = 'short',
    scenario = 'default',
    activationType = 'foreground',

    tag,
    group,
    suppressPopup,
    expirationTime

} = {}) => {

    const template =
    `<toast duration='${duration}' scenario='${scenario}' activationType='${activationType}'>
        <visual>
            <binding template='ToastGeneric'>
                <text>${title}</text>E
                <text>${text}</text>
                <image placement='appLogoOverride' src='${icon}'/>
            </binding>
        </visual>
        <audio src='ms-winsoundevent:Notification.${sound}' silent='${silent}'/>
    </toast>`

    const xml = new dom.XmlDocument()
    xml.loadXml(template)

    const toast = new notifications.ToastNotification(xml)

    if (tag) toast.tag = tag
    if (group) toast.group = group
    if (suppressPopup) toast.suppressPopup = suppressPopup
    if (expirationTime) toast.expirationTime = expirationTime

    const reasons = notifications.ToastDismissalReason
    const keepAlive = setTimeout(() => {}, 999999)
    const emitter = new EventEmitter()

    toast.on('activated', () => {
        emitter.emit('activated')
        clearTimeout(keepAlive)
    })

    toast.on('dismissed', (_, { reason }) => {
        switch (reason) {
            case reasons.userCanceled:
                emitter.emit('userCanceled')
                break
            case reasons.applicationHidden:
                emitter.emit('applicationHidden')
                break
            case reasons.timedOut:
                emitter.emit('timedOut')
                break
        }
        clearTimeout(keepAlive)
    })

    toast.on('failed', () => {
        emitter.emit('failed')
        clearTimeout(keepAlive)
    })

    const notifier = notifications.ToastNotificationManager.createToastNotifier(appId)
    notifier.show(toast)

    return emitter

}
