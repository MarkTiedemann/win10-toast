_NotificationSetting = function () {
  this.enabled = 0;
  this.disabledForApplication = 1;
  this.disabledForUser = 2;
  this.disabledByGroupPolicy = 3;
  this.disabledByManifest = 4;
}
exports.NotificationSetting = new _NotificationSetting();

_ToastDismissalReason = function () {
  this.userCanceled = 0;
  this.applicationHidden = 1;
  this.timedOut = 2;
}
exports.ToastDismissalReason = new _ToastDismissalReason();

_BadgeTemplateType = function () {
  this.badgeGlyph = 0;
  this.badgeNumber = 1;
}
exports.BadgeTemplateType = new _BadgeTemplateType();

_TileFlyoutTemplateType = function () {
  this.tileFlyoutTemplate01 = 0;
}
exports.TileFlyoutTemplateType = new _TileFlyoutTemplateType();

_TileTemplateType = function () {
  this.tileSquareImage = 0;
  this.tileSquareBlock = 1;
  this.tileSquareText01 = 2;
  this.tileSquareText02 = 3;
  this.tileSquareText03 = 4;
  this.tileSquareText04 = 5;
  this.tileSquarePeekImageAndText01 = 6;
  this.tileSquarePeekImageAndText02 = 7;
  this.tileSquarePeekImageAndText03 = 8;
  this.tileSquarePeekImageAndText04 = 9;
  this.tileWideImage = 10;
  this.tileWideImageCollection = 11;
  this.tileWideImageAndText01 = 12;
  this.tileWideImageAndText02 = 13;
  this.tileWideBlockAndText01 = 14;
  this.tileWideBlockAndText02 = 15;
  this.tileWidePeekImageCollection01 = 16;
  this.tileWidePeekImageCollection02 = 17;
  this.tileWidePeekImageCollection03 = 18;
  this.tileWidePeekImageCollection04 = 19;
  this.tileWidePeekImageCollection05 = 20;
  this.tileWidePeekImageCollection06 = 21;
  this.tileWidePeekImageAndText01 = 22;
  this.tileWidePeekImageAndText02 = 23;
  this.tileWidePeekImage01 = 24;
  this.tileWidePeekImage02 = 25;
  this.tileWidePeekImage03 = 26;
  this.tileWidePeekImage04 = 27;
  this.tileWidePeekImage05 = 28;
  this.tileWidePeekImage06 = 29;
  this.tileWideSmallImageAndText01 = 30;
  this.tileWideSmallImageAndText02 = 31;
  this.tileWideSmallImageAndText03 = 32;
  this.tileWideSmallImageAndText04 = 33;
  this.tileWideSmallImageAndText05 = 34;
  this.tileWideText01 = 35;
  this.tileWideText02 = 36;
  this.tileWideText03 = 37;
  this.tileWideText04 = 38;
  this.tileWideText05 = 39;
  this.tileWideText06 = 40;
  this.tileWideText07 = 41;
  this.tileWideText08 = 42;
  this.tileWideText09 = 43;
  this.tileWideText10 = 44;
  this.tileWideText11 = 45;
  this.tileSquare150x150Image = 46;
  this.tileSquare150x150Block = 47;
  this.tileSquare150x150Text01 = 48;
  this.tileSquare150x150Text02 = 49;
  this.tileSquare150x150Text03 = 50;
  this.tileSquare150x150Text04 = 51;
  this.tileSquare150x150PeekImageAndText01 = 52;
  this.tileSquare150x150PeekImageAndText02 = 53;
  this.tileSquare150x150PeekImageAndText03 = 54;
  this.tileSquare150x150PeekImageAndText04 = 55;
  this.tileWide310x150Image = 56;
  this.tileWide310x150ImageCollection = 57;
  this.tileWide310x150ImageAndText01 = 58;
  this.tileWide310x150ImageAndText02 = 59;
  this.tileWide310x150BlockAndText01 = 60;
  this.tileWide310x150BlockAndText02 = 61;
  this.tileWide310x150PeekImageCollection01 = 62;
  this.tileWide310x150PeekImageCollection02 = 63;
  this.tileWide310x150PeekImageCollection03 = 64;
  this.tileWide310x150PeekImageCollection04 = 65;
  this.tileWide310x150PeekImageCollection05 = 66;
  this.tileWide310x150PeekImageCollection06 = 67;
  this.tileWide310x150PeekImageAndText01 = 68;
  this.tileWide310x150PeekImageAndText02 = 69;
  this.tileWide310x150PeekImage01 = 70;
  this.tileWide310x150PeekImage02 = 71;
  this.tileWide310x150PeekImage03 = 72;
  this.tileWide310x150PeekImage04 = 73;
  this.tileWide310x150PeekImage05 = 74;
  this.tileWide310x150PeekImage06 = 75;
  this.tileWide310x150SmallImageAndText01 = 76;
  this.tileWide310x150SmallImageAndText02 = 77;
  this.tileWide310x150SmallImageAndText03 = 78;
  this.tileWide310x150SmallImageAndText04 = 79;
  this.tileWide310x150SmallImageAndText05 = 80;
  this.tileWide310x150Text01 = 81;
  this.tileWide310x150Text02 = 82;
  this.tileWide310x150Text03 = 83;
  this.tileWide310x150Text04 = 84;
  this.tileWide310x150Text05 = 85;
  this.tileWide310x150Text06 = 86;
  this.tileWide310x150Text07 = 87;
  this.tileWide310x150Text08 = 88;
  this.tileWide310x150Text09 = 89;
  this.tileWide310x150Text10 = 90;
  this.tileWide310x150Text11 = 91;
  this.tileSquare310x310BlockAndText01 = 92;
  this.tileSquare310x310BlockAndText02 = 93;
  this.tileSquare310x310Image = 94;
  this.tileSquare310x310ImageAndText01 = 95;
  this.tileSquare310x310ImageAndText02 = 96;
  this.tileSquare310x310ImageAndTextOverlay01 = 97;
  this.tileSquare310x310ImageAndTextOverlay02 = 98;
  this.tileSquare310x310ImageAndTextOverlay03 = 99;
  this.tileSquare310x310ImageCollectionAndText01 = 100;
  this.tileSquare310x310ImageCollectionAndText02 = 101;
  this.tileSquare310x310ImageCollection = 102;
  this.tileSquare310x310SmallImagesAndTextList01 = 103;
  this.tileSquare310x310SmallImagesAndTextList02 = 104;
  this.tileSquare310x310SmallImagesAndTextList03 = 105;
  this.tileSquare310x310SmallImagesAndTextList04 = 106;
  this.tileSquare310x310Text01 = 107;
  this.tileSquare310x310Text02 = 108;
  this.tileSquare310x310Text03 = 109;
  this.tileSquare310x310Text04 = 110;
  this.tileSquare310x310Text05 = 111;
  this.tileSquare310x310Text06 = 112;
  this.tileSquare310x310Text07 = 113;
  this.tileSquare310x310Text08 = 114;
  this.tileSquare310x310TextList01 = 115;
  this.tileSquare310x310TextList02 = 116;
  this.tileSquare310x310TextList03 = 117;
  this.tileSquare310x310SmallImageAndText01 = 118;
  this.tileSquare310x310SmallImagesAndTextList05 = 119;
  this.tileSquare310x310Text09 = 120;
  this.tileSquare71x71IconWithBadge = 121;
  this.tileSquare150x150IconWithBadge = 122;
  this.tileWide310x150IconWithBadgeAndText = 123;
  this.tileSquare71x71Image = 124;
  this.tileTall150x310Image = 125;
}
exports.TileTemplateType = new _TileTemplateType();

_ToastTemplateType = function () {
  this.toastImageAndText01 = 0;
  this.toastImageAndText02 = 1;
  this.toastImageAndText03 = 2;
  this.toastImageAndText04 = 3;
  this.toastText01 = 4;
  this.toastText02 = 5;
  this.toastText03 = 6;
  this.toastText04 = 7;
}
exports.ToastTemplateType = new _ToastTemplateType();

_PeriodicUpdateRecurrence = function () {
  this.halfHour = 0;
  this.hour = 1;
  this.sixHours = 2;
  this.twelveHours = 3;
  this.daily = 4;
}
exports.PeriodicUpdateRecurrence = new _PeriodicUpdateRecurrence();

_ToastHistoryChangedType = function () {
  this.cleared = 0;
  this.removed = 1;
  this.expired = 2;
  this.added = 3;
}
exports.ToastHistoryChangedType = new _ToastHistoryChangedType();

_AdaptiveNotificationContentKind = function () {
  this.text = 0;
}
exports.AdaptiveNotificationContentKind = new _AdaptiveNotificationContentKind();

_NotificationMirroring = function () {
  this.allowed = 0;
  this.disabled = 1;
}
exports.NotificationMirroring = new _NotificationMirroring();

_NotificationKinds = function () {
  this.unknown = 0;
  this.toast = 1;
}
exports.NotificationKinds = new _NotificationKinds();

_UserNotificationChangedKind = function () {
  this.added = 0;
  this.removed = 1;
}
exports.UserNotificationChangedKind = new _UserNotificationChangedKind();

ShownTileNotification = (function () {
  var cls = function ShownTileNotification() {
    this.arguments = new String();
  };
  

  return cls;
}) ();
exports.ShownTileNotification = ShownTileNotification;

Notification = (function () {
  var cls = function Notification() {
    this.visual = new NotificationVisual();
    this.expirationTime = new Date();
  };
  

  return cls;
}) ();
exports.Notification = Notification;

NotificationBinding = (function () {
  var cls = function NotificationBinding() {
    this.template = new String();
    this.language = new String();
    this.hints = new Object();
  };
  

  cls.prototype.getTextElements = function getTextElements() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  return cls;
}) ();
exports.NotificationBinding = NotificationBinding;

IAdaptiveNotificationContent = (function () {
  var cls = function IAdaptiveNotificationContent() {
    this.hints = new Object();
    this.kind = new AdaptiveNotificationContentKind();
  };
  

  return cls;
}) ();
exports.IAdaptiveNotificationContent = IAdaptiveNotificationContent;

AdaptiveNotificationText = (function () {
  var cls = function AdaptiveNotificationText() {
    this.hints = new Object();
    this.kind = new AdaptiveNotificationContentKind();
    this.text = new String();
    this.language = new String();
  };
  

  return cls;
}) ();
exports.AdaptiveNotificationText = AdaptiveNotificationText;

TileUpdater = (function () {
  var cls = function TileUpdater() {
    this.setting = new NotificationSetting();
  };
  

  cls.prototype.update = function update(notification) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="notification" type="TileNotification">A param.</param>
    /// </signature>
  }


  cls.prototype.clear = function clear() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.enableNotificationQueue = function enableNotificationQueue(enable) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="enable" type="Boolean">A param.</param>
    /// </signature>
  }


  cls.prototype.addToSchedule = function addToSchedule(scheduledTile) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="scheduledTile" type="ScheduledTileNotification">A param.</param>
    /// </signature>
  }


  cls.prototype.removeFromSchedule = function removeFromSchedule(scheduledTile) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="scheduledTile" type="ScheduledTileNotification">A param.</param>
    /// </signature>
  }


  cls.prototype.getScheduledTileNotifications = function getScheduledTileNotifications() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.prototype.startPeriodicUpdate = function startPeriodicUpdate(tileContent, requestedInterval) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="tileContent" type="Object">A param.</param>
    /// <param name="requestedInterval" type="PeriodicUpdateRecurrence">A param.</param>
    /// </signature>
  }

cls.prototype.startPeriodicUpdate = function startPeriodicUpdate(tileContent, startTime, requestedInterval) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="tileContent" type="Object">A param.</param>
    /// <param name="startTime" type="Date">A param.</param>
    /// <param name="requestedInterval" type="PeriodicUpdateRecurrence">A param.</param>
    /// </signature>
  }


  cls.prototype.stopPeriodicUpdate = function stopPeriodicUpdate() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.startPeriodicUpdateBatch = function startPeriodicUpdateBatch(tileContents, requestedInterval) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="tileContents" type="Object">A param.</param>
    /// <param name="requestedInterval" type="PeriodicUpdateRecurrence">A param.</param>
    /// </signature>
  }

cls.prototype.startPeriodicUpdateBatch = function startPeriodicUpdateBatch(tileContents, startTime, requestedInterval) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="tileContents" type="Object">A param.</param>
    /// <param name="startTime" type="Date">A param.</param>
    /// <param name="requestedInterval" type="PeriodicUpdateRecurrence">A param.</param>
    /// </signature>
  }


  cls.prototype.enableNotificationQueueForSquare150x150 = function enableNotificationQueueForSquare150x150(enable) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="enable" type="Boolean">A param.</param>
    /// </signature>
  }


  cls.prototype.enableNotificationQueueForWide310x150 = function enableNotificationQueueForWide310x150(enable) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="enable" type="Boolean">A param.</param>
    /// </signature>
  }


  cls.prototype.enableNotificationQueueForSquare310x310 = function enableNotificationQueueForSquare310x310(enable) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="enable" type="Boolean">A param.</param>
    /// </signature>
  }


  return cls;
}) ();
exports.TileUpdater = TileUpdater;

TileUpdateManagerForUser = (function () {
  var cls = function TileUpdateManagerForUser() {
    this.user = new Object();
  };
  

  cls.prototype.createTileUpdaterForApplicationForUser = function createTileUpdaterForApplicationForUser() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="TileUpdater" />
    /// </signature>
    return new TileUpdater();
  }


  cls.prototype.createTileUpdaterForApplication = function createTileUpdaterForApplication(applicationId) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="applicationId" type="String">A param.</param>
    /// <returns type="TileUpdater" />
    /// </signature>
    return new TileUpdater();
  }


  cls.prototype.createTileUpdaterForSecondaryTile = function createTileUpdaterForSecondaryTile(tileId) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="tileId" type="String">A param.</param>
    /// <returns type="TileUpdater" />
    /// </signature>
    return new TileUpdater();
  }


  return cls;
}) ();
exports.TileUpdateManagerForUser = TileUpdateManagerForUser;

TileNotification = (function () {
  var cls = function TileNotification() {
    this.tag = new String();
    this.expirationTime = new Date();
    this.content = new Object();
  };
  
var cls = function TileNotification(content) {
      this.tag = new String();
      this.expirationTime = new Date();
      this.content = new Object();
};


  return cls;
}) ();
exports.TileNotification = TileNotification;

ScheduledTileNotification = (function () {
  var cls = function ScheduledTileNotification() {
    this.tag = new String();
    this.id = new String();
    this.expirationTime = new Date();
    this.content = new Object();
    this.deliveryTime = new Date();
  };
  
var cls = function ScheduledTileNotification(content, deliveryTime) {
      this.tag = new String();
      this.id = new String();
      this.expirationTime = new Date();
      this.content = new Object();
      this.deliveryTime = new Date();
};


  return cls;
}) ();
exports.ScheduledTileNotification = ScheduledTileNotification;

TileFlyoutUpdater = (function () {
  var cls = function TileFlyoutUpdater() {
    this.setting = new NotificationSetting();
  };
  

  cls.prototype.update = function update(notification) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="notification" type="TileFlyoutNotification">A param.</param>
    /// </signature>
  }


  cls.prototype.clear = function clear() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.startPeriodicUpdate = function startPeriodicUpdate(tileFlyoutContent, requestedInterval) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="tileFlyoutContent" type="Object">A param.</param>
    /// <param name="requestedInterval" type="PeriodicUpdateRecurrence">A param.</param>
    /// </signature>
  }

cls.prototype.startPeriodicUpdate = function startPeriodicUpdate(tileFlyoutContent, startTime, requestedInterval) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="tileFlyoutContent" type="Object">A param.</param>
    /// <param name="startTime" type="Date">A param.</param>
    /// <param name="requestedInterval" type="PeriodicUpdateRecurrence">A param.</param>
    /// </signature>
  }


  cls.prototype.stopPeriodicUpdate = function stopPeriodicUpdate() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  return cls;
}) ();
exports.TileFlyoutUpdater = TileFlyoutUpdater;

TileFlyoutNotification = (function () {
  var cls = function TileFlyoutNotification() {
    this.expirationTime = new Date();
    this.content = new Object();
  };
  
var cls = function TileFlyoutNotification(content) {
      this.expirationTime = new Date();
      this.content = new Object();
};


  return cls;
}) ();
exports.TileFlyoutNotification = TileFlyoutNotification;

BadgeUpdater = (function () {
  var cls = function BadgeUpdater() {
  };
  

  cls.prototype.update = function update(notification) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="notification" type="BadgeNotification">A param.</param>
    /// </signature>
  }


  cls.prototype.clear = function clear() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.startPeriodicUpdate = function startPeriodicUpdate(badgeContent, requestedInterval) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="badgeContent" type="Object">A param.</param>
    /// <param name="requestedInterval" type="PeriodicUpdateRecurrence">A param.</param>
    /// </signature>
  }

cls.prototype.startPeriodicUpdate = function startPeriodicUpdate(badgeContent, startTime, requestedInterval) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="badgeContent" type="Object">A param.</param>
    /// <param name="startTime" type="Date">A param.</param>
    /// <param name="requestedInterval" type="PeriodicUpdateRecurrence">A param.</param>
    /// </signature>
  }


  cls.prototype.stopPeriodicUpdate = function stopPeriodicUpdate() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  return cls;
}) ();
exports.BadgeUpdater = BadgeUpdater;

BadgeUpdateManagerForUser = (function () {
  var cls = function BadgeUpdateManagerForUser() {
    this.user = new Object();
  };
  

  cls.prototype.createBadgeUpdaterForApplication = function createBadgeUpdaterForApplication() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="BadgeUpdater" />
    /// </signature>
    return new BadgeUpdater();
  }

cls.prototype.createBadgeUpdaterForApplication = function createBadgeUpdaterForApplication(applicationId) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="applicationId" type="String">A param.</param>
    /// <returns type="BadgeUpdater" />
    /// </signature>
    return new BadgeUpdater();
  }


  cls.prototype.createBadgeUpdaterForSecondaryTile = function createBadgeUpdaterForSecondaryTile(tileId) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="tileId" type="String">A param.</param>
    /// <returns type="BadgeUpdater" />
    /// </signature>
    return new BadgeUpdater();
  }


  return cls;
}) ();
exports.BadgeUpdateManagerForUser = BadgeUpdateManagerForUser;

BadgeNotification = (function () {
  var cls = function BadgeNotification() {
    this.expirationTime = new Date();
    this.content = new Object();
  };
  
var cls = function BadgeNotification(content) {
      this.expirationTime = new Date();
      this.content = new Object();
};


  return cls;
}) ();
exports.BadgeNotification = BadgeNotification;

ToastNotifier = (function () {
  var cls = function ToastNotifier() {
    this.setting = new NotificationSetting();
  };
  

  cls.prototype.show = function show(notification) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="notification" type="ToastNotification">A param.</param>
    /// </signature>
  }


  cls.prototype.hide = function hide(notification) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="notification" type="ToastNotification">A param.</param>
    /// </signature>
  }


  cls.prototype.addToSchedule = function addToSchedule(scheduledToast) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="scheduledToast" type="ScheduledToastNotification">A param.</param>
    /// </signature>
  }


  cls.prototype.removeFromSchedule = function removeFromSchedule(scheduledToast) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="scheduledToast" type="ScheduledToastNotification">A param.</param>
    /// </signature>
  }


  cls.prototype.getScheduledToastNotifications = function getScheduledToastNotifications() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  return cls;
}) ();
exports.ToastNotifier = ToastNotifier;

ToastNotification = (function () {
  var cls = function ToastNotification() {
    this.expirationTime = new Date();
    this.content = new Object();
    this.tag = new String();
    this.suppressPopup = new Boolean();
    this.group = new String();
    this.remoteId = new String();
    this.notificationMirroring = new NotificationMirroring();
  };
  
var cls = function ToastNotification(content) {
      this.expirationTime = new Date();
      this.content = new Object();
      this.tag = new String();
      this.suppressPopup = new Boolean();
      this.group = new String();
      this.remoteId = new String();
      this.notificationMirroring = new NotificationMirroring();
};


    cls.prototype.addListener = function addListener(eventName, callback){}
    cls.prototype.removeListener = function removeListener(eventName, callback){}
    cls.prototype.on = function on(eventName, callback){}
    cls.prototype.off = function off(eventName, callback){}
  return cls;
}) ();
exports.ToastNotification = ToastNotification;

ScheduledToastNotification = (function () {
  var cls = function ScheduledToastNotification() {
    this.id = new String();
    this.content = new Object();
    this.deliveryTime = new Date();
    this.maximumSnoozeCount = new Number();
    this.snoozeInterval = new Number();
    this.tag = new String();
    this.suppressPopup = new Boolean();
    this.group = new String();
    this.remoteId = new String();
    this.notificationMirroring = new NotificationMirroring();
  };
  
var cls = function ScheduledToastNotification(content, deliveryTime) {
      this.id = new String();
      this.content = new Object();
      this.deliveryTime = new Date();
      this.maximumSnoozeCount = new Number();
      this.snoozeInterval = new Number();
      this.tag = new String();
      this.suppressPopup = new Boolean();
      this.group = new String();
      this.remoteId = new String();
      this.notificationMirroring = new NotificationMirroring();
};

var cls = function ScheduledToastNotification(content, deliveryTime, snoozeInterval, maximumSnoozeCount) {
      this.id = new String();
      this.content = new Object();
      this.deliveryTime = new Date();
      this.maximumSnoozeCount = new Number();
      this.snoozeInterval = new Number();
      this.tag = new String();
      this.suppressPopup = new Boolean();
      this.group = new String();
      this.remoteId = new String();
      this.notificationMirroring = new NotificationMirroring();
};


  return cls;
}) ();
exports.ScheduledToastNotification = ScheduledToastNotification;

ToastDismissedEventArgs = (function () {
  var cls = function ToastDismissedEventArgs() {
    this.reason = new ToastDismissalReason();
  };
  

  return cls;
}) ();
exports.ToastDismissedEventArgs = ToastDismissedEventArgs;

ToastFailedEventArgs = (function () {
  var cls = function ToastFailedEventArgs() {
    this.errorCode = new Number();
  };
  

  return cls;
}) ();
exports.ToastFailedEventArgs = ToastFailedEventArgs;

NotificationVisual = (function () {
  var cls = function NotificationVisual() {
    this.language = new String();
    this.bindings = new Object();
  };
  

  cls.prototype.getBinding = function getBinding(templateName) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="templateName" type="String">A param.</param>
    /// <returns type="NotificationBinding" />
    /// </signature>
    return new NotificationBinding();
  }


  return cls;
}) ();
exports.NotificationVisual = NotificationVisual;

ToastNotificationHistory = (function () {
  var cls = function ToastNotificationHistory() {
  };
  

  cls.prototype.removeGroup = function removeGroup(group) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="group" type="String">A param.</param>
    /// </signature>
  }

cls.prototype.removeGroup = function removeGroup(group, applicationId) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="group" type="String">A param.</param>
    /// <param name="applicationId" type="String">A param.</param>
    /// </signature>
  }


  cls.prototype.remove = function remove(tag, group, applicationId) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="tag" type="String">A param.</param>
    /// <param name="group" type="String">A param.</param>
    /// <param name="applicationId" type="String">A param.</param>
    /// </signature>
  }

cls.prototype.remove = function remove(tag, group) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="tag" type="String">A param.</param>
    /// <param name="group" type="String">A param.</param>
    /// </signature>
  }

cls.prototype.remove = function remove(tag) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="tag" type="String">A param.</param>
    /// </signature>
  }


  cls.prototype.clear = function clear() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }

cls.prototype.clear = function clear(applicationId) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="applicationId" type="String">A param.</param>
    /// </signature>
  }


  cls.prototype.getHistory = function getHistory() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }

cls.prototype.getHistory = function getHistory(applicationId) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="applicationId" type="String">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  return cls;
}) ();
exports.ToastNotificationHistory = ToastNotificationHistory;

ToastNotificationManagerForUser = (function () {
  var cls = function ToastNotificationManagerForUser() {
    this.history = new ToastNotificationHistory();
    this.user = new Object();
  };
  

  cls.prototype.createToastNotifier = function createToastNotifier() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="ToastNotifier" />
    /// </signature>
    return new ToastNotifier();
  }

cls.prototype.createToastNotifier = function createToastNotifier(applicationId) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="applicationId" type="String">A param.</param>
    /// <returns type="ToastNotifier" />
    /// </signature>
    return new ToastNotifier();
  }


  return cls;
}) ();
exports.ToastNotificationManagerForUser = ToastNotificationManagerForUser;

UserNotificationChangedEventArgs = (function () {
  var cls = function UserNotificationChangedEventArgs() {
    this.changeKind = new UserNotificationChangedKind();
    this.userNotificationId = new Number();
  };
  

  return cls;
}) ();
exports.UserNotificationChangedEventArgs = UserNotificationChangedEventArgs;

UserNotification = (function () {
  var cls = function UserNotification() {
    this.appInfo = new Object();
    this.creationTime = new Date();
    this.id = new Number();
    this.notification = new Notification();
  };
  

  return cls;
}) ();
exports.UserNotification = UserNotification;

KnownAdaptiveNotificationHints = (function () {
  var cls = function KnownAdaptiveNotificationHints() {
  };
  

  cls.align = new String();
  cls.maxLines = new String();
  cls.minLines = new String();
  cls.style = new String();
  cls.textStacking = new String();
  cls.wrap = new String();
  return cls;
}) ();
exports.KnownAdaptiveNotificationHints = KnownAdaptiveNotificationHints;

KnownNotificationBindings = (function () {
  var cls = function KnownNotificationBindings() {
  };
  

  cls.toastGeneric = new String();
  return cls;
}) ();
exports.KnownNotificationBindings = KnownNotificationBindings;

KnownAdaptiveNotificationTextStyles = (function () {
  var cls = function KnownAdaptiveNotificationTextStyles() {
  };
  

  cls.base = new String();
  cls.baseSubtle = new String();
  cls.body = new String();
  cls.bodySubtle = new String();
  cls.caption = new String();
  cls.captionSubtle = new String();
  cls.header = new String();
  cls.headerNumeral = new String();
  cls.headerNumeralSubtle = new String();
  cls.headerSubtle = new String();
  cls.subheader = new String();
  cls.subheaderNumeral = new String();
  cls.subheaderNumeralSubtle = new String();
  cls.subheaderSubtle = new String();
  cls.subtitle = new String();
  cls.subtitleSubtle = new String();
  cls.title = new String();
  cls.titleNumeral = new String();
  cls.titleSubtle = new String();
  return cls;
}) ();
exports.KnownAdaptiveNotificationTextStyles = KnownAdaptiveNotificationTextStyles;

TileUpdateManager = (function () {
  var cls = function TileUpdateManager() {
  };
  

  cls.getForUser = function getForUser(user) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="user" type="Object">A param.</param>
    /// <returns type="TileUpdateManagerForUser" />
    /// </signature>
    return new TileUpdateManagerForUser();
  }


  cls.createTileUpdaterForApplication = function createTileUpdaterForApplication() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="TileUpdater" />
    /// </signature>
    return new TileUpdater();
  }

cls.createTileUpdaterForApplication = function createTileUpdaterForApplication(applicationId) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="applicationId" type="String">A param.</param>
    /// <returns type="TileUpdater" />
    /// </signature>
    return new TileUpdater();
  }


  cls.createTileUpdaterForSecondaryTile = function createTileUpdaterForSecondaryTile(tileId) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="tileId" type="String">A param.</param>
    /// <returns type="TileUpdater" />
    /// </signature>
    return new TileUpdater();
  }


  cls.getTemplateContent = function getTemplateContent(type) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="type" type="TileTemplateType">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  return cls;
}) ();
exports.TileUpdateManager = TileUpdateManager;

BadgeUpdateManager = (function () {
  var cls = function BadgeUpdateManager() {
  };
  

  cls.getForUser = function getForUser(user) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="user" type="Object">A param.</param>
    /// <returns type="BadgeUpdateManagerForUser" />
    /// </signature>
    return new BadgeUpdateManagerForUser();
  }


  cls.createBadgeUpdaterForApplication = function createBadgeUpdaterForApplication() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="BadgeUpdater" />
    /// </signature>
    return new BadgeUpdater();
  }

cls.createBadgeUpdaterForApplication = function createBadgeUpdaterForApplication(applicationId) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="applicationId" type="String">A param.</param>
    /// <returns type="BadgeUpdater" />
    /// </signature>
    return new BadgeUpdater();
  }


  cls.createBadgeUpdaterForSecondaryTile = function createBadgeUpdaterForSecondaryTile(tileId) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="tileId" type="String">A param.</param>
    /// <returns type="BadgeUpdater" />
    /// </signature>
    return new BadgeUpdater();
  }


  cls.getTemplateContent = function getTemplateContent(type) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="type" type="BadgeTemplateType">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  return cls;
}) ();
exports.BadgeUpdateManager = BadgeUpdateManager;

TileFlyoutUpdateManager = (function () {
  var cls = function TileFlyoutUpdateManager() {
  };
  

  cls.createTileFlyoutUpdaterForApplication = function createTileFlyoutUpdaterForApplication() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="TileFlyoutUpdater" />
    /// </signature>
    return new TileFlyoutUpdater();
  }

cls.createTileFlyoutUpdaterForApplication = function createTileFlyoutUpdaterForApplication(applicationId) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="applicationId" type="String">A param.</param>
    /// <returns type="TileFlyoutUpdater" />
    /// </signature>
    return new TileFlyoutUpdater();
  }


  cls.createTileFlyoutUpdaterForSecondaryTile = function createTileFlyoutUpdaterForSecondaryTile(tileId) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="tileId" type="String">A param.</param>
    /// <returns type="TileFlyoutUpdater" />
    /// </signature>
    return new TileFlyoutUpdater();
  }


  cls.getTemplateContent = function getTemplateContent(type) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="type" type="TileFlyoutTemplateType">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  return cls;
}) ();
exports.TileFlyoutUpdateManager = TileFlyoutUpdateManager;

ToastNotificationManager = (function () {
  var cls = function ToastNotificationManager() {
  };
  

  cls.getForUser = function getForUser(user) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="user" type="Object">A param.</param>
    /// <returns type="ToastNotificationManagerForUser" />
    /// </signature>
    return new ToastNotificationManagerForUser();
  }


  cls.configureNotificationMirroring = function configureNotificationMirroring(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="NotificationMirroring">A param.</param>
    /// </signature>
  }


  cls.createToastNotifier = function createToastNotifier() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="ToastNotifier" />
    /// </signature>
    return new ToastNotifier();
  }

cls.createToastNotifier = function createToastNotifier(applicationId) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="applicationId" type="String">A param.</param>
    /// <returns type="ToastNotifier" />
    /// </signature>
    return new ToastNotifier();
  }


  cls.getTemplateContent = function getTemplateContent(type) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="type" type="ToastTemplateType">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.history = new ToastNotificationHistory();
  return cls;
}) ();
exports.ToastNotificationManager = ToastNotificationManager;

ToastActivatedEventArgs = (function () {
  var cls = function ToastActivatedEventArgs() {
    this.arguments = new String();
  };
  

  return cls;
}) ();
exports.ToastActivatedEventArgs = ToastActivatedEventArgs;

ToastNotificationHistoryChangedTriggerDetail = (function () {
  var cls = function ToastNotificationHistoryChangedTriggerDetail() {
    this.changeType = new ToastHistoryChangedType();
  };
  

  return cls;
}) ();
exports.ToastNotificationHistoryChangedTriggerDetail = ToastNotificationHistoryChangedTriggerDetail;

ToastNotificationActionTriggerDetail = (function () {
  var cls = function ToastNotificationActionTriggerDetail() {
    this.argument = new String();
    this.userInput = new Object();
  };
  

  return cls;
}) ();
exports.ToastNotificationActionTriggerDetail = ToastNotificationActionTriggerDetail;

