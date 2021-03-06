// Copyright (c) Microsoft Corporation
// All rights reserved. 
//
// Licensed under the Apache License, Version 2.0 (the ""License""); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0 
//
// THIS CODE IS PROVIDED ON AN  *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE, MERCHANTABLITY OR NON-INFRINGEMENT. 
//
// See the Apache Version 2.0 License for specific language governing permissions and limitations under the License.

// TODO: Verify that this is is still needed..
#define NTDDI_VERSION 0x06010000

#include <v8.h>
#include "nan.h"
#include <string>
#include <ppltasks.h>
#include "CollectionsConverter.h"
#include "CollectionsWrap.h"
#include "node-async.h"
#include "NodeRtUtils.h"
#include "OpaqueWrapper.h"
#include "WrapperBase.h"

#using <Windows.WinMD>

// this undefs fixes the issues of compiling Windows.Data.Json, Windows.Storag.FileProperties, and Windows.Stroage.Search
// Some of the node header files brings windows definitions with the same names as some of the WinRT methods
#undef DocumentProperties
#undef GetObject
#undef CreateEvent
#undef FindText
#undef SendMessage

const char* REGISTRATION_TOKEN_MAP_PROPERTY_NAME = "__registrationTokenMap__";

using v8::Array;
using v8::String;
using v8::Handle;
using v8::Value;
using v8::Boolean;
using v8::Integer;
using v8::FunctionTemplate;
using v8::Object;
using v8::Local;
using v8::Function;
using v8::Date;
using v8::Number;
using v8::PropertyAttribute;
using v8::Primitive;
using Nan::HandleScope;
using Nan::Persistent;
using Nan::Undefined;
using Nan::True;
using Nan::False;
using Nan::Null;
using Nan::MaybeLocal;
using Nan::EscapableHandleScope;
using Nan::HandleScope;
using Nan::TryCatch;
using namespace concurrency;

namespace NodeRT { namespace Windows { namespace UI { namespace Notifications { 

  v8::Local<v8::Value> WrapShownTileNotification(::Windows::UI::Notifications::ShownTileNotification^ wintRtInstance);
  ::Windows::UI::Notifications::ShownTileNotification^ UnwrapShownTileNotification(Local<Value> value);
  
  v8::Local<v8::Value> WrapNotification(::Windows::UI::Notifications::Notification^ wintRtInstance);
  ::Windows::UI::Notifications::Notification^ UnwrapNotification(Local<Value> value);
  
  v8::Local<v8::Value> WrapNotificationBinding(::Windows::UI::Notifications::NotificationBinding^ wintRtInstance);
  ::Windows::UI::Notifications::NotificationBinding^ UnwrapNotificationBinding(Local<Value> value);
  
  v8::Local<v8::Value> WrapIAdaptiveNotificationContent(::Windows::UI::Notifications::IAdaptiveNotificationContent^ wintRtInstance);
  ::Windows::UI::Notifications::IAdaptiveNotificationContent^ UnwrapIAdaptiveNotificationContent(Local<Value> value);
  
  v8::Local<v8::Value> WrapAdaptiveNotificationText(::Windows::UI::Notifications::AdaptiveNotificationText^ wintRtInstance);
  ::Windows::UI::Notifications::AdaptiveNotificationText^ UnwrapAdaptiveNotificationText(Local<Value> value);
  
  v8::Local<v8::Value> WrapTileUpdater(::Windows::UI::Notifications::TileUpdater^ wintRtInstance);
  ::Windows::UI::Notifications::TileUpdater^ UnwrapTileUpdater(Local<Value> value);
  
  v8::Local<v8::Value> WrapTileUpdateManagerForUser(::Windows::UI::Notifications::TileUpdateManagerForUser^ wintRtInstance);
  ::Windows::UI::Notifications::TileUpdateManagerForUser^ UnwrapTileUpdateManagerForUser(Local<Value> value);
  
  v8::Local<v8::Value> WrapTileNotification(::Windows::UI::Notifications::TileNotification^ wintRtInstance);
  ::Windows::UI::Notifications::TileNotification^ UnwrapTileNotification(Local<Value> value);
  
  v8::Local<v8::Value> WrapScheduledTileNotification(::Windows::UI::Notifications::ScheduledTileNotification^ wintRtInstance);
  ::Windows::UI::Notifications::ScheduledTileNotification^ UnwrapScheduledTileNotification(Local<Value> value);
  
  v8::Local<v8::Value> WrapTileFlyoutUpdater(::Windows::UI::Notifications::TileFlyoutUpdater^ wintRtInstance);
  ::Windows::UI::Notifications::TileFlyoutUpdater^ UnwrapTileFlyoutUpdater(Local<Value> value);
  
  v8::Local<v8::Value> WrapTileFlyoutNotification(::Windows::UI::Notifications::TileFlyoutNotification^ wintRtInstance);
  ::Windows::UI::Notifications::TileFlyoutNotification^ UnwrapTileFlyoutNotification(Local<Value> value);
  
  v8::Local<v8::Value> WrapBadgeUpdater(::Windows::UI::Notifications::BadgeUpdater^ wintRtInstance);
  ::Windows::UI::Notifications::BadgeUpdater^ UnwrapBadgeUpdater(Local<Value> value);
  
  v8::Local<v8::Value> WrapBadgeUpdateManagerForUser(::Windows::UI::Notifications::BadgeUpdateManagerForUser^ wintRtInstance);
  ::Windows::UI::Notifications::BadgeUpdateManagerForUser^ UnwrapBadgeUpdateManagerForUser(Local<Value> value);
  
  v8::Local<v8::Value> WrapBadgeNotification(::Windows::UI::Notifications::BadgeNotification^ wintRtInstance);
  ::Windows::UI::Notifications::BadgeNotification^ UnwrapBadgeNotification(Local<Value> value);
  
  v8::Local<v8::Value> WrapToastNotifier(::Windows::UI::Notifications::ToastNotifier^ wintRtInstance);
  ::Windows::UI::Notifications::ToastNotifier^ UnwrapToastNotifier(Local<Value> value);
  
  v8::Local<v8::Value> WrapToastNotification(::Windows::UI::Notifications::ToastNotification^ wintRtInstance);
  ::Windows::UI::Notifications::ToastNotification^ UnwrapToastNotification(Local<Value> value);
  
  v8::Local<v8::Value> WrapScheduledToastNotification(::Windows::UI::Notifications::ScheduledToastNotification^ wintRtInstance);
  ::Windows::UI::Notifications::ScheduledToastNotification^ UnwrapScheduledToastNotification(Local<Value> value);
  
  v8::Local<v8::Value> WrapToastDismissedEventArgs(::Windows::UI::Notifications::ToastDismissedEventArgs^ wintRtInstance);
  ::Windows::UI::Notifications::ToastDismissedEventArgs^ UnwrapToastDismissedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapToastFailedEventArgs(::Windows::UI::Notifications::ToastFailedEventArgs^ wintRtInstance);
  ::Windows::UI::Notifications::ToastFailedEventArgs^ UnwrapToastFailedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapNotificationVisual(::Windows::UI::Notifications::NotificationVisual^ wintRtInstance);
  ::Windows::UI::Notifications::NotificationVisual^ UnwrapNotificationVisual(Local<Value> value);
  
  v8::Local<v8::Value> WrapToastNotificationHistory(::Windows::UI::Notifications::ToastNotificationHistory^ wintRtInstance);
  ::Windows::UI::Notifications::ToastNotificationHistory^ UnwrapToastNotificationHistory(Local<Value> value);
  
  v8::Local<v8::Value> WrapToastNotificationManagerForUser(::Windows::UI::Notifications::ToastNotificationManagerForUser^ wintRtInstance);
  ::Windows::UI::Notifications::ToastNotificationManagerForUser^ UnwrapToastNotificationManagerForUser(Local<Value> value);
  
  v8::Local<v8::Value> WrapUserNotificationChangedEventArgs(::Windows::UI::Notifications::UserNotificationChangedEventArgs^ wintRtInstance);
  ::Windows::UI::Notifications::UserNotificationChangedEventArgs^ UnwrapUserNotificationChangedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapUserNotification(::Windows::UI::Notifications::UserNotification^ wintRtInstance);
  ::Windows::UI::Notifications::UserNotification^ UnwrapUserNotification(Local<Value> value);
  
  v8::Local<v8::Value> WrapKnownAdaptiveNotificationHints(::Windows::UI::Notifications::KnownAdaptiveNotificationHints^ wintRtInstance);
  ::Windows::UI::Notifications::KnownAdaptiveNotificationHints^ UnwrapKnownAdaptiveNotificationHints(Local<Value> value);
  
  v8::Local<v8::Value> WrapKnownNotificationBindings(::Windows::UI::Notifications::KnownNotificationBindings^ wintRtInstance);
  ::Windows::UI::Notifications::KnownNotificationBindings^ UnwrapKnownNotificationBindings(Local<Value> value);
  
  v8::Local<v8::Value> WrapKnownAdaptiveNotificationTextStyles(::Windows::UI::Notifications::KnownAdaptiveNotificationTextStyles^ wintRtInstance);
  ::Windows::UI::Notifications::KnownAdaptiveNotificationTextStyles^ UnwrapKnownAdaptiveNotificationTextStyles(Local<Value> value);
  
  v8::Local<v8::Value> WrapTileUpdateManager(::Windows::UI::Notifications::TileUpdateManager^ wintRtInstance);
  ::Windows::UI::Notifications::TileUpdateManager^ UnwrapTileUpdateManager(Local<Value> value);
  
  v8::Local<v8::Value> WrapBadgeUpdateManager(::Windows::UI::Notifications::BadgeUpdateManager^ wintRtInstance);
  ::Windows::UI::Notifications::BadgeUpdateManager^ UnwrapBadgeUpdateManager(Local<Value> value);
  
  v8::Local<v8::Value> WrapTileFlyoutUpdateManager(::Windows::UI::Notifications::TileFlyoutUpdateManager^ wintRtInstance);
  ::Windows::UI::Notifications::TileFlyoutUpdateManager^ UnwrapTileFlyoutUpdateManager(Local<Value> value);
  
  v8::Local<v8::Value> WrapToastNotificationManager(::Windows::UI::Notifications::ToastNotificationManager^ wintRtInstance);
  ::Windows::UI::Notifications::ToastNotificationManager^ UnwrapToastNotificationManager(Local<Value> value);
  
  v8::Local<v8::Value> WrapToastActivatedEventArgs(::Windows::UI::Notifications::ToastActivatedEventArgs^ wintRtInstance);
  ::Windows::UI::Notifications::ToastActivatedEventArgs^ UnwrapToastActivatedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapToastNotificationHistoryChangedTriggerDetail(::Windows::UI::Notifications::ToastNotificationHistoryChangedTriggerDetail^ wintRtInstance);
  ::Windows::UI::Notifications::ToastNotificationHistoryChangedTriggerDetail^ UnwrapToastNotificationHistoryChangedTriggerDetail(Local<Value> value);
  
  v8::Local<v8::Value> WrapToastNotificationActionTriggerDetail(::Windows::UI::Notifications::ToastNotificationActionTriggerDetail^ wintRtInstance);
  ::Windows::UI::Notifications::ToastNotificationActionTriggerDetail^ UnwrapToastNotificationActionTriggerDetail(Local<Value> value);
  


  static void InitNotificationSettingEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("NotificationSetting").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("enabled").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::NotificationSetting::Enabled)));
	Nan::Set(enumObject, Nan::New<String>("disabledForApplication").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::NotificationSetting::DisabledForApplication)));
	Nan::Set(enumObject, Nan::New<String>("disabledForUser").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::NotificationSetting::DisabledForUser)));
	Nan::Set(enumObject, Nan::New<String>("disabledByGroupPolicy").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::NotificationSetting::DisabledByGroupPolicy)));
	Nan::Set(enumObject, Nan::New<String>("disabledByManifest").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::NotificationSetting::DisabledByManifest)));
  }


  static void InitToastDismissalReasonEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("ToastDismissalReason").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("userCanceled").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::ToastDismissalReason::UserCanceled)));
	Nan::Set(enumObject, Nan::New<String>("applicationHidden").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::ToastDismissalReason::ApplicationHidden)));
	Nan::Set(enumObject, Nan::New<String>("timedOut").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::ToastDismissalReason::TimedOut)));
  }


  static void InitBadgeTemplateTypeEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("BadgeTemplateType").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("badgeGlyph").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::BadgeTemplateType::BadgeGlyph)));
	Nan::Set(enumObject, Nan::New<String>("badgeNumber").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::BadgeTemplateType::BadgeNumber)));
  }


  static void InitTileFlyoutTemplateTypeEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("TileFlyoutTemplateType").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("tileFlyoutTemplate01").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileFlyoutTemplateType::TileFlyoutTemplate01)));
  }


  static void InitTileTemplateTypeEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("TileTemplateType").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("tileSquare150x150Image").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare150x150Image)));
	Nan::Set(enumObject, Nan::New<String>("tileSquareImage").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquareImage)));
	Nan::Set(enumObject, Nan::New<String>("tileSquareBlock").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquareBlock)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare150x150Block").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare150x150Block)));
	Nan::Set(enumObject, Nan::New<String>("tileSquareText01").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquareText01)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare150x150Text01").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare150x150Text01)));
	Nan::Set(enumObject, Nan::New<String>("tileSquareText02").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquareText02)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare150x150Text02").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare150x150Text02)));
	Nan::Set(enumObject, Nan::New<String>("tileSquareText03").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquareText03)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare150x150Text03").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare150x150Text03)));
	Nan::Set(enumObject, Nan::New<String>("tileSquareText04").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquareText04)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare150x150Text04").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare150x150Text04)));
	Nan::Set(enumObject, Nan::New<String>("tileSquarePeekImageAndText01").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquarePeekImageAndText01)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare150x150PeekImageAndText01").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare150x150PeekImageAndText01)));
	Nan::Set(enumObject, Nan::New<String>("tileSquarePeekImageAndText02").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquarePeekImageAndText02)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare150x150PeekImageAndText02").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare150x150PeekImageAndText02)));
	Nan::Set(enumObject, Nan::New<String>("tileSquarePeekImageAndText03").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquarePeekImageAndText03)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare150x150PeekImageAndText03").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare150x150PeekImageAndText03)));
	Nan::Set(enumObject, Nan::New<String>("tileSquarePeekImageAndText04").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquarePeekImageAndText04)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare150x150PeekImageAndText04").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare150x150PeekImageAndText04)));
	Nan::Set(enumObject, Nan::New<String>("tileWideImage").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWideImage)));
	Nan::Set(enumObject, Nan::New<String>("tileWide310x150Image").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWide310x150Image)));
	Nan::Set(enumObject, Nan::New<String>("tileWideImageCollection").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWideImageCollection)));
	Nan::Set(enumObject, Nan::New<String>("tileWide310x150ImageCollection").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWide310x150ImageCollection)));
	Nan::Set(enumObject, Nan::New<String>("tileWideImageAndText01").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWideImageAndText01)));
	Nan::Set(enumObject, Nan::New<String>("tileWide310x150ImageAndText01").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWide310x150ImageAndText01)));
	Nan::Set(enumObject, Nan::New<String>("tileWideImageAndText02").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWideImageAndText02)));
	Nan::Set(enumObject, Nan::New<String>("tileWide310x150ImageAndText02").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWide310x150ImageAndText02)));
	Nan::Set(enumObject, Nan::New<String>("tileWideBlockAndText01").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWideBlockAndText01)));
	Nan::Set(enumObject, Nan::New<String>("tileWide310x150BlockAndText01").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWide310x150BlockAndText01)));
	Nan::Set(enumObject, Nan::New<String>("tileWideBlockAndText02").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWideBlockAndText02)));
	Nan::Set(enumObject, Nan::New<String>("tileWide310x150BlockAndText02").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWide310x150BlockAndText02)));
	Nan::Set(enumObject, Nan::New<String>("tileWide310x150PeekImageCollection01").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWide310x150PeekImageCollection01)));
	Nan::Set(enumObject, Nan::New<String>("tileWidePeekImageCollection01").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWidePeekImageCollection01)));
	Nan::Set(enumObject, Nan::New<String>("tileWidePeekImageCollection02").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWidePeekImageCollection02)));
	Nan::Set(enumObject, Nan::New<String>("tileWide310x150PeekImageCollection02").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWide310x150PeekImageCollection02)));
	Nan::Set(enumObject, Nan::New<String>("tileWidePeekImageCollection03").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWidePeekImageCollection03)));
	Nan::Set(enumObject, Nan::New<String>("tileWide310x150PeekImageCollection03").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWide310x150PeekImageCollection03)));
	Nan::Set(enumObject, Nan::New<String>("tileWidePeekImageCollection04").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWidePeekImageCollection04)));
	Nan::Set(enumObject, Nan::New<String>("tileWide310x150PeekImageCollection04").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWide310x150PeekImageCollection04)));
	Nan::Set(enumObject, Nan::New<String>("tileWidePeekImageCollection05").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWidePeekImageCollection05)));
	Nan::Set(enumObject, Nan::New<String>("tileWide310x150PeekImageCollection05").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWide310x150PeekImageCollection05)));
	Nan::Set(enumObject, Nan::New<String>("tileWidePeekImageCollection06").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWidePeekImageCollection06)));
	Nan::Set(enumObject, Nan::New<String>("tileWide310x150PeekImageCollection06").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWide310x150PeekImageCollection06)));
	Nan::Set(enumObject, Nan::New<String>("tileWidePeekImageAndText01").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWidePeekImageAndText01)));
	Nan::Set(enumObject, Nan::New<String>("tileWide310x150PeekImageAndText01").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWide310x150PeekImageAndText01)));
	Nan::Set(enumObject, Nan::New<String>("tileWidePeekImageAndText02").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWidePeekImageAndText02)));
	Nan::Set(enumObject, Nan::New<String>("tileWide310x150PeekImageAndText02").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWide310x150PeekImageAndText02)));
	Nan::Set(enumObject, Nan::New<String>("tileWidePeekImage01").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWidePeekImage01)));
	Nan::Set(enumObject, Nan::New<String>("tileWide310x150PeekImage01").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWide310x150PeekImage01)));
	Nan::Set(enumObject, Nan::New<String>("tileWidePeekImage02").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWidePeekImage02)));
	Nan::Set(enumObject, Nan::New<String>("tileWide310x150PeekImage02").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWide310x150PeekImage02)));
	Nan::Set(enumObject, Nan::New<String>("tileWidePeekImage03").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWidePeekImage03)));
	Nan::Set(enumObject, Nan::New<String>("tileWide310x150PeekImage03").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWide310x150PeekImage03)));
	Nan::Set(enumObject, Nan::New<String>("tileWidePeekImage04").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWidePeekImage04)));
	Nan::Set(enumObject, Nan::New<String>("tileWide310x150PeekImage04").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWide310x150PeekImage04)));
	Nan::Set(enumObject, Nan::New<String>("tileWidePeekImage05").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWidePeekImage05)));
	Nan::Set(enumObject, Nan::New<String>("tileWide310x150PeekImage05").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWide310x150PeekImage05)));
	Nan::Set(enumObject, Nan::New<String>("tileWidePeekImage06").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWidePeekImage06)));
	Nan::Set(enumObject, Nan::New<String>("tileWide310x150PeekImage06").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWide310x150PeekImage06)));
	Nan::Set(enumObject, Nan::New<String>("tileWideSmallImageAndText01").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWideSmallImageAndText01)));
	Nan::Set(enumObject, Nan::New<String>("tileWide310x150SmallImageAndText01").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWide310x150SmallImageAndText01)));
	Nan::Set(enumObject, Nan::New<String>("tileWideSmallImageAndText02").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWideSmallImageAndText02)));
	Nan::Set(enumObject, Nan::New<String>("tileWide310x150SmallImageAndText02").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWide310x150SmallImageAndText02)));
	Nan::Set(enumObject, Nan::New<String>("tileWideSmallImageAndText03").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWideSmallImageAndText03)));
	Nan::Set(enumObject, Nan::New<String>("tileWide310x150SmallImageAndText03").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWide310x150SmallImageAndText03)));
	Nan::Set(enumObject, Nan::New<String>("tileWide310x150SmallImageAndText04").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWide310x150SmallImageAndText04)));
	Nan::Set(enumObject, Nan::New<String>("tileWideSmallImageAndText04").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWideSmallImageAndText04)));
	Nan::Set(enumObject, Nan::New<String>("tileWideSmallImageAndText05").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWideSmallImageAndText05)));
	Nan::Set(enumObject, Nan::New<String>("tileWide310x150SmallImageAndText05").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWide310x150SmallImageAndText05)));
	Nan::Set(enumObject, Nan::New<String>("tileWide310x150Text01").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWide310x150Text01)));
	Nan::Set(enumObject, Nan::New<String>("tileWideText01").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWideText01)));
	Nan::Set(enumObject, Nan::New<String>("tileWideText02").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWideText02)));
	Nan::Set(enumObject, Nan::New<String>("tileWide310x150Text02").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWide310x150Text02)));
	Nan::Set(enumObject, Nan::New<String>("tileWide310x150Text03").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWide310x150Text03)));
	Nan::Set(enumObject, Nan::New<String>("tileWideText03").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWideText03)));
	Nan::Set(enumObject, Nan::New<String>("tileWide310x150Text04").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWide310x150Text04)));
	Nan::Set(enumObject, Nan::New<String>("tileWideText04").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWideText04)));
	Nan::Set(enumObject, Nan::New<String>("tileWide310x150Text05").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWide310x150Text05)));
	Nan::Set(enumObject, Nan::New<String>("tileWideText05").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWideText05)));
	Nan::Set(enumObject, Nan::New<String>("tileWideText06").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWideText06)));
	Nan::Set(enumObject, Nan::New<String>("tileWide310x150Text06").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWide310x150Text06)));
	Nan::Set(enumObject, Nan::New<String>("tileWide310x150Text07").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWide310x150Text07)));
	Nan::Set(enumObject, Nan::New<String>("tileWideText07").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWideText07)));
	Nan::Set(enumObject, Nan::New<String>("tileWideText08").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWideText08)));
	Nan::Set(enumObject, Nan::New<String>("tileWide310x150Text08").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWide310x150Text08)));
	Nan::Set(enumObject, Nan::New<String>("tileWide310x150Text09").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWide310x150Text09)));
	Nan::Set(enumObject, Nan::New<String>("tileWideText09").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWideText09)));
	Nan::Set(enumObject, Nan::New<String>("tileWide310x150Text10").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWide310x150Text10)));
	Nan::Set(enumObject, Nan::New<String>("tileWideText10").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWideText10)));
	Nan::Set(enumObject, Nan::New<String>("tileWide310x150Text11").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWide310x150Text11)));
	Nan::Set(enumObject, Nan::New<String>("tileWideText11").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWideText11)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare310x310BlockAndText01").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare310x310BlockAndText01)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare310x310BlockAndText02").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare310x310BlockAndText02)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare310x310Image").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare310x310Image)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare310x310ImageAndText01").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare310x310ImageAndText01)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare310x310ImageAndText02").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare310x310ImageAndText02)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare310x310ImageAndTextOverlay01").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare310x310ImageAndTextOverlay01)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare310x310ImageAndTextOverlay02").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare310x310ImageAndTextOverlay02)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare310x310ImageAndTextOverlay03").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare310x310ImageAndTextOverlay03)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare310x310ImageCollectionAndText01").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare310x310ImageCollectionAndText01)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare310x310ImageCollectionAndText02").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare310x310ImageCollectionAndText02)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare310x310ImageCollection").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare310x310ImageCollection)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare310x310SmallImagesAndTextList01").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare310x310SmallImagesAndTextList01)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare310x310SmallImagesAndTextList02").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare310x310SmallImagesAndTextList02)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare310x310SmallImagesAndTextList03").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare310x310SmallImagesAndTextList03)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare310x310SmallImagesAndTextList04").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare310x310SmallImagesAndTextList04)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare310x310Text01").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare310x310Text01)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare310x310Text02").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare310x310Text02)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare310x310Text03").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare310x310Text03)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare310x310Text04").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare310x310Text04)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare310x310Text05").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare310x310Text05)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare310x310Text06").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare310x310Text06)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare310x310Text07").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare310x310Text07)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare310x310Text08").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare310x310Text08)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare310x310TextList01").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare310x310TextList01)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare310x310TextList02").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare310x310TextList02)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare310x310TextList03").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare310x310TextList03)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare310x310SmallImageAndText01").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare310x310SmallImageAndText01)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare310x310SmallImagesAndTextList05").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare310x310SmallImagesAndTextList05)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare310x310Text09").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare310x310Text09)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare71x71IconWithBadge").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare71x71IconWithBadge)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare150x150IconWithBadge").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare150x150IconWithBadge)));
	Nan::Set(enumObject, Nan::New<String>("tileWide310x150IconWithBadgeAndText").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileWide310x150IconWithBadgeAndText)));
	Nan::Set(enumObject, Nan::New<String>("tileSquare71x71Image").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileSquare71x71Image)));
	Nan::Set(enumObject, Nan::New<String>("tileTall150x310Image").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::TileTemplateType::TileTall150x310Image)));
  }


  static void InitToastTemplateTypeEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("ToastTemplateType").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("toastImageAndText01").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::ToastTemplateType::ToastImageAndText01)));
	Nan::Set(enumObject, Nan::New<String>("toastImageAndText02").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::ToastTemplateType::ToastImageAndText02)));
	Nan::Set(enumObject, Nan::New<String>("toastImageAndText03").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::ToastTemplateType::ToastImageAndText03)));
	Nan::Set(enumObject, Nan::New<String>("toastImageAndText04").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::ToastTemplateType::ToastImageAndText04)));
	Nan::Set(enumObject, Nan::New<String>("toastText01").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::ToastTemplateType::ToastText01)));
	Nan::Set(enumObject, Nan::New<String>("toastText02").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::ToastTemplateType::ToastText02)));
	Nan::Set(enumObject, Nan::New<String>("toastText03").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::ToastTemplateType::ToastText03)));
	Nan::Set(enumObject, Nan::New<String>("toastText04").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::ToastTemplateType::ToastText04)));
  }


  static void InitPeriodicUpdateRecurrenceEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("PeriodicUpdateRecurrence").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("halfHour").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::PeriodicUpdateRecurrence::HalfHour)));
	Nan::Set(enumObject, Nan::New<String>("hour").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::PeriodicUpdateRecurrence::Hour)));
	Nan::Set(enumObject, Nan::New<String>("sixHours").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::PeriodicUpdateRecurrence::SixHours)));
	Nan::Set(enumObject, Nan::New<String>("twelveHours").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::PeriodicUpdateRecurrence::TwelveHours)));
	Nan::Set(enumObject, Nan::New<String>("daily").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::PeriodicUpdateRecurrence::Daily)));
  }


  static void InitToastHistoryChangedTypeEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("ToastHistoryChangedType").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("cleared").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::ToastHistoryChangedType::Cleared)));
	Nan::Set(enumObject, Nan::New<String>("removed").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::ToastHistoryChangedType::Removed)));
	Nan::Set(enumObject, Nan::New<String>("expired").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::ToastHistoryChangedType::Expired)));
	Nan::Set(enumObject, Nan::New<String>("added").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::ToastHistoryChangedType::Added)));
  }


  static void InitAdaptiveNotificationContentKindEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("AdaptiveNotificationContentKind").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("text").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::AdaptiveNotificationContentKind::Text)));
  }


  static void InitNotificationMirroringEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("NotificationMirroring").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("allowed").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::NotificationMirroring::Allowed)));
	Nan::Set(enumObject, Nan::New<String>("disabled").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::NotificationMirroring::Disabled)));
  }


  static void InitNotificationKindsEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("NotificationKinds").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("unknown").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::NotificationKinds::Unknown)));
	Nan::Set(enumObject, Nan::New<String>("toast").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::NotificationKinds::Toast)));
  }


  static void InitUserNotificationChangedKindEnum(const Local<Object> exports)
  {
    HandleScope scope;
    
	Local<Object> enumObject = Nan::New<Object>();
    Nan::Set(exports, Nan::New<String>("UserNotificationChangedKind").ToLocalChecked(), enumObject);
	Nan::Set(enumObject, Nan::New<String>("added").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::UserNotificationChangedKind::Added)));
	Nan::Set(enumObject, Nan::New<String>("removed").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::UI::Notifications::UserNotificationChangedKind::Removed)));
  }



  
  class ShownTileNotification : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("ShownTileNotification").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("arguments").ToLocalChecked(), ArgumentsGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();


      Nan::Set(exports, Nan::New<String>("ShownTileNotification").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    ShownTileNotification(::Windows::UI::Notifications::ShownTileNotification^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Value> res = Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::UI::Notifications::ShownTileNotification^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ShownTileNotification^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::Notifications::ShownTileNotification^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      ShownTileNotification *wrapperInstance = new ShownTileNotification(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  



    static void ArgumentsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ShownTileNotification^>(info.This()))
      {
        return;
      }

      ShownTileNotification *wrapper = ShownTileNotification::Unwrap<ShownTileNotification>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Arguments;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::UI::Notifications::ShownTileNotification^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapShownTileNotification(::Windows::UI::Notifications::ShownTileNotification^ wintRtInstance);
    friend ::Windows::UI::Notifications::ShownTileNotification^ UnwrapShownTileNotification(Local<Value> value);
  };
  Persistent<FunctionTemplate> ShownTileNotification::s_constructorTemplate;

  v8::Local<v8::Value> WrapShownTileNotification(::Windows::UI::Notifications::ShownTileNotification^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(ShownTileNotification::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::Notifications::ShownTileNotification^ UnwrapShownTileNotification(Local<Value> value)
  {
     return ShownTileNotification::Unwrap<ShownTileNotification>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitShownTileNotification(Local<Object> exports)
  {
    ShownTileNotification::Init(exports);
  }

  class Notification : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("Notification").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("visual").ToLocalChecked(), VisualGetter, VisualSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("expirationTime").ToLocalChecked(), ExpirationTimeGetter, ExpirationTimeSetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();


      Nan::Set(exports, Nan::New<String>("Notification").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    Notification(::Windows::UI::Notifications::Notification^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Value> res = Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::UI::Notifications::Notification^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::Notification^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::Notifications::Notification^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 0)
      {
        try
        {
          winRtInstance = ref new ::Windows::UI::Notifications::Notification();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      Notification *wrapperInstance = new Notification(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  



    static void VisualGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::Notification^>(info.This()))
      {
        return;
      }

      Notification *wrapper = Notification::Unwrap<Notification>(info.This());

      try 
      {
        ::Windows::UI::Notifications::NotificationVisual^ result = wrapper->_instance->Visual;
        info.GetReturnValue().Set(WrapNotificationVisual(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void VisualSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::NotificationVisual^>(value))
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::Notification^>(info.This()))
      {
        return;
      }

      Notification *wrapper = Notification::Unwrap<Notification>(info.This());

      try 
      {
        
        ::Windows::UI::Notifications::NotificationVisual^ winRtValue = dynamic_cast<::Windows::UI::Notifications::NotificationVisual^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->Visual = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void ExpirationTimeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::Notification^>(info.This()))
      {
        return;
      }

      Notification *wrapper = Notification::Unwrap<Notification>(info.This());

      try 
      {
        ::Platform::IBox<::Windows::Foundation::DateTime>^ result = wrapper->_instance->ExpirationTime;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(NodeRT::Utils::DateTimeToJS(result->Value)) : Undefined());
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ExpirationTimeSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsDate())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::Notification^>(info.This()))
      {
        return;
      }

      Notification *wrapper = Notification::Unwrap<Notification>(info.This());

      try 
      {
        
        ::Platform::IBox<::Windows::Foundation::DateTime>^ winRtValue = ref new ::Platform::Box<::Windows::Foundation::DateTime>(NodeRT::Utils::DateTimeFromJSDate(value));

        wrapper->_instance->ExpirationTime = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    


  private:
    ::Windows::UI::Notifications::Notification^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapNotification(::Windows::UI::Notifications::Notification^ wintRtInstance);
    friend ::Windows::UI::Notifications::Notification^ UnwrapNotification(Local<Value> value);
  };
  Persistent<FunctionTemplate> Notification::s_constructorTemplate;

  v8::Local<v8::Value> WrapNotification(::Windows::UI::Notifications::Notification^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(Notification::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::Notifications::Notification^ UnwrapNotification(Local<Value> value)
  {
     return Notification::Unwrap<Notification>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitNotification(Local<Object> exports)
  {
    Notification::Init(exports);
  }

  class NotificationBinding : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("NotificationBinding").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "getTextElements", GetTextElements);
      
                        
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("template").ToLocalChecked(), TemplateGetter, TemplateSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("language").ToLocalChecked(), LanguageGetter, LanguageSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("hints").ToLocalChecked(), HintsGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();


      Nan::Set(exports, Nan::New<String>("NotificationBinding").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    NotificationBinding(::Windows::UI::Notifications::NotificationBinding^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Value> res = Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::UI::Notifications::NotificationBinding^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::NotificationBinding^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::Notifications::NotificationBinding^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      NotificationBinding *wrapperInstance = new NotificationBinding(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  
    static void GetTextElements(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::NotificationBinding^>(info.This()))
      {
        return;
      }

      NotificationBinding *wrapper = NotificationBinding::Unwrap<NotificationBinding>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Collections::IVectorView<::Windows::UI::Notifications::AdaptiveNotificationText^>^ result;
          result = wrapper->_instance->GetTextElements();
          info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::UI::Notifications::AdaptiveNotificationText^>::CreateVectorViewWrapper(result, 
            [](::Windows::UI::Notifications::AdaptiveNotificationText^ val) -> Local<Value> {
              return WrapAdaptiveNotificationText(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::AdaptiveNotificationText^>(value);
            },
            [](Local<Value> value) -> ::Windows::UI::Notifications::AdaptiveNotificationText^ {
              return UnwrapAdaptiveNotificationText(value);
            }
          ));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void TemplateGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::NotificationBinding^>(info.This()))
      {
        return;
      }

      NotificationBinding *wrapper = NotificationBinding::Unwrap<NotificationBinding>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Template;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void TemplateSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsString())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::NotificationBinding^>(info.This()))
      {
        return;
      }

      NotificationBinding *wrapper = NotificationBinding::Unwrap<NotificationBinding>(info.This());

      try 
      {
        
        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));

        wrapper->_instance->Template = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void LanguageGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::NotificationBinding^>(info.This()))
      {
        return;
      }

      NotificationBinding *wrapper = NotificationBinding::Unwrap<NotificationBinding>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Language;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void LanguageSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsString())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::NotificationBinding^>(info.This()))
      {
        return;
      }

      NotificationBinding *wrapper = NotificationBinding::Unwrap<NotificationBinding>(info.This());

      try 
      {
        
        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));

        wrapper->_instance->Language = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void HintsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::NotificationBinding^>(info.This()))
      {
        return;
      }

      NotificationBinding *wrapper = NotificationBinding::Unwrap<NotificationBinding>(info.This());

      try 
      {
        ::Windows::Foundation::Collections::IMap<::Platform::String^, ::Platform::String^>^ result = wrapper->_instance->Hints;
        info.GetReturnValue().Set(NodeRT::Collections::MapWrapper<::Platform::String^,::Platform::String^>::CreateMapWrapper(result, 
            [](::Platform::String^ val) -> Local<Value> {
              return NodeRT::Utils::NewString(val->Data());
            },
            [](Local<Value> value) -> bool {
              return value->IsString();
            },
            [](Local<Value> value) -> ::Platform::String^ {
              return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));
            },
            [](::Platform::String^ val) -> Local<Value> {
              return NodeRT::Utils::NewString(val->Data());
            },
            [](Local<Value> value) -> bool {
              return value->IsString();
            },
            [](Local<Value> value) -> ::Platform::String^ {
              return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));
            }
          ));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::UI::Notifications::NotificationBinding^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapNotificationBinding(::Windows::UI::Notifications::NotificationBinding^ wintRtInstance);
    friend ::Windows::UI::Notifications::NotificationBinding^ UnwrapNotificationBinding(Local<Value> value);
  };
  Persistent<FunctionTemplate> NotificationBinding::s_constructorTemplate;

  v8::Local<v8::Value> WrapNotificationBinding(::Windows::UI::Notifications::NotificationBinding^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(NotificationBinding::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::Notifications::NotificationBinding^ UnwrapNotificationBinding(Local<Value> value)
  {
     return NotificationBinding::Unwrap<NotificationBinding>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitNotificationBinding(Local<Object> exports)
  {
    NotificationBinding::Init(exports);
  }

  class IAdaptiveNotificationContent : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("IAdaptiveNotificationContent").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("hints").ToLocalChecked(), HintsGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("kind").ToLocalChecked(), KindGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();


      Nan::Set(exports, Nan::New<String>("IAdaptiveNotificationContent").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    IAdaptiveNotificationContent(::Windows::UI::Notifications::IAdaptiveNotificationContent^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Value> res = Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::UI::Notifications::IAdaptiveNotificationContent^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::IAdaptiveNotificationContent^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::Notifications::IAdaptiveNotificationContent^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      IAdaptiveNotificationContent *wrapperInstance = new IAdaptiveNotificationContent(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  



    static void HintsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::IAdaptiveNotificationContent^>(info.This()))
      {
        return;
      }

      IAdaptiveNotificationContent *wrapper = IAdaptiveNotificationContent::Unwrap<IAdaptiveNotificationContent>(info.This());

      try 
      {
        ::Windows::Foundation::Collections::IMap<::Platform::String^, ::Platform::String^>^ result = wrapper->_instance->Hints;
        info.GetReturnValue().Set(NodeRT::Collections::MapWrapper<::Platform::String^,::Platform::String^>::CreateMapWrapper(result, 
            [](::Platform::String^ val) -> Local<Value> {
              return NodeRT::Utils::NewString(val->Data());
            },
            [](Local<Value> value) -> bool {
              return value->IsString();
            },
            [](Local<Value> value) -> ::Platform::String^ {
              return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));
            },
            [](::Platform::String^ val) -> Local<Value> {
              return NodeRT::Utils::NewString(val->Data());
            },
            [](Local<Value> value) -> bool {
              return value->IsString();
            },
            [](Local<Value> value) -> ::Platform::String^ {
              return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));
            }
          ));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void KindGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::IAdaptiveNotificationContent^>(info.This()))
      {
        return;
      }

      IAdaptiveNotificationContent *wrapper = IAdaptiveNotificationContent::Unwrap<IAdaptiveNotificationContent>(info.This());

      try 
      {
        ::Windows::UI::Notifications::AdaptiveNotificationContentKind result = wrapper->_instance->Kind;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::UI::Notifications::IAdaptiveNotificationContent^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapIAdaptiveNotificationContent(::Windows::UI::Notifications::IAdaptiveNotificationContent^ wintRtInstance);
    friend ::Windows::UI::Notifications::IAdaptiveNotificationContent^ UnwrapIAdaptiveNotificationContent(Local<Value> value);
  };
  Persistent<FunctionTemplate> IAdaptiveNotificationContent::s_constructorTemplate;

  v8::Local<v8::Value> WrapIAdaptiveNotificationContent(::Windows::UI::Notifications::IAdaptiveNotificationContent^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IAdaptiveNotificationContent::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::Notifications::IAdaptiveNotificationContent^ UnwrapIAdaptiveNotificationContent(Local<Value> value)
  {
     return IAdaptiveNotificationContent::Unwrap<IAdaptiveNotificationContent>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIAdaptiveNotificationContent(Local<Object> exports)
  {
    IAdaptiveNotificationContent::Init(exports);
  }

  class AdaptiveNotificationText : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("AdaptiveNotificationText").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("hints").ToLocalChecked(), HintsGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("kind").ToLocalChecked(), KindGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("text").ToLocalChecked(), TextGetter, TextSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("language").ToLocalChecked(), LanguageGetter, LanguageSetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();


      Nan::Set(exports, Nan::New<String>("AdaptiveNotificationText").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    AdaptiveNotificationText(::Windows::UI::Notifications::AdaptiveNotificationText^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Value> res = Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::UI::Notifications::AdaptiveNotificationText^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::AdaptiveNotificationText^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::Notifications::AdaptiveNotificationText^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 0)
      {
        try
        {
          winRtInstance = ref new ::Windows::UI::Notifications::AdaptiveNotificationText();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      AdaptiveNotificationText *wrapperInstance = new AdaptiveNotificationText(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  



    static void HintsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::AdaptiveNotificationText^>(info.This()))
      {
        return;
      }

      AdaptiveNotificationText *wrapper = AdaptiveNotificationText::Unwrap<AdaptiveNotificationText>(info.This());

      try 
      {
        ::Windows::Foundation::Collections::IMap<::Platform::String^, ::Platform::String^>^ result = wrapper->_instance->Hints;
        info.GetReturnValue().Set(NodeRT::Collections::MapWrapper<::Platform::String^,::Platform::String^>::CreateMapWrapper(result, 
            [](::Platform::String^ val) -> Local<Value> {
              return NodeRT::Utils::NewString(val->Data());
            },
            [](Local<Value> value) -> bool {
              return value->IsString();
            },
            [](Local<Value> value) -> ::Platform::String^ {
              return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));
            },
            [](::Platform::String^ val) -> Local<Value> {
              return NodeRT::Utils::NewString(val->Data());
            },
            [](Local<Value> value) -> bool {
              return value->IsString();
            },
            [](Local<Value> value) -> ::Platform::String^ {
              return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));
            }
          ));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void KindGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::AdaptiveNotificationText^>(info.This()))
      {
        return;
      }

      AdaptiveNotificationText *wrapper = AdaptiveNotificationText::Unwrap<AdaptiveNotificationText>(info.This());

      try 
      {
        ::Windows::UI::Notifications::AdaptiveNotificationContentKind result = wrapper->_instance->Kind;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void TextGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::AdaptiveNotificationText^>(info.This()))
      {
        return;
      }

      AdaptiveNotificationText *wrapper = AdaptiveNotificationText::Unwrap<AdaptiveNotificationText>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Text;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void TextSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsString())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::AdaptiveNotificationText^>(info.This()))
      {
        return;
      }

      AdaptiveNotificationText *wrapper = AdaptiveNotificationText::Unwrap<AdaptiveNotificationText>(info.This());

      try 
      {
        
        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));

        wrapper->_instance->Text = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void LanguageGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::AdaptiveNotificationText^>(info.This()))
      {
        return;
      }

      AdaptiveNotificationText *wrapper = AdaptiveNotificationText::Unwrap<AdaptiveNotificationText>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Language;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void LanguageSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsString())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::AdaptiveNotificationText^>(info.This()))
      {
        return;
      }

      AdaptiveNotificationText *wrapper = AdaptiveNotificationText::Unwrap<AdaptiveNotificationText>(info.This());

      try 
      {
        
        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));

        wrapper->_instance->Language = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    


  private:
    ::Windows::UI::Notifications::AdaptiveNotificationText^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapAdaptiveNotificationText(::Windows::UI::Notifications::AdaptiveNotificationText^ wintRtInstance);
    friend ::Windows::UI::Notifications::AdaptiveNotificationText^ UnwrapAdaptiveNotificationText(Local<Value> value);
  };
  Persistent<FunctionTemplate> AdaptiveNotificationText::s_constructorTemplate;

  v8::Local<v8::Value> WrapAdaptiveNotificationText(::Windows::UI::Notifications::AdaptiveNotificationText^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(AdaptiveNotificationText::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::Notifications::AdaptiveNotificationText^ UnwrapAdaptiveNotificationText(Local<Value> value)
  {
     return AdaptiveNotificationText::Unwrap<AdaptiveNotificationText>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitAdaptiveNotificationText(Local<Object> exports)
  {
    AdaptiveNotificationText::Init(exports);
  }

  class TileUpdater : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("TileUpdater").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "update", Update);
      Nan::SetPrototypeMethod(localRef, "clear", Clear);
      Nan::SetPrototypeMethod(localRef, "enableNotificationQueue", EnableNotificationQueue);
      Nan::SetPrototypeMethod(localRef, "addToSchedule", AddToSchedule);
      Nan::SetPrototypeMethod(localRef, "removeFromSchedule", RemoveFromSchedule);
      Nan::SetPrototypeMethod(localRef, "getScheduledTileNotifications", GetScheduledTileNotifications);
      Nan::SetPrototypeMethod(localRef, "startPeriodicUpdate", StartPeriodicUpdate);
      Nan::SetPrototypeMethod(localRef, "stopPeriodicUpdate", StopPeriodicUpdate);
      Nan::SetPrototypeMethod(localRef, "startPeriodicUpdateBatch", StartPeriodicUpdateBatch);
      Nan::SetPrototypeMethod(localRef, "enableNotificationQueueForSquare150x150", EnableNotificationQueueForSquare150x150);
      Nan::SetPrototypeMethod(localRef, "enableNotificationQueueForWide310x150", EnableNotificationQueueForWide310x150);
      Nan::SetPrototypeMethod(localRef, "enableNotificationQueueForSquare310x310", EnableNotificationQueueForSquare310x310);
      
                        
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("setting").ToLocalChecked(), SettingGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();


      Nan::Set(exports, Nan::New<String>("TileUpdater").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    TileUpdater(::Windows::UI::Notifications::TileUpdater^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Value> res = Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::UI::Notifications::TileUpdater^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::TileUpdater^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::Notifications::TileUpdater^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      TileUpdater *wrapperInstance = new TileUpdater(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  
    static void Update(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::TileUpdater^>(info.This()))
      {
        return;
      }

      TileUpdater *wrapper = TileUpdater::Unwrap<TileUpdater>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::TileNotification^>(info[0]))
      {
        try
        {
          ::Windows::UI::Notifications::TileNotification^ arg0 = UnwrapTileNotification(info[0]);
          
          wrapper->_instance->Update(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Clear(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::TileUpdater^>(info.This()))
      {
        return;
      }

      TileUpdater *wrapper = TileUpdater::Unwrap<TileUpdater>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Clear();
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void EnableNotificationQueue(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::TileUpdater^>(info.This()))
      {
        return;
      }

      TileUpdater *wrapper = TileUpdater::Unwrap<TileUpdater>(info.This());

      if (info.Length() == 1
        && info[0]->IsBoolean())
      {
        try
        {
          bool arg0 = Nan::To<bool>(info[0]).FromMaybe(false);
          
          wrapper->_instance->EnableNotificationQueue(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void AddToSchedule(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::TileUpdater^>(info.This()))
      {
        return;
      }

      TileUpdater *wrapper = TileUpdater::Unwrap<TileUpdater>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ScheduledTileNotification^>(info[0]))
      {
        try
        {
          ::Windows::UI::Notifications::ScheduledTileNotification^ arg0 = UnwrapScheduledTileNotification(info[0]);
          
          wrapper->_instance->AddToSchedule(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void RemoveFromSchedule(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::TileUpdater^>(info.This()))
      {
        return;
      }

      TileUpdater *wrapper = TileUpdater::Unwrap<TileUpdater>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ScheduledTileNotification^>(info[0]))
      {
        try
        {
          ::Windows::UI::Notifications::ScheduledTileNotification^ arg0 = UnwrapScheduledTileNotification(info[0]);
          
          wrapper->_instance->RemoveFromSchedule(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetScheduledTileNotifications(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::TileUpdater^>(info.This()))
      {
        return;
      }

      TileUpdater *wrapper = TileUpdater::Unwrap<TileUpdater>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Collections::IVectorView<::Windows::UI::Notifications::ScheduledTileNotification^>^ result;
          result = wrapper->_instance->GetScheduledTileNotifications();
          info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::UI::Notifications::ScheduledTileNotification^>::CreateVectorViewWrapper(result, 
            [](::Windows::UI::Notifications::ScheduledTileNotification^ val) -> Local<Value> {
              return WrapScheduledTileNotification(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ScheduledTileNotification^>(value);
            },
            [](Local<Value> value) -> ::Windows::UI::Notifications::ScheduledTileNotification^ {
              return UnwrapScheduledTileNotification(value);
            }
          ));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void StartPeriodicUpdate(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::TileUpdater^>(info.This()))
      {
        return;
      }

      TileUpdater *wrapper = TileUpdater::Unwrap<TileUpdater>(info.This());

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info[0])
        && info[1]->IsInt32())
      {
        try
        {
          ::Windows::Foundation::Uri^ arg0 = dynamic_cast<::Windows::Foundation::Uri^>(NodeRT::Utils::GetObjectInstance(info[0]));
          ::Windows::UI::Notifications::PeriodicUpdateRecurrence arg1 = static_cast<::Windows::UI::Notifications::PeriodicUpdateRecurrence>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          wrapper->_instance->StartPeriodicUpdate(arg0, arg1);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info[0])
        && info[1]->IsDate()
        && info[2]->IsInt32())
      {
        try
        {
          ::Windows::Foundation::Uri^ arg0 = dynamic_cast<::Windows::Foundation::Uri^>(NodeRT::Utils::GetObjectInstance(info[0]));
          ::Windows::Foundation::DateTime arg1 = NodeRT::Utils::DateTimeFromJSDate(info[1]);
          ::Windows::UI::Notifications::PeriodicUpdateRecurrence arg2 = static_cast<::Windows::UI::Notifications::PeriodicUpdateRecurrence>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          
          wrapper->_instance->StartPeriodicUpdate(arg0, arg1, arg2);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void StopPeriodicUpdate(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::TileUpdater^>(info.This()))
      {
        return;
      }

      TileUpdater *wrapper = TileUpdater::Unwrap<TileUpdater>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->StopPeriodicUpdate();
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void StartPeriodicUpdateBatch(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::TileUpdater^>(info.This()))
      {
        return;
      }

      TileUpdater *wrapper = TileUpdater::Unwrap<TileUpdater>(info.This());

      if (info.Length() == 2
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Windows::Foundation::Uri^>^>(info[0]) || info[0]->IsArray())
        && info[1]->IsInt32())
      {
        try
        {
          ::Windows::Foundation::Collections::IIterable<::Windows::Foundation::Uri^>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Windows::Foundation::Uri^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Windows::Foundation::Uri^>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(value);
                 },
                 [](Local<Value> value) -> ::Windows::Foundation::Uri^ {
                   return dynamic_cast<::Windows::Foundation::Uri^>(NodeRT::Utils::GetObjectInstance(value));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Windows::Foundation::Uri^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          ::Windows::UI::Notifications::PeriodicUpdateRecurrence arg1 = static_cast<::Windows::UI::Notifications::PeriodicUpdateRecurrence>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          wrapper->_instance->StartPeriodicUpdateBatch(arg0, arg1);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Windows::Foundation::Uri^>^>(info[0]) || info[0]->IsArray())
        && info[1]->IsDate()
        && info[2]->IsInt32())
      {
        try
        {
          ::Windows::Foundation::Collections::IIterable<::Windows::Foundation::Uri^>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Windows::Foundation::Uri^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Windows::Foundation::Uri^>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(value);
                 },
                 [](Local<Value> value) -> ::Windows::Foundation::Uri^ {
                   return dynamic_cast<::Windows::Foundation::Uri^>(NodeRT::Utils::GetObjectInstance(value));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Windows::Foundation::Uri^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          ::Windows::Foundation::DateTime arg1 = NodeRT::Utils::DateTimeFromJSDate(info[1]);
          ::Windows::UI::Notifications::PeriodicUpdateRecurrence arg2 = static_cast<::Windows::UI::Notifications::PeriodicUpdateRecurrence>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          
          wrapper->_instance->StartPeriodicUpdateBatch(arg0, arg1, arg2);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void EnableNotificationQueueForSquare150x150(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::TileUpdater^>(info.This()))
      {
        return;
      }

      TileUpdater *wrapper = TileUpdater::Unwrap<TileUpdater>(info.This());

      if (info.Length() == 1
        && info[0]->IsBoolean())
      {
        try
        {
          bool arg0 = Nan::To<bool>(info[0]).FromMaybe(false);
          
          wrapper->_instance->EnableNotificationQueueForSquare150x150(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void EnableNotificationQueueForWide310x150(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::TileUpdater^>(info.This()))
      {
        return;
      }

      TileUpdater *wrapper = TileUpdater::Unwrap<TileUpdater>(info.This());

      if (info.Length() == 1
        && info[0]->IsBoolean())
      {
        try
        {
          bool arg0 = Nan::To<bool>(info[0]).FromMaybe(false);
          
          wrapper->_instance->EnableNotificationQueueForWide310x150(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void EnableNotificationQueueForSquare310x310(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::TileUpdater^>(info.This()))
      {
        return;
      }

      TileUpdater *wrapper = TileUpdater::Unwrap<TileUpdater>(info.This());

      if (info.Length() == 1
        && info[0]->IsBoolean())
      {
        try
        {
          bool arg0 = Nan::To<bool>(info[0]).FromMaybe(false);
          
          wrapper->_instance->EnableNotificationQueueForSquare310x310(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void SettingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::TileUpdater^>(info.This()))
      {
        return;
      }

      TileUpdater *wrapper = TileUpdater::Unwrap<TileUpdater>(info.This());

      try 
      {
        ::Windows::UI::Notifications::NotificationSetting result = wrapper->_instance->Setting;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::UI::Notifications::TileUpdater^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapTileUpdater(::Windows::UI::Notifications::TileUpdater^ wintRtInstance);
    friend ::Windows::UI::Notifications::TileUpdater^ UnwrapTileUpdater(Local<Value> value);
  };
  Persistent<FunctionTemplate> TileUpdater::s_constructorTemplate;

  v8::Local<v8::Value> WrapTileUpdater(::Windows::UI::Notifications::TileUpdater^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(TileUpdater::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::Notifications::TileUpdater^ UnwrapTileUpdater(Local<Value> value)
  {
     return TileUpdater::Unwrap<TileUpdater>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitTileUpdater(Local<Object> exports)
  {
    TileUpdater::Init(exports);
  }

  class TileUpdateManagerForUser : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("TileUpdateManagerForUser").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "createTileUpdaterForApplicationForUser", CreateTileUpdaterForApplicationForUser);
      Nan::SetPrototypeMethod(localRef, "createTileUpdaterForApplication", CreateTileUpdaterForApplication);
      Nan::SetPrototypeMethod(localRef, "createTileUpdaterForSecondaryTile", CreateTileUpdaterForSecondaryTile);
      
                        
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("user").ToLocalChecked(), UserGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();


      Nan::Set(exports, Nan::New<String>("TileUpdateManagerForUser").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    TileUpdateManagerForUser(::Windows::UI::Notifications::TileUpdateManagerForUser^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Value> res = Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::UI::Notifications::TileUpdateManagerForUser^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::TileUpdateManagerForUser^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::Notifications::TileUpdateManagerForUser^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      TileUpdateManagerForUser *wrapperInstance = new TileUpdateManagerForUser(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  
    static void CreateTileUpdaterForApplicationForUser(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::TileUpdateManagerForUser^>(info.This()))
      {
        return;
      }

      TileUpdateManagerForUser *wrapper = TileUpdateManagerForUser::Unwrap<TileUpdateManagerForUser>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::UI::Notifications::TileUpdater^ result;
          result = wrapper->_instance->CreateTileUpdaterForApplicationForUser();
          info.GetReturnValue().Set(WrapTileUpdater(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CreateTileUpdaterForApplication(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::TileUpdateManagerForUser^>(info.This()))
      {
        return;
      }

      TileUpdateManagerForUser *wrapper = TileUpdateManagerForUser::Unwrap<TileUpdateManagerForUser>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          ::Windows::UI::Notifications::TileUpdater^ result;
          result = wrapper->_instance->CreateTileUpdaterForApplication(arg0);
          info.GetReturnValue().Set(WrapTileUpdater(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CreateTileUpdaterForSecondaryTile(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::TileUpdateManagerForUser^>(info.This()))
      {
        return;
      }

      TileUpdateManagerForUser *wrapper = TileUpdateManagerForUser::Unwrap<TileUpdateManagerForUser>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          ::Windows::UI::Notifications::TileUpdater^ result;
          result = wrapper->_instance->CreateTileUpdaterForSecondaryTile(arg0);
          info.GetReturnValue().Set(WrapTileUpdater(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void UserGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::TileUpdateManagerForUser^>(info.This()))
      {
        return;
      }

      TileUpdateManagerForUser *wrapper = TileUpdateManagerForUser::Unwrap<TileUpdateManagerForUser>(info.This());

      try 
      {
        ::Windows::System::User^ result = wrapper->_instance->User;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.System", "User", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::UI::Notifications::TileUpdateManagerForUser^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapTileUpdateManagerForUser(::Windows::UI::Notifications::TileUpdateManagerForUser^ wintRtInstance);
    friend ::Windows::UI::Notifications::TileUpdateManagerForUser^ UnwrapTileUpdateManagerForUser(Local<Value> value);
  };
  Persistent<FunctionTemplate> TileUpdateManagerForUser::s_constructorTemplate;

  v8::Local<v8::Value> WrapTileUpdateManagerForUser(::Windows::UI::Notifications::TileUpdateManagerForUser^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(TileUpdateManagerForUser::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::Notifications::TileUpdateManagerForUser^ UnwrapTileUpdateManagerForUser(Local<Value> value)
  {
     return TileUpdateManagerForUser::Unwrap<TileUpdateManagerForUser>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitTileUpdateManagerForUser(Local<Object> exports)
  {
    TileUpdateManagerForUser::Init(exports);
  }

  class TileNotification : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("TileNotification").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("tag").ToLocalChecked(), TagGetter, TagSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("expirationTime").ToLocalChecked(), ExpirationTimeGetter, ExpirationTimeSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("content").ToLocalChecked(), ContentGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();


      Nan::Set(exports, Nan::New<String>("TileNotification").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    TileNotification(::Windows::UI::Notifications::TileNotification^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Value> res = Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::UI::Notifications::TileNotification^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::TileNotification^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::Notifications::TileNotification^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info[0]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::XmlDocument^ arg0 = dynamic_cast<::Windows::Data::Xml::Dom::XmlDocument^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          winRtInstance = ref new ::Windows::UI::Notifications::TileNotification(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      TileNotification *wrapperInstance = new TileNotification(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  



    static void TagGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::TileNotification^>(info.This()))
      {
        return;
      }

      TileNotification *wrapper = TileNotification::Unwrap<TileNotification>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Tag;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void TagSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsString())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::TileNotification^>(info.This()))
      {
        return;
      }

      TileNotification *wrapper = TileNotification::Unwrap<TileNotification>(info.This());

      try 
      {
        
        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));

        wrapper->_instance->Tag = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void ExpirationTimeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::TileNotification^>(info.This()))
      {
        return;
      }

      TileNotification *wrapper = TileNotification::Unwrap<TileNotification>(info.This());

      try 
      {
        ::Platform::IBox<::Windows::Foundation::DateTime>^ result = wrapper->_instance->ExpirationTime;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(NodeRT::Utils::DateTimeToJS(result->Value)) : Undefined());
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ExpirationTimeSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsDate())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::TileNotification^>(info.This()))
      {
        return;
      }

      TileNotification *wrapper = TileNotification::Unwrap<TileNotification>(info.This());

      try 
      {
        
        ::Platform::IBox<::Windows::Foundation::DateTime>^ winRtValue = ref new ::Platform::Box<::Windows::Foundation::DateTime>(NodeRT::Utils::DateTimeFromJSDate(value));

        wrapper->_instance->ExpirationTime = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void ContentGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::TileNotification^>(info.This()))
      {
        return;
      }

      TileNotification *wrapper = TileNotification::Unwrap<TileNotification>(info.This());

      try 
      {
        ::Windows::Data::Xml::Dom::XmlDocument^ result = wrapper->_instance->Content;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Data.Xml.Dom", "XmlDocument", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::UI::Notifications::TileNotification^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapTileNotification(::Windows::UI::Notifications::TileNotification^ wintRtInstance);
    friend ::Windows::UI::Notifications::TileNotification^ UnwrapTileNotification(Local<Value> value);
  };
  Persistent<FunctionTemplate> TileNotification::s_constructorTemplate;

  v8::Local<v8::Value> WrapTileNotification(::Windows::UI::Notifications::TileNotification^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(TileNotification::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::Notifications::TileNotification^ UnwrapTileNotification(Local<Value> value)
  {
     return TileNotification::Unwrap<TileNotification>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitTileNotification(Local<Object> exports)
  {
    TileNotification::Init(exports);
  }

  class ScheduledTileNotification : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("ScheduledTileNotification").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("tag").ToLocalChecked(), TagGetter, TagSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("id").ToLocalChecked(), IdGetter, IdSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("expirationTime").ToLocalChecked(), ExpirationTimeGetter, ExpirationTimeSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("content").ToLocalChecked(), ContentGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("deliveryTime").ToLocalChecked(), DeliveryTimeGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();


      Nan::Set(exports, Nan::New<String>("ScheduledTileNotification").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    ScheduledTileNotification(::Windows::UI::Notifications::ScheduledTileNotification^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Value> res = Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::UI::Notifications::ScheduledTileNotification^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ScheduledTileNotification^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::Notifications::ScheduledTileNotification^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info[0])
        && info[1]->IsDate())
      {
        try
        {
          ::Windows::Data::Xml::Dom::XmlDocument^ arg0 = dynamic_cast<::Windows::Data::Xml::Dom::XmlDocument^>(NodeRT::Utils::GetObjectInstance(info[0]));
          ::Windows::Foundation::DateTime arg1 = NodeRT::Utils::DateTimeFromJSDate(info[1]);
          
          winRtInstance = ref new ::Windows::UI::Notifications::ScheduledTileNotification(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      ScheduledTileNotification *wrapperInstance = new ScheduledTileNotification(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  



    static void TagGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ScheduledTileNotification^>(info.This()))
      {
        return;
      }

      ScheduledTileNotification *wrapper = ScheduledTileNotification::Unwrap<ScheduledTileNotification>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Tag;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void TagSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsString())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ScheduledTileNotification^>(info.This()))
      {
        return;
      }

      ScheduledTileNotification *wrapper = ScheduledTileNotification::Unwrap<ScheduledTileNotification>(info.This());

      try 
      {
        
        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));

        wrapper->_instance->Tag = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void IdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ScheduledTileNotification^>(info.This()))
      {
        return;
      }

      ScheduledTileNotification *wrapper = ScheduledTileNotification::Unwrap<ScheduledTileNotification>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Id;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IdSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsString())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ScheduledTileNotification^>(info.This()))
      {
        return;
      }

      ScheduledTileNotification *wrapper = ScheduledTileNotification::Unwrap<ScheduledTileNotification>(info.This());

      try 
      {
        
        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));

        wrapper->_instance->Id = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void ExpirationTimeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ScheduledTileNotification^>(info.This()))
      {
        return;
      }

      ScheduledTileNotification *wrapper = ScheduledTileNotification::Unwrap<ScheduledTileNotification>(info.This());

      try 
      {
        ::Platform::IBox<::Windows::Foundation::DateTime>^ result = wrapper->_instance->ExpirationTime;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(NodeRT::Utils::DateTimeToJS(result->Value)) : Undefined());
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ExpirationTimeSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsDate())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ScheduledTileNotification^>(info.This()))
      {
        return;
      }

      ScheduledTileNotification *wrapper = ScheduledTileNotification::Unwrap<ScheduledTileNotification>(info.This());

      try 
      {
        
        ::Platform::IBox<::Windows::Foundation::DateTime>^ winRtValue = ref new ::Platform::Box<::Windows::Foundation::DateTime>(NodeRT::Utils::DateTimeFromJSDate(value));

        wrapper->_instance->ExpirationTime = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void ContentGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ScheduledTileNotification^>(info.This()))
      {
        return;
      }

      ScheduledTileNotification *wrapper = ScheduledTileNotification::Unwrap<ScheduledTileNotification>(info.This());

      try 
      {
        ::Windows::Data::Xml::Dom::XmlDocument^ result = wrapper->_instance->Content;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Data.Xml.Dom", "XmlDocument", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void DeliveryTimeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ScheduledTileNotification^>(info.This()))
      {
        return;
      }

      ScheduledTileNotification *wrapper = ScheduledTileNotification::Unwrap<ScheduledTileNotification>(info.This());

      try 
      {
        ::Windows::Foundation::DateTime result = wrapper->_instance->DeliveryTime;
        info.GetReturnValue().Set(NodeRT::Utils::DateTimeToJS(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::UI::Notifications::ScheduledTileNotification^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapScheduledTileNotification(::Windows::UI::Notifications::ScheduledTileNotification^ wintRtInstance);
    friend ::Windows::UI::Notifications::ScheduledTileNotification^ UnwrapScheduledTileNotification(Local<Value> value);
  };
  Persistent<FunctionTemplate> ScheduledTileNotification::s_constructorTemplate;

  v8::Local<v8::Value> WrapScheduledTileNotification(::Windows::UI::Notifications::ScheduledTileNotification^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(ScheduledTileNotification::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::Notifications::ScheduledTileNotification^ UnwrapScheduledTileNotification(Local<Value> value)
  {
     return ScheduledTileNotification::Unwrap<ScheduledTileNotification>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitScheduledTileNotification(Local<Object> exports)
  {
    ScheduledTileNotification::Init(exports);
  }

  class TileFlyoutUpdater : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("TileFlyoutUpdater").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "update", Update);
      Nan::SetPrototypeMethod(localRef, "clear", Clear);
      Nan::SetPrototypeMethod(localRef, "startPeriodicUpdate", StartPeriodicUpdate);
      Nan::SetPrototypeMethod(localRef, "stopPeriodicUpdate", StopPeriodicUpdate);
      
                        
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("setting").ToLocalChecked(), SettingGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();


      Nan::Set(exports, Nan::New<String>("TileFlyoutUpdater").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    TileFlyoutUpdater(::Windows::UI::Notifications::TileFlyoutUpdater^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Value> res = Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::UI::Notifications::TileFlyoutUpdater^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::TileFlyoutUpdater^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::Notifications::TileFlyoutUpdater^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      TileFlyoutUpdater *wrapperInstance = new TileFlyoutUpdater(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  
    static void Update(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::TileFlyoutUpdater^>(info.This()))
      {
        return;
      }

      TileFlyoutUpdater *wrapper = TileFlyoutUpdater::Unwrap<TileFlyoutUpdater>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::TileFlyoutNotification^>(info[0]))
      {
        try
        {
          ::Windows::UI::Notifications::TileFlyoutNotification^ arg0 = UnwrapTileFlyoutNotification(info[0]);
          
          wrapper->_instance->Update(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Clear(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::TileFlyoutUpdater^>(info.This()))
      {
        return;
      }

      TileFlyoutUpdater *wrapper = TileFlyoutUpdater::Unwrap<TileFlyoutUpdater>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Clear();
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void StartPeriodicUpdate(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::TileFlyoutUpdater^>(info.This()))
      {
        return;
      }

      TileFlyoutUpdater *wrapper = TileFlyoutUpdater::Unwrap<TileFlyoutUpdater>(info.This());

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info[0])
        && info[1]->IsInt32())
      {
        try
        {
          ::Windows::Foundation::Uri^ arg0 = dynamic_cast<::Windows::Foundation::Uri^>(NodeRT::Utils::GetObjectInstance(info[0]));
          ::Windows::UI::Notifications::PeriodicUpdateRecurrence arg1 = static_cast<::Windows::UI::Notifications::PeriodicUpdateRecurrence>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          wrapper->_instance->StartPeriodicUpdate(arg0, arg1);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info[0])
        && info[1]->IsDate()
        && info[2]->IsInt32())
      {
        try
        {
          ::Windows::Foundation::Uri^ arg0 = dynamic_cast<::Windows::Foundation::Uri^>(NodeRT::Utils::GetObjectInstance(info[0]));
          ::Windows::Foundation::DateTime arg1 = NodeRT::Utils::DateTimeFromJSDate(info[1]);
          ::Windows::UI::Notifications::PeriodicUpdateRecurrence arg2 = static_cast<::Windows::UI::Notifications::PeriodicUpdateRecurrence>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          
          wrapper->_instance->StartPeriodicUpdate(arg0, arg1, arg2);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void StopPeriodicUpdate(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::TileFlyoutUpdater^>(info.This()))
      {
        return;
      }

      TileFlyoutUpdater *wrapper = TileFlyoutUpdater::Unwrap<TileFlyoutUpdater>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->StopPeriodicUpdate();
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void SettingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::TileFlyoutUpdater^>(info.This()))
      {
        return;
      }

      TileFlyoutUpdater *wrapper = TileFlyoutUpdater::Unwrap<TileFlyoutUpdater>(info.This());

      try 
      {
        ::Windows::UI::Notifications::NotificationSetting result = wrapper->_instance->Setting;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::UI::Notifications::TileFlyoutUpdater^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapTileFlyoutUpdater(::Windows::UI::Notifications::TileFlyoutUpdater^ wintRtInstance);
    friend ::Windows::UI::Notifications::TileFlyoutUpdater^ UnwrapTileFlyoutUpdater(Local<Value> value);
  };
  Persistent<FunctionTemplate> TileFlyoutUpdater::s_constructorTemplate;

  v8::Local<v8::Value> WrapTileFlyoutUpdater(::Windows::UI::Notifications::TileFlyoutUpdater^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(TileFlyoutUpdater::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::Notifications::TileFlyoutUpdater^ UnwrapTileFlyoutUpdater(Local<Value> value)
  {
     return TileFlyoutUpdater::Unwrap<TileFlyoutUpdater>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitTileFlyoutUpdater(Local<Object> exports)
  {
    TileFlyoutUpdater::Init(exports);
  }

  class TileFlyoutNotification : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("TileFlyoutNotification").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("expirationTime").ToLocalChecked(), ExpirationTimeGetter, ExpirationTimeSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("content").ToLocalChecked(), ContentGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();


      Nan::Set(exports, Nan::New<String>("TileFlyoutNotification").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    TileFlyoutNotification(::Windows::UI::Notifications::TileFlyoutNotification^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Value> res = Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::UI::Notifications::TileFlyoutNotification^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::TileFlyoutNotification^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::Notifications::TileFlyoutNotification^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info[0]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::XmlDocument^ arg0 = dynamic_cast<::Windows::Data::Xml::Dom::XmlDocument^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          winRtInstance = ref new ::Windows::UI::Notifications::TileFlyoutNotification(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      TileFlyoutNotification *wrapperInstance = new TileFlyoutNotification(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  



    static void ExpirationTimeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::TileFlyoutNotification^>(info.This()))
      {
        return;
      }

      TileFlyoutNotification *wrapper = TileFlyoutNotification::Unwrap<TileFlyoutNotification>(info.This());

      try 
      {
        ::Platform::IBox<::Windows::Foundation::DateTime>^ result = wrapper->_instance->ExpirationTime;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(NodeRT::Utils::DateTimeToJS(result->Value)) : Undefined());
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ExpirationTimeSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsDate())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::TileFlyoutNotification^>(info.This()))
      {
        return;
      }

      TileFlyoutNotification *wrapper = TileFlyoutNotification::Unwrap<TileFlyoutNotification>(info.This());

      try 
      {
        
        ::Platform::IBox<::Windows::Foundation::DateTime>^ winRtValue = ref new ::Platform::Box<::Windows::Foundation::DateTime>(NodeRT::Utils::DateTimeFromJSDate(value));

        wrapper->_instance->ExpirationTime = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void ContentGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::TileFlyoutNotification^>(info.This()))
      {
        return;
      }

      TileFlyoutNotification *wrapper = TileFlyoutNotification::Unwrap<TileFlyoutNotification>(info.This());

      try 
      {
        ::Windows::Data::Xml::Dom::XmlDocument^ result = wrapper->_instance->Content;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Data.Xml.Dom", "XmlDocument", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::UI::Notifications::TileFlyoutNotification^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapTileFlyoutNotification(::Windows::UI::Notifications::TileFlyoutNotification^ wintRtInstance);
    friend ::Windows::UI::Notifications::TileFlyoutNotification^ UnwrapTileFlyoutNotification(Local<Value> value);
  };
  Persistent<FunctionTemplate> TileFlyoutNotification::s_constructorTemplate;

  v8::Local<v8::Value> WrapTileFlyoutNotification(::Windows::UI::Notifications::TileFlyoutNotification^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(TileFlyoutNotification::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::Notifications::TileFlyoutNotification^ UnwrapTileFlyoutNotification(Local<Value> value)
  {
     return TileFlyoutNotification::Unwrap<TileFlyoutNotification>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitTileFlyoutNotification(Local<Object> exports)
  {
    TileFlyoutNotification::Init(exports);
  }

  class BadgeUpdater : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("BadgeUpdater").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "update", Update);
      Nan::SetPrototypeMethod(localRef, "clear", Clear);
      Nan::SetPrototypeMethod(localRef, "startPeriodicUpdate", StartPeriodicUpdate);
      Nan::SetPrototypeMethod(localRef, "stopPeriodicUpdate", StopPeriodicUpdate);
      
                        
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();


      Nan::Set(exports, Nan::New<String>("BadgeUpdater").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    BadgeUpdater(::Windows::UI::Notifications::BadgeUpdater^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Value> res = Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::UI::Notifications::BadgeUpdater^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::BadgeUpdater^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::Notifications::BadgeUpdater^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      BadgeUpdater *wrapperInstance = new BadgeUpdater(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  
    static void Update(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::BadgeUpdater^>(info.This()))
      {
        return;
      }

      BadgeUpdater *wrapper = BadgeUpdater::Unwrap<BadgeUpdater>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::BadgeNotification^>(info[0]))
      {
        try
        {
          ::Windows::UI::Notifications::BadgeNotification^ arg0 = UnwrapBadgeNotification(info[0]);
          
          wrapper->_instance->Update(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Clear(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::BadgeUpdater^>(info.This()))
      {
        return;
      }

      BadgeUpdater *wrapper = BadgeUpdater::Unwrap<BadgeUpdater>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Clear();
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void StartPeriodicUpdate(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::BadgeUpdater^>(info.This()))
      {
        return;
      }

      BadgeUpdater *wrapper = BadgeUpdater::Unwrap<BadgeUpdater>(info.This());

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info[0])
        && info[1]->IsInt32())
      {
        try
        {
          ::Windows::Foundation::Uri^ arg0 = dynamic_cast<::Windows::Foundation::Uri^>(NodeRT::Utils::GetObjectInstance(info[0]));
          ::Windows::UI::Notifications::PeriodicUpdateRecurrence arg1 = static_cast<::Windows::UI::Notifications::PeriodicUpdateRecurrence>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          wrapper->_instance->StartPeriodicUpdate(arg0, arg1);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info[0])
        && info[1]->IsDate()
        && info[2]->IsInt32())
      {
        try
        {
          ::Windows::Foundation::Uri^ arg0 = dynamic_cast<::Windows::Foundation::Uri^>(NodeRT::Utils::GetObjectInstance(info[0]));
          ::Windows::Foundation::DateTime arg1 = NodeRT::Utils::DateTimeFromJSDate(info[1]);
          ::Windows::UI::Notifications::PeriodicUpdateRecurrence arg2 = static_cast<::Windows::UI::Notifications::PeriodicUpdateRecurrence>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          
          wrapper->_instance->StartPeriodicUpdate(arg0, arg1, arg2);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void StopPeriodicUpdate(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::BadgeUpdater^>(info.This()))
      {
        return;
      }

      BadgeUpdater *wrapper = BadgeUpdater::Unwrap<BadgeUpdater>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->StopPeriodicUpdate();
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }





  private:
    ::Windows::UI::Notifications::BadgeUpdater^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapBadgeUpdater(::Windows::UI::Notifications::BadgeUpdater^ wintRtInstance);
    friend ::Windows::UI::Notifications::BadgeUpdater^ UnwrapBadgeUpdater(Local<Value> value);
  };
  Persistent<FunctionTemplate> BadgeUpdater::s_constructorTemplate;

  v8::Local<v8::Value> WrapBadgeUpdater(::Windows::UI::Notifications::BadgeUpdater^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(BadgeUpdater::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::Notifications::BadgeUpdater^ UnwrapBadgeUpdater(Local<Value> value)
  {
     return BadgeUpdater::Unwrap<BadgeUpdater>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitBadgeUpdater(Local<Object> exports)
  {
    BadgeUpdater::Init(exports);
  }

  class BadgeUpdateManagerForUser : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("BadgeUpdateManagerForUser").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "createBadgeUpdaterForApplication", CreateBadgeUpdaterForApplication);
      Nan::SetPrototypeMethod(localRef, "createBadgeUpdaterForSecondaryTile", CreateBadgeUpdaterForSecondaryTile);
      
                        
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("user").ToLocalChecked(), UserGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();


      Nan::Set(exports, Nan::New<String>("BadgeUpdateManagerForUser").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    BadgeUpdateManagerForUser(::Windows::UI::Notifications::BadgeUpdateManagerForUser^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Value> res = Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::UI::Notifications::BadgeUpdateManagerForUser^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::BadgeUpdateManagerForUser^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::Notifications::BadgeUpdateManagerForUser^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      BadgeUpdateManagerForUser *wrapperInstance = new BadgeUpdateManagerForUser(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  
    static void CreateBadgeUpdaterForApplication(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::BadgeUpdateManagerForUser^>(info.This()))
      {
        return;
      }

      BadgeUpdateManagerForUser *wrapper = BadgeUpdateManagerForUser::Unwrap<BadgeUpdateManagerForUser>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::UI::Notifications::BadgeUpdater^ result;
          result = wrapper->_instance->CreateBadgeUpdaterForApplication();
          info.GetReturnValue().Set(WrapBadgeUpdater(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          ::Windows::UI::Notifications::BadgeUpdater^ result;
          result = wrapper->_instance->CreateBadgeUpdaterForApplication(arg0);
          info.GetReturnValue().Set(WrapBadgeUpdater(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CreateBadgeUpdaterForSecondaryTile(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::BadgeUpdateManagerForUser^>(info.This()))
      {
        return;
      }

      BadgeUpdateManagerForUser *wrapper = BadgeUpdateManagerForUser::Unwrap<BadgeUpdateManagerForUser>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          ::Windows::UI::Notifications::BadgeUpdater^ result;
          result = wrapper->_instance->CreateBadgeUpdaterForSecondaryTile(arg0);
          info.GetReturnValue().Set(WrapBadgeUpdater(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void UserGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::BadgeUpdateManagerForUser^>(info.This()))
      {
        return;
      }

      BadgeUpdateManagerForUser *wrapper = BadgeUpdateManagerForUser::Unwrap<BadgeUpdateManagerForUser>(info.This());

      try 
      {
        ::Windows::System::User^ result = wrapper->_instance->User;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.System", "User", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::UI::Notifications::BadgeUpdateManagerForUser^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapBadgeUpdateManagerForUser(::Windows::UI::Notifications::BadgeUpdateManagerForUser^ wintRtInstance);
    friend ::Windows::UI::Notifications::BadgeUpdateManagerForUser^ UnwrapBadgeUpdateManagerForUser(Local<Value> value);
  };
  Persistent<FunctionTemplate> BadgeUpdateManagerForUser::s_constructorTemplate;

  v8::Local<v8::Value> WrapBadgeUpdateManagerForUser(::Windows::UI::Notifications::BadgeUpdateManagerForUser^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(BadgeUpdateManagerForUser::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::Notifications::BadgeUpdateManagerForUser^ UnwrapBadgeUpdateManagerForUser(Local<Value> value)
  {
     return BadgeUpdateManagerForUser::Unwrap<BadgeUpdateManagerForUser>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitBadgeUpdateManagerForUser(Local<Object> exports)
  {
    BadgeUpdateManagerForUser::Init(exports);
  }

  class BadgeNotification : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("BadgeNotification").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("expirationTime").ToLocalChecked(), ExpirationTimeGetter, ExpirationTimeSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("content").ToLocalChecked(), ContentGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();


      Nan::Set(exports, Nan::New<String>("BadgeNotification").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    BadgeNotification(::Windows::UI::Notifications::BadgeNotification^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Value> res = Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::UI::Notifications::BadgeNotification^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::BadgeNotification^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::Notifications::BadgeNotification^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info[0]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::XmlDocument^ arg0 = dynamic_cast<::Windows::Data::Xml::Dom::XmlDocument^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          winRtInstance = ref new ::Windows::UI::Notifications::BadgeNotification(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      BadgeNotification *wrapperInstance = new BadgeNotification(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  



    static void ExpirationTimeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::BadgeNotification^>(info.This()))
      {
        return;
      }

      BadgeNotification *wrapper = BadgeNotification::Unwrap<BadgeNotification>(info.This());

      try 
      {
        ::Platform::IBox<::Windows::Foundation::DateTime>^ result = wrapper->_instance->ExpirationTime;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(NodeRT::Utils::DateTimeToJS(result->Value)) : Undefined());
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ExpirationTimeSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsDate())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::BadgeNotification^>(info.This()))
      {
        return;
      }

      BadgeNotification *wrapper = BadgeNotification::Unwrap<BadgeNotification>(info.This());

      try 
      {
        
        ::Platform::IBox<::Windows::Foundation::DateTime>^ winRtValue = ref new ::Platform::Box<::Windows::Foundation::DateTime>(NodeRT::Utils::DateTimeFromJSDate(value));

        wrapper->_instance->ExpirationTime = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void ContentGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::BadgeNotification^>(info.This()))
      {
        return;
      }

      BadgeNotification *wrapper = BadgeNotification::Unwrap<BadgeNotification>(info.This());

      try 
      {
        ::Windows::Data::Xml::Dom::XmlDocument^ result = wrapper->_instance->Content;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Data.Xml.Dom", "XmlDocument", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::UI::Notifications::BadgeNotification^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapBadgeNotification(::Windows::UI::Notifications::BadgeNotification^ wintRtInstance);
    friend ::Windows::UI::Notifications::BadgeNotification^ UnwrapBadgeNotification(Local<Value> value);
  };
  Persistent<FunctionTemplate> BadgeNotification::s_constructorTemplate;

  v8::Local<v8::Value> WrapBadgeNotification(::Windows::UI::Notifications::BadgeNotification^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(BadgeNotification::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::Notifications::BadgeNotification^ UnwrapBadgeNotification(Local<Value> value)
  {
     return BadgeNotification::Unwrap<BadgeNotification>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitBadgeNotification(Local<Object> exports)
  {
    BadgeNotification::Init(exports);
  }

  class ToastNotifier : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("ToastNotifier").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "show", Show);
      Nan::SetPrototypeMethod(localRef, "hide", Hide);
      Nan::SetPrototypeMethod(localRef, "addToSchedule", AddToSchedule);
      Nan::SetPrototypeMethod(localRef, "removeFromSchedule", RemoveFromSchedule);
      Nan::SetPrototypeMethod(localRef, "getScheduledToastNotifications", GetScheduledToastNotifications);
      
                        
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("setting").ToLocalChecked(), SettingGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();


      Nan::Set(exports, Nan::New<String>("ToastNotifier").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    ToastNotifier(::Windows::UI::Notifications::ToastNotifier^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Value> res = Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::UI::Notifications::ToastNotifier^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotifier^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::Notifications::ToastNotifier^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      ToastNotifier *wrapperInstance = new ToastNotifier(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  
    static void Show(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotifier^>(info.This()))
      {
        return;
      }

      ToastNotifier *wrapper = ToastNotifier::Unwrap<ToastNotifier>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotification^>(info[0]))
      {
        try
        {
          ::Windows::UI::Notifications::ToastNotification^ arg0 = UnwrapToastNotification(info[0]);
          
          wrapper->_instance->Show(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Hide(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotifier^>(info.This()))
      {
        return;
      }

      ToastNotifier *wrapper = ToastNotifier::Unwrap<ToastNotifier>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotification^>(info[0]))
      {
        try
        {
          ::Windows::UI::Notifications::ToastNotification^ arg0 = UnwrapToastNotification(info[0]);
          
          wrapper->_instance->Hide(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void AddToSchedule(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotifier^>(info.This()))
      {
        return;
      }

      ToastNotifier *wrapper = ToastNotifier::Unwrap<ToastNotifier>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ScheduledToastNotification^>(info[0]))
      {
        try
        {
          ::Windows::UI::Notifications::ScheduledToastNotification^ arg0 = UnwrapScheduledToastNotification(info[0]);
          
          wrapper->_instance->AddToSchedule(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void RemoveFromSchedule(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotifier^>(info.This()))
      {
        return;
      }

      ToastNotifier *wrapper = ToastNotifier::Unwrap<ToastNotifier>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ScheduledToastNotification^>(info[0]))
      {
        try
        {
          ::Windows::UI::Notifications::ScheduledToastNotification^ arg0 = UnwrapScheduledToastNotification(info[0]);
          
          wrapper->_instance->RemoveFromSchedule(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetScheduledToastNotifications(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotifier^>(info.This()))
      {
        return;
      }

      ToastNotifier *wrapper = ToastNotifier::Unwrap<ToastNotifier>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Collections::IVectorView<::Windows::UI::Notifications::ScheduledToastNotification^>^ result;
          result = wrapper->_instance->GetScheduledToastNotifications();
          info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::UI::Notifications::ScheduledToastNotification^>::CreateVectorViewWrapper(result, 
            [](::Windows::UI::Notifications::ScheduledToastNotification^ val) -> Local<Value> {
              return WrapScheduledToastNotification(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ScheduledToastNotification^>(value);
            },
            [](Local<Value> value) -> ::Windows::UI::Notifications::ScheduledToastNotification^ {
              return UnwrapScheduledToastNotification(value);
            }
          ));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void SettingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotifier^>(info.This()))
      {
        return;
      }

      ToastNotifier *wrapper = ToastNotifier::Unwrap<ToastNotifier>(info.This());

      try 
      {
        ::Windows::UI::Notifications::NotificationSetting result = wrapper->_instance->Setting;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::UI::Notifications::ToastNotifier^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapToastNotifier(::Windows::UI::Notifications::ToastNotifier^ wintRtInstance);
    friend ::Windows::UI::Notifications::ToastNotifier^ UnwrapToastNotifier(Local<Value> value);
  };
  Persistent<FunctionTemplate> ToastNotifier::s_constructorTemplate;

  v8::Local<v8::Value> WrapToastNotifier(::Windows::UI::Notifications::ToastNotifier^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(ToastNotifier::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::Notifications::ToastNotifier^ UnwrapToastNotifier(Local<Value> value)
  {
     return ToastNotifier::Unwrap<ToastNotifier>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitToastNotifier(Local<Object> exports)
  {
    ToastNotifier::Init(exports);
  }

  class ToastNotification : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("ToastNotification").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                        
      Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
      Nan::SetPrototypeMethod(localRef,"on", AddListener);
      Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
      Nan::SetPrototypeMethod(localRef, "off", RemoveListener);
            
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("expirationTime").ToLocalChecked(), ExpirationTimeGetter, ExpirationTimeSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("content").ToLocalChecked(), ContentGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("tag").ToLocalChecked(), TagGetter, TagSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("suppressPopup").ToLocalChecked(), SuppressPopupGetter, SuppressPopupSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("group").ToLocalChecked(), GroupGetter, GroupSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("remoteId").ToLocalChecked(), RemoteIdGetter, RemoteIdSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("notificationMirroring").ToLocalChecked(), NotificationMirroringGetter, NotificationMirroringSetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();


      Nan::Set(exports, Nan::New<String>("ToastNotification").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    ToastNotification(::Windows::UI::Notifications::ToastNotification^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Value> res = Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::UI::Notifications::ToastNotification^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotification^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::Notifications::ToastNotification^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info[0]))
      {
        try
        {
          ::Windows::Data::Xml::Dom::XmlDocument^ arg0 = dynamic_cast<::Windows::Data::Xml::Dom::XmlDocument^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          winRtInstance = ref new ::Windows::UI::Notifications::ToastNotification(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      ToastNotification *wrapperInstance = new ToastNotification(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  



    static void ExpirationTimeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotification^>(info.This()))
      {
        return;
      }

      ToastNotification *wrapper = ToastNotification::Unwrap<ToastNotification>(info.This());

      try 
      {
        ::Platform::IBox<::Windows::Foundation::DateTime>^ result = wrapper->_instance->ExpirationTime;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(NodeRT::Utils::DateTimeToJS(result->Value)) : Undefined());
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void ExpirationTimeSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsDate())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotification^>(info.This()))
      {
        return;
      }

      ToastNotification *wrapper = ToastNotification::Unwrap<ToastNotification>(info.This());

      try 
      {
        
        ::Platform::IBox<::Windows::Foundation::DateTime>^ winRtValue = ref new ::Platform::Box<::Windows::Foundation::DateTime>(NodeRT::Utils::DateTimeFromJSDate(value));

        wrapper->_instance->ExpirationTime = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void ContentGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotification^>(info.This()))
      {
        return;
      }

      ToastNotification *wrapper = ToastNotification::Unwrap<ToastNotification>(info.This());

      try 
      {
        ::Windows::Data::Xml::Dom::XmlDocument^ result = wrapper->_instance->Content;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Data.Xml.Dom", "XmlDocument", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void TagGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotification^>(info.This()))
      {
        return;
      }

      ToastNotification *wrapper = ToastNotification::Unwrap<ToastNotification>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Tag;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void TagSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsString())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotification^>(info.This()))
      {
        return;
      }

      ToastNotification *wrapper = ToastNotification::Unwrap<ToastNotification>(info.This());

      try 
      {
        
        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));

        wrapper->_instance->Tag = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void SuppressPopupGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotification^>(info.This()))
      {
        return;
      }

      ToastNotification *wrapper = ToastNotification::Unwrap<ToastNotification>(info.This());

      try 
      {
        bool result = wrapper->_instance->SuppressPopup;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SuppressPopupSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsBoolean())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotification^>(info.This()))
      {
        return;
      }

      ToastNotification *wrapper = ToastNotification::Unwrap<ToastNotification>(info.This());

      try 
      {
        
        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->SuppressPopup = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void GroupGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotification^>(info.This()))
      {
        return;
      }

      ToastNotification *wrapper = ToastNotification::Unwrap<ToastNotification>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Group;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void GroupSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsString())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotification^>(info.This()))
      {
        return;
      }

      ToastNotification *wrapper = ToastNotification::Unwrap<ToastNotification>(info.This());

      try 
      {
        
        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));

        wrapper->_instance->Group = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void RemoteIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotification^>(info.This()))
      {
        return;
      }

      ToastNotification *wrapper = ToastNotification::Unwrap<ToastNotification>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->RemoteId;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void RemoteIdSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsString())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotification^>(info.This()))
      {
        return;
      }

      ToastNotification *wrapper = ToastNotification::Unwrap<ToastNotification>(info.This());

      try 
      {
        
        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));

        wrapper->_instance->RemoteId = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void NotificationMirroringGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotification^>(info.This()))
      {
        return;
      }

      ToastNotification *wrapper = ToastNotification::Unwrap<ToastNotification>(info.This());

      try 
      {
        ::Windows::UI::Notifications::NotificationMirroring result = wrapper->_instance->NotificationMirroring;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void NotificationMirroringSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsInt32())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotification^>(info.This()))
      {
        return;
      }

      ToastNotification *wrapper = ToastNotification::Unwrap<ToastNotification>(info.This());

      try 
      {
        
        ::Windows::UI::Notifications::NotificationMirroring winRtValue = static_cast<::Windows::UI::Notifications::NotificationMirroring>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->NotificationMirroring = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    


    static void AddListener(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected arguments are eventName(string),callback(function)")));
		return;
      }

      String::Value eventName(info[0]);
      auto str = *eventName;
      
      Local<Function> callback = info[1].As<Function>();
      
      ::Windows::Foundation::EventRegistrationToken registrationToken;
      if (NodeRT::Utils::CaseInsenstiveEquals(L"activated", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotification^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        ToastNotification *wrapper = ToastNotification::Unwrap<ToastNotification>(info.This());
      
        try
        {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr, 
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->Activated::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::UI::Notifications::ToastNotification^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::UI::Notifications::ToastNotification^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
           	    HandleScope scope;
                TryCatch tryCatch;
              
                Local<Value> error;

                Local<Value> wrappedArg0 = WrapToastNotification(arg0);
                Local<Value> wrappedArg1 = CreateOpaqueWrapper(arg1);

                if (tryCatch.HasCaught())
                {
                  error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
                }
                else 
                {
                  error = Undefined();
                }


                if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"dismissed", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotification^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        ToastNotification *wrapper = ToastNotification::Unwrap<ToastNotification>(info.This());
      
        try
        {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr, 
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->Dismissed::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::UI::Notifications::ToastNotification^, ::Windows::UI::Notifications::ToastDismissedEventArgs^>(
            [callbackObjPtr](::Windows::UI::Notifications::ToastNotification^ arg0, ::Windows::UI::Notifications::ToastDismissedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
           	    HandleScope scope;
                TryCatch tryCatch;
              
                Local<Value> error;

                Local<Value> wrappedArg0 = WrapToastNotification(arg0);
                Local<Value> wrappedArg1 = WrapToastDismissedEventArgs(arg1);

                if (tryCatch.HasCaught())
                {
                  error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
                }
                else 
                {
                  error = Undefined();
                }


                if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"failed", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotification^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
		  return;
        }
        ToastNotification *wrapper = ToastNotification::Unwrap<ToastNotification>(info.This());
      
        try
        {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr, 
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->Failed::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::UI::Notifications::ToastNotification^, ::Windows::UI::Notifications::ToastFailedEventArgs^>(
            [callbackObjPtr](::Windows::UI::Notifications::ToastNotification^ arg0, ::Windows::UI::Notifications::ToastFailedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
           	    HandleScope scope;
                TryCatch tryCatch;
              
                Local<Value> error;

                Local<Value> wrappedArg0 = WrapToastNotification(arg0);
                Local<Value> wrappedArg1 = WrapToastFailedEventArgs(arg1);

                if (tryCatch.HasCaught())
                {
                  error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
                }
                else 
                {
                  error = Undefined();
                }


                if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else 
      {
        Nan::ThrowError(Nan::Error(String::Concat(NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
		return;
      }

      Local<Value> tokenMapVal = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());
      Local<Object> tokenMap;

      if (tokenMapVal.IsEmpty() || Nan::Equals(tokenMapVal, Undefined()).FromMaybe(false))
      {
        tokenMap = Nan::New<Object>();
        NodeRT::Utils::SetHiddenValueWithObject(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked(), tokenMap);
      }
      else
      {
        tokenMap = Nan::To<Object>(tokenMapVal).ToLocalChecked();
      }

      Nan::Set(tokenMap, info[0], CreateOpaqueWrapper(::Windows::Foundation::PropertyValue::CreateInt64(registrationToken.Value)));
    }

    static void RemoveListener(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected a string and a callback")));
        return;
      }

      String::Value eventName(info[0]);
      auto str = *eventName;

      if ((NodeRT::Utils::CaseInsenstiveEquals(L"activated", str)) &&(NodeRT::Utils::CaseInsenstiveEquals(L"dismissed", str)) &&(NodeRT::Utils::CaseInsenstiveEquals(L"failed", str)))
      {
        Nan::ThrowError(Nan::Error(String::Concat(NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Function> callback = info[1].As<Function>();
      Local<Value> tokenMap = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());
                
      if (tokenMap.IsEmpty() || Nan::Equals(tokenMap, Undefined()).FromMaybe(false))
      {
        return;
      }

      Local<Value> opaqueWrapperObj =  Nan::Get(Nan::To<Object>(tokenMap).ToLocalChecked(), info[0]).ToLocalChecked();

      if (opaqueWrapperObj.IsEmpty() || Nan::Equals(opaqueWrapperObj,Undefined()).FromMaybe(false))
      {
        return;
      }

      OpaqueWrapper *opaqueWrapper = OpaqueWrapper::Unwrap<OpaqueWrapper>(opaqueWrapperObj.As<Object>());
            
      long long tokenValue = (long long) opaqueWrapper->GetObjectInstance();
      ::Windows::Foundation::EventRegistrationToken registrationToken;
      registrationToken.Value = tokenValue;
        
      try 
      {
        if (NodeRT::Utils::CaseInsenstiveEquals(L"activated", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotification^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          ToastNotification *wrapper = ToastNotification::Unwrap<ToastNotification>(info.This());
          wrapper->_instance->Activated::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"dismissed", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotification^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          ToastNotification *wrapper = ToastNotification::Unwrap<ToastNotification>(info.This());
          wrapper->_instance->Dismissed::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"failed", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotification^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          ToastNotification *wrapper = ToastNotification::Unwrap<ToastNotification>(info.This());
          wrapper->_instance->Failed::remove(registrationToken);
        }
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
  private:
    ::Windows::UI::Notifications::ToastNotification^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapToastNotification(::Windows::UI::Notifications::ToastNotification^ wintRtInstance);
    friend ::Windows::UI::Notifications::ToastNotification^ UnwrapToastNotification(Local<Value> value);
  };
  Persistent<FunctionTemplate> ToastNotification::s_constructorTemplate;

  v8::Local<v8::Value> WrapToastNotification(::Windows::UI::Notifications::ToastNotification^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(ToastNotification::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::Notifications::ToastNotification^ UnwrapToastNotification(Local<Value> value)
  {
     return ToastNotification::Unwrap<ToastNotification>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitToastNotification(Local<Object> exports)
  {
    ToastNotification::Init(exports);
  }

  class ScheduledToastNotification : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("ScheduledToastNotification").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("id").ToLocalChecked(), IdGetter, IdSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("content").ToLocalChecked(), ContentGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("deliveryTime").ToLocalChecked(), DeliveryTimeGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("maximumSnoozeCount").ToLocalChecked(), MaximumSnoozeCountGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("snoozeInterval").ToLocalChecked(), SnoozeIntervalGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("tag").ToLocalChecked(), TagGetter, TagSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("suppressPopup").ToLocalChecked(), SuppressPopupGetter, SuppressPopupSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("group").ToLocalChecked(), GroupGetter, GroupSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("remoteId").ToLocalChecked(), RemoteIdGetter, RemoteIdSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("notificationMirroring").ToLocalChecked(), NotificationMirroringGetter, NotificationMirroringSetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();


      Nan::Set(exports, Nan::New<String>("ScheduledToastNotification").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    ScheduledToastNotification(::Windows::UI::Notifications::ScheduledToastNotification^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Value> res = Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::UI::Notifications::ScheduledToastNotification^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ScheduledToastNotification^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::Notifications::ScheduledToastNotification^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info[0])
        && info[1]->IsDate())
      {
        try
        {
          ::Windows::Data::Xml::Dom::XmlDocument^ arg0 = dynamic_cast<::Windows::Data::Xml::Dom::XmlDocument^>(NodeRT::Utils::GetObjectInstance(info[0]));
          ::Windows::Foundation::DateTime arg1 = NodeRT::Utils::DateTimeFromJSDate(info[1]);
          
          winRtInstance = ref new ::Windows::UI::Notifications::ScheduledToastNotification(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 4
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Data::Xml::Dom::XmlDocument^>(info[0])
        && info[1]->IsDate()
        && info[2]->IsNumber()
        && info[3]->IsUint32())
      {
        try
        {
          ::Windows::Data::Xml::Dom::XmlDocument^ arg0 = dynamic_cast<::Windows::Data::Xml::Dom::XmlDocument^>(NodeRT::Utils::GetObjectInstance(info[0]));
          ::Windows::Foundation::DateTime arg1 = NodeRT::Utils::DateTimeFromJSDate(info[1]);
          ::Windows::Foundation::TimeSpan arg2 = NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(info[2]).FromMaybe(0));
          unsigned int arg3 = static_cast<unsigned int>(Nan::To<uint32_t>(info[3]).FromMaybe(0));
          
          winRtInstance = ref new ::Windows::UI::Notifications::ScheduledToastNotification(arg0,arg1,arg2,arg3);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      ScheduledToastNotification *wrapperInstance = new ScheduledToastNotification(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  



    static void IdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ScheduledToastNotification^>(info.This()))
      {
        return;
      }

      ScheduledToastNotification *wrapper = ScheduledToastNotification::Unwrap<ScheduledToastNotification>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Id;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IdSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsString())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ScheduledToastNotification^>(info.This()))
      {
        return;
      }

      ScheduledToastNotification *wrapper = ScheduledToastNotification::Unwrap<ScheduledToastNotification>(info.This());

      try 
      {
        
        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));

        wrapper->_instance->Id = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void ContentGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ScheduledToastNotification^>(info.This()))
      {
        return;
      }

      ScheduledToastNotification *wrapper = ScheduledToastNotification::Unwrap<ScheduledToastNotification>(info.This());

      try 
      {
        ::Windows::Data::Xml::Dom::XmlDocument^ result = wrapper->_instance->Content;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Data.Xml.Dom", "XmlDocument", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void DeliveryTimeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ScheduledToastNotification^>(info.This()))
      {
        return;
      }

      ScheduledToastNotification *wrapper = ScheduledToastNotification::Unwrap<ScheduledToastNotification>(info.This());

      try 
      {
        ::Windows::Foundation::DateTime result = wrapper->_instance->DeliveryTime;
        info.GetReturnValue().Set(NodeRT::Utils::DateTimeToJS(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void MaximumSnoozeCountGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ScheduledToastNotification^>(info.This()))
      {
        return;
      }

      ScheduledToastNotification *wrapper = ScheduledToastNotification::Unwrap<ScheduledToastNotification>(info.This());

      try 
      {
        unsigned int result = wrapper->_instance->MaximumSnoozeCount;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SnoozeIntervalGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ScheduledToastNotification^>(info.This()))
      {
        return;
      }

      ScheduledToastNotification *wrapper = ScheduledToastNotification::Unwrap<ScheduledToastNotification>(info.This());

      try 
      {
        ::Platform::IBox<::Windows::Foundation::TimeSpan>^ result = wrapper->_instance->SnoozeInterval;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Number>(result->Value.Duration/10000.0)) : Undefined());
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void TagGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ScheduledToastNotification^>(info.This()))
      {
        return;
      }

      ScheduledToastNotification *wrapper = ScheduledToastNotification::Unwrap<ScheduledToastNotification>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Tag;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void TagSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsString())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ScheduledToastNotification^>(info.This()))
      {
        return;
      }

      ScheduledToastNotification *wrapper = ScheduledToastNotification::Unwrap<ScheduledToastNotification>(info.This());

      try 
      {
        
        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));

        wrapper->_instance->Tag = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void SuppressPopupGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ScheduledToastNotification^>(info.This()))
      {
        return;
      }

      ScheduledToastNotification *wrapper = ScheduledToastNotification::Unwrap<ScheduledToastNotification>(info.This());

      try 
      {
        bool result = wrapper->_instance->SuppressPopup;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SuppressPopupSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsBoolean())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ScheduledToastNotification^>(info.This()))
      {
        return;
      }

      ScheduledToastNotification *wrapper = ScheduledToastNotification::Unwrap<ScheduledToastNotification>(info.This());

      try 
      {
        
        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->SuppressPopup = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void GroupGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ScheduledToastNotification^>(info.This()))
      {
        return;
      }

      ScheduledToastNotification *wrapper = ScheduledToastNotification::Unwrap<ScheduledToastNotification>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Group;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void GroupSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsString())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ScheduledToastNotification^>(info.This()))
      {
        return;
      }

      ScheduledToastNotification *wrapper = ScheduledToastNotification::Unwrap<ScheduledToastNotification>(info.This());

      try 
      {
        
        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));

        wrapper->_instance->Group = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void RemoteIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ScheduledToastNotification^>(info.This()))
      {
        return;
      }

      ScheduledToastNotification *wrapper = ScheduledToastNotification::Unwrap<ScheduledToastNotification>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->RemoteId;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void RemoteIdSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsString())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ScheduledToastNotification^>(info.This()))
      {
        return;
      }

      ScheduledToastNotification *wrapper = ScheduledToastNotification::Unwrap<ScheduledToastNotification>(info.This());

      try 
      {
        
        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));

        wrapper->_instance->RemoteId = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void NotificationMirroringGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ScheduledToastNotification^>(info.This()))
      {
        return;
      }

      ScheduledToastNotification *wrapper = ScheduledToastNotification::Unwrap<ScheduledToastNotification>(info.This());

      try 
      {
        ::Windows::UI::Notifications::NotificationMirroring result = wrapper->_instance->NotificationMirroring;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void NotificationMirroringSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsInt32())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ScheduledToastNotification^>(info.This()))
      {
        return;
      }

      ScheduledToastNotification *wrapper = ScheduledToastNotification::Unwrap<ScheduledToastNotification>(info.This());

      try 
      {
        
        ::Windows::UI::Notifications::NotificationMirroring winRtValue = static_cast<::Windows::UI::Notifications::NotificationMirroring>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->NotificationMirroring = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    


  private:
    ::Windows::UI::Notifications::ScheduledToastNotification^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapScheduledToastNotification(::Windows::UI::Notifications::ScheduledToastNotification^ wintRtInstance);
    friend ::Windows::UI::Notifications::ScheduledToastNotification^ UnwrapScheduledToastNotification(Local<Value> value);
  };
  Persistent<FunctionTemplate> ScheduledToastNotification::s_constructorTemplate;

  v8::Local<v8::Value> WrapScheduledToastNotification(::Windows::UI::Notifications::ScheduledToastNotification^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(ScheduledToastNotification::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::Notifications::ScheduledToastNotification^ UnwrapScheduledToastNotification(Local<Value> value)
  {
     return ScheduledToastNotification::Unwrap<ScheduledToastNotification>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitScheduledToastNotification(Local<Object> exports)
  {
    ScheduledToastNotification::Init(exports);
  }

  class ToastDismissedEventArgs : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("ToastDismissedEventArgs").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("reason").ToLocalChecked(), ReasonGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();


      Nan::Set(exports, Nan::New<String>("ToastDismissedEventArgs").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    ToastDismissedEventArgs(::Windows::UI::Notifications::ToastDismissedEventArgs^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Value> res = Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::UI::Notifications::ToastDismissedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastDismissedEventArgs^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::Notifications::ToastDismissedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      ToastDismissedEventArgs *wrapperInstance = new ToastDismissedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  



    static void ReasonGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastDismissedEventArgs^>(info.This()))
      {
        return;
      }

      ToastDismissedEventArgs *wrapper = ToastDismissedEventArgs::Unwrap<ToastDismissedEventArgs>(info.This());

      try 
      {
        ::Windows::UI::Notifications::ToastDismissalReason result = wrapper->_instance->Reason;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::UI::Notifications::ToastDismissedEventArgs^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapToastDismissedEventArgs(::Windows::UI::Notifications::ToastDismissedEventArgs^ wintRtInstance);
    friend ::Windows::UI::Notifications::ToastDismissedEventArgs^ UnwrapToastDismissedEventArgs(Local<Value> value);
  };
  Persistent<FunctionTemplate> ToastDismissedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapToastDismissedEventArgs(::Windows::UI::Notifications::ToastDismissedEventArgs^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(ToastDismissedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::Notifications::ToastDismissedEventArgs^ UnwrapToastDismissedEventArgs(Local<Value> value)
  {
     return ToastDismissedEventArgs::Unwrap<ToastDismissedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitToastDismissedEventArgs(Local<Object> exports)
  {
    ToastDismissedEventArgs::Init(exports);
  }

  class ToastFailedEventArgs : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("ToastFailedEventArgs").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("errorCode").ToLocalChecked(), ErrorCodeGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();


      Nan::Set(exports, Nan::New<String>("ToastFailedEventArgs").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    ToastFailedEventArgs(::Windows::UI::Notifications::ToastFailedEventArgs^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Value> res = Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::UI::Notifications::ToastFailedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastFailedEventArgs^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::Notifications::ToastFailedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      ToastFailedEventArgs *wrapperInstance = new ToastFailedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  



    static void ErrorCodeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastFailedEventArgs^>(info.This()))
      {
        return;
      }

      ToastFailedEventArgs *wrapper = ToastFailedEventArgs::Unwrap<ToastFailedEventArgs>(info.This());

      try 
      {
        ::Windows::Foundation::HResult result = wrapper->_instance->ErrorCode;
        info.GetReturnValue().Set(Nan::New<Integer>(result.Value));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::UI::Notifications::ToastFailedEventArgs^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapToastFailedEventArgs(::Windows::UI::Notifications::ToastFailedEventArgs^ wintRtInstance);
    friend ::Windows::UI::Notifications::ToastFailedEventArgs^ UnwrapToastFailedEventArgs(Local<Value> value);
  };
  Persistent<FunctionTemplate> ToastFailedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapToastFailedEventArgs(::Windows::UI::Notifications::ToastFailedEventArgs^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(ToastFailedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::Notifications::ToastFailedEventArgs^ UnwrapToastFailedEventArgs(Local<Value> value)
  {
     return ToastFailedEventArgs::Unwrap<ToastFailedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitToastFailedEventArgs(Local<Object> exports)
  {
    ToastFailedEventArgs::Init(exports);
  }

  class NotificationVisual : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("NotificationVisual").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "getBinding", GetBinding);
      
                        
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("language").ToLocalChecked(), LanguageGetter, LanguageSetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("bindings").ToLocalChecked(), BindingsGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();


      Nan::Set(exports, Nan::New<String>("NotificationVisual").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    NotificationVisual(::Windows::UI::Notifications::NotificationVisual^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Value> res = Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::UI::Notifications::NotificationVisual^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::NotificationVisual^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::Notifications::NotificationVisual^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      NotificationVisual *wrapperInstance = new NotificationVisual(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  
    static void GetBinding(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::NotificationVisual^>(info.This()))
      {
        return;
      }

      NotificationVisual *wrapper = NotificationVisual::Unwrap<NotificationVisual>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          ::Windows::UI::Notifications::NotificationBinding^ result;
          result = wrapper->_instance->GetBinding(arg0);
          info.GetReturnValue().Set(WrapNotificationBinding(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void LanguageGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::NotificationVisual^>(info.This()))
      {
        return;
      }

      NotificationVisual *wrapper = NotificationVisual::Unwrap<NotificationVisual>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Language;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void LanguageSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info)
    {
      HandleScope scope;
      
      if (!value->IsString())
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::NotificationVisual^>(info.This()))
      {
        return;
      }

      NotificationVisual *wrapper = NotificationVisual::Unwrap<NotificationVisual>(info.This());

      try 
      {
        
        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(value)));

        wrapper->_instance->Language = winRtValue;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
    
    static void BindingsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::NotificationVisual^>(info.This()))
      {
        return;
      }

      NotificationVisual *wrapper = NotificationVisual::Unwrap<NotificationVisual>(info.This());

      try 
      {
        ::Windows::Foundation::Collections::IVector<::Windows::UI::Notifications::NotificationBinding^>^ result = wrapper->_instance->Bindings;
        info.GetReturnValue().Set(NodeRT::Collections::VectorWrapper<::Windows::UI::Notifications::NotificationBinding^>::CreateVectorWrapper(result, 
            [](::Windows::UI::Notifications::NotificationBinding^ val) -> Local<Value> {
              return WrapNotificationBinding(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::NotificationBinding^>(value);
            },
            [](Local<Value> value) -> ::Windows::UI::Notifications::NotificationBinding^ {
              return UnwrapNotificationBinding(value);
            }
          ));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::UI::Notifications::NotificationVisual^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapNotificationVisual(::Windows::UI::Notifications::NotificationVisual^ wintRtInstance);
    friend ::Windows::UI::Notifications::NotificationVisual^ UnwrapNotificationVisual(Local<Value> value);
  };
  Persistent<FunctionTemplate> NotificationVisual::s_constructorTemplate;

  v8::Local<v8::Value> WrapNotificationVisual(::Windows::UI::Notifications::NotificationVisual^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(NotificationVisual::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::Notifications::NotificationVisual^ UnwrapNotificationVisual(Local<Value> value)
  {
     return NotificationVisual::Unwrap<NotificationVisual>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitNotificationVisual(Local<Object> exports)
  {
    NotificationVisual::Init(exports);
  }

  class ToastNotificationHistory : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("ToastNotificationHistory").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "removeGroup", RemoveGroup);
      Nan::SetPrototypeMethod(localRef, "remove", Remove);
      Nan::SetPrototypeMethod(localRef, "clear", Clear);
      Nan::SetPrototypeMethod(localRef, "getHistory", GetHistory);
      
                        
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();


      Nan::Set(exports, Nan::New<String>("ToastNotificationHistory").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    ToastNotificationHistory(::Windows::UI::Notifications::ToastNotificationHistory^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Value> res = Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::UI::Notifications::ToastNotificationHistory^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotificationHistory^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::Notifications::ToastNotificationHistory^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      ToastNotificationHistory *wrapperInstance = new ToastNotificationHistory(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  
    static void RemoveGroup(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotificationHistory^>(info.This()))
      {
        return;
      }

      ToastNotificationHistory *wrapper = ToastNotificationHistory::Unwrap<ToastNotificationHistory>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          wrapper->_instance->RemoveGroup(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && info[0]->IsString()
        && info[1]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[1])));
          
          wrapper->_instance->RemoveGroup(arg0, arg1);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Remove(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotificationHistory^>(info.This()))
      {
        return;
      }

      ToastNotificationHistory *wrapper = ToastNotificationHistory::Unwrap<ToastNotificationHistory>(info.This());

      if (info.Length() == 3
        && info[0]->IsString()
        && info[1]->IsString()
        && info[2]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[1])));
          Platform::String^ arg2 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[2])));
          
          wrapper->_instance->Remove(arg0, arg1, arg2);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && info[0]->IsString()
        && info[1]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[1])));
          
          wrapper->_instance->Remove(arg0, arg1);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          wrapper->_instance->Remove(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Clear(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotificationHistory^>(info.This()))
      {
        return;
      }

      ToastNotificationHistory *wrapper = ToastNotificationHistory::Unwrap<ToastNotificationHistory>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Clear();
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          wrapper->_instance->Clear(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetHistory(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotificationHistory^>(info.This()))
      {
        return;
      }

      ToastNotificationHistory *wrapper = ToastNotificationHistory::Unwrap<ToastNotificationHistory>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Collections::IVectorView<::Windows::UI::Notifications::ToastNotification^>^ result;
          result = wrapper->_instance->GetHistory();
          info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::UI::Notifications::ToastNotification^>::CreateVectorViewWrapper(result, 
            [](::Windows::UI::Notifications::ToastNotification^ val) -> Local<Value> {
              return WrapToastNotification(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotification^>(value);
            },
            [](Local<Value> value) -> ::Windows::UI::Notifications::ToastNotification^ {
              return UnwrapToastNotification(value);
            }
          ));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          ::Windows::Foundation::Collections::IVectorView<::Windows::UI::Notifications::ToastNotification^>^ result;
          result = wrapper->_instance->GetHistory(arg0);
          info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::UI::Notifications::ToastNotification^>::CreateVectorViewWrapper(result, 
            [](::Windows::UI::Notifications::ToastNotification^ val) -> Local<Value> {
              return WrapToastNotification(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotification^>(value);
            },
            [](Local<Value> value) -> ::Windows::UI::Notifications::ToastNotification^ {
              return UnwrapToastNotification(value);
            }
          ));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }





  private:
    ::Windows::UI::Notifications::ToastNotificationHistory^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapToastNotificationHistory(::Windows::UI::Notifications::ToastNotificationHistory^ wintRtInstance);
    friend ::Windows::UI::Notifications::ToastNotificationHistory^ UnwrapToastNotificationHistory(Local<Value> value);
  };
  Persistent<FunctionTemplate> ToastNotificationHistory::s_constructorTemplate;

  v8::Local<v8::Value> WrapToastNotificationHistory(::Windows::UI::Notifications::ToastNotificationHistory^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(ToastNotificationHistory::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::Notifications::ToastNotificationHistory^ UnwrapToastNotificationHistory(Local<Value> value)
  {
     return ToastNotificationHistory::Unwrap<ToastNotificationHistory>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitToastNotificationHistory(Local<Object> exports)
  {
    ToastNotificationHistory::Init(exports);
  }

  class ToastNotificationManagerForUser : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("ToastNotificationManagerForUser").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
            
      Nan::SetPrototypeMethod(localRef, "createToastNotifier", CreateToastNotifier);
      
                        
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("history").ToLocalChecked(), HistoryGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("user").ToLocalChecked(), UserGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();


      Nan::Set(exports, Nan::New<String>("ToastNotificationManagerForUser").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    ToastNotificationManagerForUser(::Windows::UI::Notifications::ToastNotificationManagerForUser^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Value> res = Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::UI::Notifications::ToastNotificationManagerForUser^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotificationManagerForUser^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::Notifications::ToastNotificationManagerForUser^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      ToastNotificationManagerForUser *wrapperInstance = new ToastNotificationManagerForUser(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  
    static void CreateToastNotifier(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotificationManagerForUser^>(info.This()))
      {
        return;
      }

      ToastNotificationManagerForUser *wrapper = ToastNotificationManagerForUser::Unwrap<ToastNotificationManagerForUser>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::UI::Notifications::ToastNotifier^ result;
          result = wrapper->_instance->CreateToastNotifier();
          info.GetReturnValue().Set(WrapToastNotifier(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          ::Windows::UI::Notifications::ToastNotifier^ result;
          result = wrapper->_instance->CreateToastNotifier(arg0);
          info.GetReturnValue().Set(WrapToastNotifier(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void HistoryGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotificationManagerForUser^>(info.This()))
      {
        return;
      }

      ToastNotificationManagerForUser *wrapper = ToastNotificationManagerForUser::Unwrap<ToastNotificationManagerForUser>(info.This());

      try 
      {
        ::Windows::UI::Notifications::ToastNotificationHistory^ result = wrapper->_instance->History;
        info.GetReturnValue().Set(WrapToastNotificationHistory(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void UserGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotificationManagerForUser^>(info.This()))
      {
        return;
      }

      ToastNotificationManagerForUser *wrapper = ToastNotificationManagerForUser::Unwrap<ToastNotificationManagerForUser>(info.This());

      try 
      {
        ::Windows::System::User^ result = wrapper->_instance->User;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.System", "User", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::UI::Notifications::ToastNotificationManagerForUser^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapToastNotificationManagerForUser(::Windows::UI::Notifications::ToastNotificationManagerForUser^ wintRtInstance);
    friend ::Windows::UI::Notifications::ToastNotificationManagerForUser^ UnwrapToastNotificationManagerForUser(Local<Value> value);
  };
  Persistent<FunctionTemplate> ToastNotificationManagerForUser::s_constructorTemplate;

  v8::Local<v8::Value> WrapToastNotificationManagerForUser(::Windows::UI::Notifications::ToastNotificationManagerForUser^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(ToastNotificationManagerForUser::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::Notifications::ToastNotificationManagerForUser^ UnwrapToastNotificationManagerForUser(Local<Value> value)
  {
     return ToastNotificationManagerForUser::Unwrap<ToastNotificationManagerForUser>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitToastNotificationManagerForUser(Local<Object> exports)
  {
    ToastNotificationManagerForUser::Init(exports);
  }

  class UserNotificationChangedEventArgs : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("UserNotificationChangedEventArgs").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("changeKind").ToLocalChecked(), ChangeKindGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("userNotificationId").ToLocalChecked(), UserNotificationIdGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();


      Nan::Set(exports, Nan::New<String>("UserNotificationChangedEventArgs").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    UserNotificationChangedEventArgs(::Windows::UI::Notifications::UserNotificationChangedEventArgs^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Value> res = Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::UI::Notifications::UserNotificationChangedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::UserNotificationChangedEventArgs^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::Notifications::UserNotificationChangedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      UserNotificationChangedEventArgs *wrapperInstance = new UserNotificationChangedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  



    static void ChangeKindGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::UserNotificationChangedEventArgs^>(info.This()))
      {
        return;
      }

      UserNotificationChangedEventArgs *wrapper = UserNotificationChangedEventArgs::Unwrap<UserNotificationChangedEventArgs>(info.This());

      try 
      {
        ::Windows::UI::Notifications::UserNotificationChangedKind result = wrapper->_instance->ChangeKind;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void UserNotificationIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::UserNotificationChangedEventArgs^>(info.This()))
      {
        return;
      }

      UserNotificationChangedEventArgs *wrapper = UserNotificationChangedEventArgs::Unwrap<UserNotificationChangedEventArgs>(info.This());

      try 
      {
        unsigned int result = wrapper->_instance->UserNotificationId;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::UI::Notifications::UserNotificationChangedEventArgs^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapUserNotificationChangedEventArgs(::Windows::UI::Notifications::UserNotificationChangedEventArgs^ wintRtInstance);
    friend ::Windows::UI::Notifications::UserNotificationChangedEventArgs^ UnwrapUserNotificationChangedEventArgs(Local<Value> value);
  };
  Persistent<FunctionTemplate> UserNotificationChangedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapUserNotificationChangedEventArgs(::Windows::UI::Notifications::UserNotificationChangedEventArgs^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(UserNotificationChangedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::Notifications::UserNotificationChangedEventArgs^ UnwrapUserNotificationChangedEventArgs(Local<Value> value)
  {
     return UserNotificationChangedEventArgs::Unwrap<UserNotificationChangedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitUserNotificationChangedEventArgs(Local<Object> exports)
  {
    UserNotificationChangedEventArgs::Init(exports);
  }

  class UserNotification : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("UserNotification").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("appInfo").ToLocalChecked(), AppInfoGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("creationTime").ToLocalChecked(), CreationTimeGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("id").ToLocalChecked(), IdGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("notification").ToLocalChecked(), NotificationGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();


      Nan::Set(exports, Nan::New<String>("UserNotification").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    UserNotification(::Windows::UI::Notifications::UserNotification^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Value> res = Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::UI::Notifications::UserNotification^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::UserNotification^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::Notifications::UserNotification^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      UserNotification *wrapperInstance = new UserNotification(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  



    static void AppInfoGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::UserNotification^>(info.This()))
      {
        return;
      }

      UserNotification *wrapper = UserNotification::Unwrap<UserNotification>(info.This());

      try 
      {
        ::Windows::ApplicationModel::AppInfo^ result = wrapper->_instance->AppInfo;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.ApplicationModel", "AppInfo", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CreationTimeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::UserNotification^>(info.This()))
      {
        return;
      }

      UserNotification *wrapper = UserNotification::Unwrap<UserNotification>(info.This());

      try 
      {
        ::Windows::Foundation::DateTime result = wrapper->_instance->CreationTime;
        info.GetReturnValue().Set(NodeRT::Utils::DateTimeToJS(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void IdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::UserNotification^>(info.This()))
      {
        return;
      }

      UserNotification *wrapper = UserNotification::Unwrap<UserNotification>(info.This());

      try 
      {
        unsigned int result = wrapper->_instance->Id;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void NotificationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::UserNotification^>(info.This()))
      {
        return;
      }

      UserNotification *wrapper = UserNotification::Unwrap<UserNotification>(info.This());

      try 
      {
        ::Windows::UI::Notifications::Notification^ result = wrapper->_instance->Notification;
        info.GetReturnValue().Set(WrapNotification(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::UI::Notifications::UserNotification^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapUserNotification(::Windows::UI::Notifications::UserNotification^ wintRtInstance);
    friend ::Windows::UI::Notifications::UserNotification^ UnwrapUserNotification(Local<Value> value);
  };
  Persistent<FunctionTemplate> UserNotification::s_constructorTemplate;

  v8::Local<v8::Value> WrapUserNotification(::Windows::UI::Notifications::UserNotification^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(UserNotification::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::Notifications::UserNotification^ UnwrapUserNotification(Local<Value> value)
  {
     return UserNotification::Unwrap<UserNotification>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitUserNotification(Local<Object> exports)
  {
    UserNotification::Init(exports);
  }

  class KnownAdaptiveNotificationHints : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("KnownAdaptiveNotificationHints").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();

      Nan::SetAccessor(constructor, Nan::New<String>("align").ToLocalChecked(), AlignGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("maxLines").ToLocalChecked(), MaxLinesGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("minLines").ToLocalChecked(), MinLinesGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("style").ToLocalChecked(), StyleGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("textStacking").ToLocalChecked(), TextStackingGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("wrap").ToLocalChecked(), WrapGetter);

      Nan::Set(exports, Nan::New<String>("KnownAdaptiveNotificationHints").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    KnownAdaptiveNotificationHints(::Windows::UI::Notifications::KnownAdaptiveNotificationHints^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Value> res = Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::UI::Notifications::KnownAdaptiveNotificationHints^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::KnownAdaptiveNotificationHints^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::Notifications::KnownAdaptiveNotificationHints^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      KnownAdaptiveNotificationHints *wrapperInstance = new KnownAdaptiveNotificationHints(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  




    static void AlignGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        Platform::String^ result = ::Windows::UI::Notifications::KnownAdaptiveNotificationHints::Align;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void MaxLinesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        Platform::String^ result = ::Windows::UI::Notifications::KnownAdaptiveNotificationHints::MaxLines;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void MinLinesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        Platform::String^ result = ::Windows::UI::Notifications::KnownAdaptiveNotificationHints::MinLines;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void StyleGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        Platform::String^ result = ::Windows::UI::Notifications::KnownAdaptiveNotificationHints::Style;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void TextStackingGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        Platform::String^ result = ::Windows::UI::Notifications::KnownAdaptiveNotificationHints::TextStacking;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void WrapGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        Platform::String^ result = ::Windows::UI::Notifications::KnownAdaptiveNotificationHints::Wrap;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    

  private:
    ::Windows::UI::Notifications::KnownAdaptiveNotificationHints^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapKnownAdaptiveNotificationHints(::Windows::UI::Notifications::KnownAdaptiveNotificationHints^ wintRtInstance);
    friend ::Windows::UI::Notifications::KnownAdaptiveNotificationHints^ UnwrapKnownAdaptiveNotificationHints(Local<Value> value);
  };
  Persistent<FunctionTemplate> KnownAdaptiveNotificationHints::s_constructorTemplate;

  v8::Local<v8::Value> WrapKnownAdaptiveNotificationHints(::Windows::UI::Notifications::KnownAdaptiveNotificationHints^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(KnownAdaptiveNotificationHints::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::Notifications::KnownAdaptiveNotificationHints^ UnwrapKnownAdaptiveNotificationHints(Local<Value> value)
  {
     return KnownAdaptiveNotificationHints::Unwrap<KnownAdaptiveNotificationHints>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitKnownAdaptiveNotificationHints(Local<Object> exports)
  {
    KnownAdaptiveNotificationHints::Init(exports);
  }

  class KnownNotificationBindings : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("KnownNotificationBindings").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();

      Nan::SetAccessor(constructor, Nan::New<String>("toastGeneric").ToLocalChecked(), ToastGenericGetter);

      Nan::Set(exports, Nan::New<String>("KnownNotificationBindings").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    KnownNotificationBindings(::Windows::UI::Notifications::KnownNotificationBindings^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Value> res = Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::UI::Notifications::KnownNotificationBindings^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::KnownNotificationBindings^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::Notifications::KnownNotificationBindings^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      KnownNotificationBindings *wrapperInstance = new KnownNotificationBindings(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  




    static void ToastGenericGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        Platform::String^ result = ::Windows::UI::Notifications::KnownNotificationBindings::ToastGeneric;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    

  private:
    ::Windows::UI::Notifications::KnownNotificationBindings^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapKnownNotificationBindings(::Windows::UI::Notifications::KnownNotificationBindings^ wintRtInstance);
    friend ::Windows::UI::Notifications::KnownNotificationBindings^ UnwrapKnownNotificationBindings(Local<Value> value);
  };
  Persistent<FunctionTemplate> KnownNotificationBindings::s_constructorTemplate;

  v8::Local<v8::Value> WrapKnownNotificationBindings(::Windows::UI::Notifications::KnownNotificationBindings^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(KnownNotificationBindings::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::Notifications::KnownNotificationBindings^ UnwrapKnownNotificationBindings(Local<Value> value)
  {
     return KnownNotificationBindings::Unwrap<KnownNotificationBindings>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitKnownNotificationBindings(Local<Object> exports)
  {
    KnownNotificationBindings::Init(exports);
  }

  class KnownAdaptiveNotificationTextStyles : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("KnownAdaptiveNotificationTextStyles").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();

      Nan::SetAccessor(constructor, Nan::New<String>("base").ToLocalChecked(), BaseGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("baseSubtle").ToLocalChecked(), BaseSubtleGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("body").ToLocalChecked(), BodyGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("bodySubtle").ToLocalChecked(), BodySubtleGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("caption").ToLocalChecked(), CaptionGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("captionSubtle").ToLocalChecked(), CaptionSubtleGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("header").ToLocalChecked(), HeaderGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("headerNumeral").ToLocalChecked(), HeaderNumeralGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("headerNumeralSubtle").ToLocalChecked(), HeaderNumeralSubtleGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("headerSubtle").ToLocalChecked(), HeaderSubtleGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("subheader").ToLocalChecked(), SubheaderGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("subheaderNumeral").ToLocalChecked(), SubheaderNumeralGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("subheaderNumeralSubtle").ToLocalChecked(), SubheaderNumeralSubtleGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("subheaderSubtle").ToLocalChecked(), SubheaderSubtleGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("subtitle").ToLocalChecked(), SubtitleGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("subtitleSubtle").ToLocalChecked(), SubtitleSubtleGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("title").ToLocalChecked(), TitleGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("titleNumeral").ToLocalChecked(), TitleNumeralGetter);
      Nan::SetAccessor(constructor, Nan::New<String>("titleSubtle").ToLocalChecked(), TitleSubtleGetter);

      Nan::Set(exports, Nan::New<String>("KnownAdaptiveNotificationTextStyles").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    KnownAdaptiveNotificationTextStyles(::Windows::UI::Notifications::KnownAdaptiveNotificationTextStyles^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Value> res = Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::UI::Notifications::KnownAdaptiveNotificationTextStyles^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::KnownAdaptiveNotificationTextStyles^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::Notifications::KnownAdaptiveNotificationTextStyles^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      KnownAdaptiveNotificationTextStyles *wrapperInstance = new KnownAdaptiveNotificationTextStyles(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  




    static void BaseGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        Platform::String^ result = ::Windows::UI::Notifications::KnownAdaptiveNotificationTextStyles::Base;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void BaseSubtleGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        Platform::String^ result = ::Windows::UI::Notifications::KnownAdaptiveNotificationTextStyles::BaseSubtle;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void BodyGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        Platform::String^ result = ::Windows::UI::Notifications::KnownAdaptiveNotificationTextStyles::Body;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void BodySubtleGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        Platform::String^ result = ::Windows::UI::Notifications::KnownAdaptiveNotificationTextStyles::BodySubtle;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CaptionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        Platform::String^ result = ::Windows::UI::Notifications::KnownAdaptiveNotificationTextStyles::Caption;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void CaptionSubtleGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        Platform::String^ result = ::Windows::UI::Notifications::KnownAdaptiveNotificationTextStyles::CaptionSubtle;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void HeaderGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        Platform::String^ result = ::Windows::UI::Notifications::KnownAdaptiveNotificationTextStyles::Header;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void HeaderNumeralGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        Platform::String^ result = ::Windows::UI::Notifications::KnownAdaptiveNotificationTextStyles::HeaderNumeral;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void HeaderNumeralSubtleGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        Platform::String^ result = ::Windows::UI::Notifications::KnownAdaptiveNotificationTextStyles::HeaderNumeralSubtle;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void HeaderSubtleGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        Platform::String^ result = ::Windows::UI::Notifications::KnownAdaptiveNotificationTextStyles::HeaderSubtle;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SubheaderGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        Platform::String^ result = ::Windows::UI::Notifications::KnownAdaptiveNotificationTextStyles::Subheader;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SubheaderNumeralGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        Platform::String^ result = ::Windows::UI::Notifications::KnownAdaptiveNotificationTextStyles::SubheaderNumeral;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SubheaderNumeralSubtleGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        Platform::String^ result = ::Windows::UI::Notifications::KnownAdaptiveNotificationTextStyles::SubheaderNumeralSubtle;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SubheaderSubtleGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        Platform::String^ result = ::Windows::UI::Notifications::KnownAdaptiveNotificationTextStyles::SubheaderSubtle;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SubtitleGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        Platform::String^ result = ::Windows::UI::Notifications::KnownAdaptiveNotificationTextStyles::Subtitle;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void SubtitleSubtleGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        Platform::String^ result = ::Windows::UI::Notifications::KnownAdaptiveNotificationTextStyles::SubtitleSubtle;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void TitleGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        Platform::String^ result = ::Windows::UI::Notifications::KnownAdaptiveNotificationTextStyles::Title;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void TitleNumeralGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        Platform::String^ result = ::Windows::UI::Notifications::KnownAdaptiveNotificationTextStyles::TitleNumeral;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void TitleSubtleGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        Platform::String^ result = ::Windows::UI::Notifications::KnownAdaptiveNotificationTextStyles::TitleSubtle;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    

  private:
    ::Windows::UI::Notifications::KnownAdaptiveNotificationTextStyles^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapKnownAdaptiveNotificationTextStyles(::Windows::UI::Notifications::KnownAdaptiveNotificationTextStyles^ wintRtInstance);
    friend ::Windows::UI::Notifications::KnownAdaptiveNotificationTextStyles^ UnwrapKnownAdaptiveNotificationTextStyles(Local<Value> value);
  };
  Persistent<FunctionTemplate> KnownAdaptiveNotificationTextStyles::s_constructorTemplate;

  v8::Local<v8::Value> WrapKnownAdaptiveNotificationTextStyles(::Windows::UI::Notifications::KnownAdaptiveNotificationTextStyles^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(KnownAdaptiveNotificationTextStyles::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::Notifications::KnownAdaptiveNotificationTextStyles^ UnwrapKnownAdaptiveNotificationTextStyles(Local<Value> value)
  {
     return KnownAdaptiveNotificationTextStyles::Unwrap<KnownAdaptiveNotificationTextStyles>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitKnownAdaptiveNotificationTextStyles(Local<Object> exports)
  {
    KnownAdaptiveNotificationTextStyles::Init(exports);
  }

  class TileUpdateManager : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("TileUpdateManager").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();

      Nan::SetMethod(constructor, "getForUser", GetForUser);
      Nan::SetMethod(constructor, "createTileUpdaterForApplication", CreateTileUpdaterForApplication);
      Nan::SetMethod(constructor, "createTileUpdaterForSecondaryTile", CreateTileUpdaterForSecondaryTile);
      Nan::SetMethod(constructor, "getTemplateContent", GetTemplateContent);

      Nan::Set(exports, Nan::New<String>("TileUpdateManager").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    TileUpdateManager(::Windows::UI::Notifications::TileUpdateManager^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Value> res = Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::UI::Notifications::TileUpdateManager^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::TileUpdateManager^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::Notifications::TileUpdateManager^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      TileUpdateManager *wrapperInstance = new TileUpdateManager(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  


    static void GetForUser(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::System::User^>(info[0]))
      {
        try
        {
          ::Windows::System::User^ arg0 = dynamic_cast<::Windows::System::User^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          ::Windows::UI::Notifications::TileUpdateManagerForUser^ result;
          result = ::Windows::UI::Notifications::TileUpdateManager::GetForUser(arg0);
          info.GetReturnValue().Set(WrapTileUpdateManagerForUser(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CreateTileUpdaterForApplication(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::UI::Notifications::TileUpdater^ result;
          result = ::Windows::UI::Notifications::TileUpdateManager::CreateTileUpdaterForApplication();
          info.GetReturnValue().Set(WrapTileUpdater(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          ::Windows::UI::Notifications::TileUpdater^ result;
          result = ::Windows::UI::Notifications::TileUpdateManager::CreateTileUpdaterForApplication(arg0);
          info.GetReturnValue().Set(WrapTileUpdater(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CreateTileUpdaterForSecondaryTile(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          ::Windows::UI::Notifications::TileUpdater^ result;
          result = ::Windows::UI::Notifications::TileUpdateManager::CreateTileUpdaterForSecondaryTile(arg0);
          info.GetReturnValue().Set(WrapTileUpdater(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetTemplateContent(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::UI::Notifications::TileTemplateType arg0 = static_cast<::Windows::UI::Notifications::TileTemplateType>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          ::Windows::Data::Xml::Dom::XmlDocument^ result;
          result = ::Windows::UI::Notifications::TileUpdateManager::GetTemplateContent(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Data.Xml.Dom", "XmlDocument", result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



  private:
    ::Windows::UI::Notifications::TileUpdateManager^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapTileUpdateManager(::Windows::UI::Notifications::TileUpdateManager^ wintRtInstance);
    friend ::Windows::UI::Notifications::TileUpdateManager^ UnwrapTileUpdateManager(Local<Value> value);
  };
  Persistent<FunctionTemplate> TileUpdateManager::s_constructorTemplate;

  v8::Local<v8::Value> WrapTileUpdateManager(::Windows::UI::Notifications::TileUpdateManager^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(TileUpdateManager::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::Notifications::TileUpdateManager^ UnwrapTileUpdateManager(Local<Value> value)
  {
     return TileUpdateManager::Unwrap<TileUpdateManager>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitTileUpdateManager(Local<Object> exports)
  {
    TileUpdateManager::Init(exports);
  }

  class BadgeUpdateManager : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("BadgeUpdateManager").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();

      Nan::SetMethod(constructor, "getForUser", GetForUser);
      Nan::SetMethod(constructor, "createBadgeUpdaterForApplication", CreateBadgeUpdaterForApplication);
      Nan::SetMethod(constructor, "createBadgeUpdaterForSecondaryTile", CreateBadgeUpdaterForSecondaryTile);
      Nan::SetMethod(constructor, "getTemplateContent", GetTemplateContent);

      Nan::Set(exports, Nan::New<String>("BadgeUpdateManager").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    BadgeUpdateManager(::Windows::UI::Notifications::BadgeUpdateManager^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Value> res = Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::UI::Notifications::BadgeUpdateManager^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::BadgeUpdateManager^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::Notifications::BadgeUpdateManager^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      BadgeUpdateManager *wrapperInstance = new BadgeUpdateManager(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  


    static void GetForUser(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::System::User^>(info[0]))
      {
        try
        {
          ::Windows::System::User^ arg0 = dynamic_cast<::Windows::System::User^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          ::Windows::UI::Notifications::BadgeUpdateManagerForUser^ result;
          result = ::Windows::UI::Notifications::BadgeUpdateManager::GetForUser(arg0);
          info.GetReturnValue().Set(WrapBadgeUpdateManagerForUser(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CreateBadgeUpdaterForApplication(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::UI::Notifications::BadgeUpdater^ result;
          result = ::Windows::UI::Notifications::BadgeUpdateManager::CreateBadgeUpdaterForApplication();
          info.GetReturnValue().Set(WrapBadgeUpdater(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          ::Windows::UI::Notifications::BadgeUpdater^ result;
          result = ::Windows::UI::Notifications::BadgeUpdateManager::CreateBadgeUpdaterForApplication(arg0);
          info.GetReturnValue().Set(WrapBadgeUpdater(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CreateBadgeUpdaterForSecondaryTile(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          ::Windows::UI::Notifications::BadgeUpdater^ result;
          result = ::Windows::UI::Notifications::BadgeUpdateManager::CreateBadgeUpdaterForSecondaryTile(arg0);
          info.GetReturnValue().Set(WrapBadgeUpdater(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetTemplateContent(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::UI::Notifications::BadgeTemplateType arg0 = static_cast<::Windows::UI::Notifications::BadgeTemplateType>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          ::Windows::Data::Xml::Dom::XmlDocument^ result;
          result = ::Windows::UI::Notifications::BadgeUpdateManager::GetTemplateContent(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Data.Xml.Dom", "XmlDocument", result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



  private:
    ::Windows::UI::Notifications::BadgeUpdateManager^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapBadgeUpdateManager(::Windows::UI::Notifications::BadgeUpdateManager^ wintRtInstance);
    friend ::Windows::UI::Notifications::BadgeUpdateManager^ UnwrapBadgeUpdateManager(Local<Value> value);
  };
  Persistent<FunctionTemplate> BadgeUpdateManager::s_constructorTemplate;

  v8::Local<v8::Value> WrapBadgeUpdateManager(::Windows::UI::Notifications::BadgeUpdateManager^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(BadgeUpdateManager::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::Notifications::BadgeUpdateManager^ UnwrapBadgeUpdateManager(Local<Value> value)
  {
     return BadgeUpdateManager::Unwrap<BadgeUpdateManager>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitBadgeUpdateManager(Local<Object> exports)
  {
    BadgeUpdateManager::Init(exports);
  }

  class TileFlyoutUpdateManager : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("TileFlyoutUpdateManager").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();

      Nan::SetMethod(constructor, "createTileFlyoutUpdaterForApplication", CreateTileFlyoutUpdaterForApplication);
      Nan::SetMethod(constructor, "createTileFlyoutUpdaterForSecondaryTile", CreateTileFlyoutUpdaterForSecondaryTile);
      Nan::SetMethod(constructor, "getTemplateContent", GetTemplateContent);

      Nan::Set(exports, Nan::New<String>("TileFlyoutUpdateManager").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    TileFlyoutUpdateManager(::Windows::UI::Notifications::TileFlyoutUpdateManager^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Value> res = Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::UI::Notifications::TileFlyoutUpdateManager^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::TileFlyoutUpdateManager^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::Notifications::TileFlyoutUpdateManager^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      TileFlyoutUpdateManager *wrapperInstance = new TileFlyoutUpdateManager(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  


    static void CreateTileFlyoutUpdaterForApplication(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::UI::Notifications::TileFlyoutUpdater^ result;
          result = ::Windows::UI::Notifications::TileFlyoutUpdateManager::CreateTileFlyoutUpdaterForApplication();
          info.GetReturnValue().Set(WrapTileFlyoutUpdater(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          ::Windows::UI::Notifications::TileFlyoutUpdater^ result;
          result = ::Windows::UI::Notifications::TileFlyoutUpdateManager::CreateTileFlyoutUpdaterForApplication(arg0);
          info.GetReturnValue().Set(WrapTileFlyoutUpdater(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CreateTileFlyoutUpdaterForSecondaryTile(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          ::Windows::UI::Notifications::TileFlyoutUpdater^ result;
          result = ::Windows::UI::Notifications::TileFlyoutUpdateManager::CreateTileFlyoutUpdaterForSecondaryTile(arg0);
          info.GetReturnValue().Set(WrapTileFlyoutUpdater(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetTemplateContent(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::UI::Notifications::TileFlyoutTemplateType arg0 = static_cast<::Windows::UI::Notifications::TileFlyoutTemplateType>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          ::Windows::Data::Xml::Dom::XmlDocument^ result;
          result = ::Windows::UI::Notifications::TileFlyoutUpdateManager::GetTemplateContent(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Data.Xml.Dom", "XmlDocument", result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



  private:
    ::Windows::UI::Notifications::TileFlyoutUpdateManager^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapTileFlyoutUpdateManager(::Windows::UI::Notifications::TileFlyoutUpdateManager^ wintRtInstance);
    friend ::Windows::UI::Notifications::TileFlyoutUpdateManager^ UnwrapTileFlyoutUpdateManager(Local<Value> value);
  };
  Persistent<FunctionTemplate> TileFlyoutUpdateManager::s_constructorTemplate;

  v8::Local<v8::Value> WrapTileFlyoutUpdateManager(::Windows::UI::Notifications::TileFlyoutUpdateManager^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(TileFlyoutUpdateManager::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::Notifications::TileFlyoutUpdateManager^ UnwrapTileFlyoutUpdateManager(Local<Value> value)
  {
     return TileFlyoutUpdateManager::Unwrap<TileFlyoutUpdateManager>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitTileFlyoutUpdateManager(Local<Object> exports)
  {
    TileFlyoutUpdateManager::Init(exports);
  }

  class ToastNotificationManager : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("ToastNotificationManager").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();

      Nan::SetMethod(constructor, "getForUser", GetForUser);
      Nan::SetMethod(constructor, "configureNotificationMirroring", ConfigureNotificationMirroring);
      Nan::SetMethod(constructor, "createToastNotifier", CreateToastNotifier);
      Nan::SetMethod(constructor, "getTemplateContent", GetTemplateContent);
      Nan::SetAccessor(constructor, Nan::New<String>("history").ToLocalChecked(), HistoryGetter);

      Nan::Set(exports, Nan::New<String>("ToastNotificationManager").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    ToastNotificationManager(::Windows::UI::Notifications::ToastNotificationManager^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Value> res = Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::UI::Notifications::ToastNotificationManager^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotificationManager^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::Notifications::ToastNotificationManager^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      ToastNotificationManager *wrapperInstance = new ToastNotificationManager(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  


    static void GetForUser(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::System::User^>(info[0]))
      {
        try
        {
          ::Windows::System::User^ arg0 = dynamic_cast<::Windows::System::User^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          ::Windows::UI::Notifications::ToastNotificationManagerForUser^ result;
          result = ::Windows::UI::Notifications::ToastNotificationManager::GetForUser(arg0);
          info.GetReturnValue().Set(WrapToastNotificationManagerForUser(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ConfigureNotificationMirroring(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::UI::Notifications::NotificationMirroring arg0 = static_cast<::Windows::UI::Notifications::NotificationMirroring>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          ::Windows::UI::Notifications::ToastNotificationManager::ConfigureNotificationMirroring(arg0);
          return;   
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CreateToastNotifier(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::UI::Notifications::ToastNotifier^ result;
          result = ::Windows::UI::Notifications::ToastNotificationManager::CreateToastNotifier();
          info.GetReturnValue().Set(WrapToastNotifier(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(info[0])));
          
          ::Windows::UI::Notifications::ToastNotifier^ result;
          result = ::Windows::UI::Notifications::ToastNotificationManager::CreateToastNotifier(arg0);
          info.GetReturnValue().Set(WrapToastNotifier(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetTemplateContent(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::UI::Notifications::ToastTemplateType arg0 = static_cast<::Windows::UI::Notifications::ToastTemplateType>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          ::Windows::Data::Xml::Dom::XmlDocument^ result;
          result = ::Windows::UI::Notifications::ToastNotificationManager::GetTemplateContent(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Data.Xml.Dom", "XmlDocument", result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else 
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }


    static void HistoryGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;

      try 
      {
        ::Windows::UI::Notifications::ToastNotificationHistory^ result = ::Windows::UI::Notifications::ToastNotificationManager::History;
        info.GetReturnValue().Set(WrapToastNotificationHistory(result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    

  private:
    ::Windows::UI::Notifications::ToastNotificationManager^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapToastNotificationManager(::Windows::UI::Notifications::ToastNotificationManager^ wintRtInstance);
    friend ::Windows::UI::Notifications::ToastNotificationManager^ UnwrapToastNotificationManager(Local<Value> value);
  };
  Persistent<FunctionTemplate> ToastNotificationManager::s_constructorTemplate;

  v8::Local<v8::Value> WrapToastNotificationManager(::Windows::UI::Notifications::ToastNotificationManager^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(ToastNotificationManager::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::Notifications::ToastNotificationManager^ UnwrapToastNotificationManager(Local<Value> value)
  {
     return ToastNotificationManager::Unwrap<ToastNotificationManager>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitToastNotificationManager(Local<Object> exports)
  {
    ToastNotificationManager::Init(exports);
  }

  class ToastActivatedEventArgs : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("ToastActivatedEventArgs").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("arguments").ToLocalChecked(), ArgumentsGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();


      Nan::Set(exports, Nan::New<String>("ToastActivatedEventArgs").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    ToastActivatedEventArgs(::Windows::UI::Notifications::ToastActivatedEventArgs^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Value> res = Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::UI::Notifications::ToastActivatedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastActivatedEventArgs^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::Notifications::ToastActivatedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      ToastActivatedEventArgs *wrapperInstance = new ToastActivatedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  



    static void ArgumentsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastActivatedEventArgs^>(info.This()))
      {
        return;
      }

      ToastActivatedEventArgs *wrapper = ToastActivatedEventArgs::Unwrap<ToastActivatedEventArgs>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Arguments;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::UI::Notifications::ToastActivatedEventArgs^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapToastActivatedEventArgs(::Windows::UI::Notifications::ToastActivatedEventArgs^ wintRtInstance);
    friend ::Windows::UI::Notifications::ToastActivatedEventArgs^ UnwrapToastActivatedEventArgs(Local<Value> value);
  };
  Persistent<FunctionTemplate> ToastActivatedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapToastActivatedEventArgs(::Windows::UI::Notifications::ToastActivatedEventArgs^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(ToastActivatedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::Notifications::ToastActivatedEventArgs^ UnwrapToastActivatedEventArgs(Local<Value> value)
  {
     return ToastActivatedEventArgs::Unwrap<ToastActivatedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitToastActivatedEventArgs(Local<Object> exports)
  {
    ToastActivatedEventArgs::Init(exports);
  }

  class ToastNotificationHistoryChangedTriggerDetail : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("ToastNotificationHistoryChangedTriggerDetail").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("changeType").ToLocalChecked(), ChangeTypeGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();


      Nan::Set(exports, Nan::New<String>("ToastNotificationHistoryChangedTriggerDetail").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    ToastNotificationHistoryChangedTriggerDetail(::Windows::UI::Notifications::ToastNotificationHistoryChangedTriggerDetail^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Value> res = Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::UI::Notifications::ToastNotificationHistoryChangedTriggerDetail^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotificationHistoryChangedTriggerDetail^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::Notifications::ToastNotificationHistoryChangedTriggerDetail^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      ToastNotificationHistoryChangedTriggerDetail *wrapperInstance = new ToastNotificationHistoryChangedTriggerDetail(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  



    static void ChangeTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotificationHistoryChangedTriggerDetail^>(info.This()))
      {
        return;
      }

      ToastNotificationHistoryChangedTriggerDetail *wrapper = ToastNotificationHistoryChangedTriggerDetail::Unwrap<ToastNotificationHistoryChangedTriggerDetail>(info.This());

      try 
      {
        ::Windows::UI::Notifications::ToastHistoryChangedType result = wrapper->_instance->ChangeType;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::UI::Notifications::ToastNotificationHistoryChangedTriggerDetail^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapToastNotificationHistoryChangedTriggerDetail(::Windows::UI::Notifications::ToastNotificationHistoryChangedTriggerDetail^ wintRtInstance);
    friend ::Windows::UI::Notifications::ToastNotificationHistoryChangedTriggerDetail^ UnwrapToastNotificationHistoryChangedTriggerDetail(Local<Value> value);
  };
  Persistent<FunctionTemplate> ToastNotificationHistoryChangedTriggerDetail::s_constructorTemplate;

  v8::Local<v8::Value> WrapToastNotificationHistoryChangedTriggerDetail(::Windows::UI::Notifications::ToastNotificationHistoryChangedTriggerDetail^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(ToastNotificationHistoryChangedTriggerDetail::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::Notifications::ToastNotificationHistoryChangedTriggerDetail^ UnwrapToastNotificationHistoryChangedTriggerDetail(Local<Value> value)
  {
     return ToastNotificationHistoryChangedTriggerDetail::Unwrap<ToastNotificationHistoryChangedTriggerDetail>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitToastNotificationHistoryChangedTriggerDetail(Local<Object> exports)
  {
    ToastNotificationHistoryChangedTriggerDetail::Init(exports);
  }

  class ToastNotificationActionTriggerDetail : public WrapperBase
  {
  public:    
    static void Init(const Local<Object> exports)
    {
      HandleScope scope;
      
      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
      s_constructorTemplate.Reset(localRef);
      localRef->SetClassName(Nan::New<String>("ToastNotificationActionTriggerDetail").ToLocalChecked());
      localRef->InstanceTemplate()->SetInternalFieldCount(1);
      
                              
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("argument").ToLocalChecked(), ArgumentGetter);
      Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("userInput").ToLocalChecked(), UserInputGetter);
      
      Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();


      Nan::Set(exports, Nan::New<String>("ToastNotificationActionTriggerDetail").ToLocalChecked(), constructor);
    }


    virtual ::Platform::Object^ GetObjectInstance() const override
    {
      return _instance;
    }

  private:
    
    ToastNotificationActionTriggerDetail(::Windows::UI::Notifications::ToastNotificationActionTriggerDetail^ instance)
    {
      _instance = instance;
    }
    
    
    static void New(Nan::NAN_METHOD_ARGS_TYPE info)
    {
      HandleScope scope;

	    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This()))
      {
        if (info.Length() > 0)
        {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++)
          {
            argsPtr[i] = info[i];
          }

		  info.GetReturnValue().Set(Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get()).ToLocalChecked());
		  return;
		}
		else
		{
          MaybeLocal<Value> res = Nan::CallAsConstructor(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);
          if (res.IsEmpty())
          {
            return;
          }
          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }
      
      ::Windows::UI::Notifications::ToastNotificationActionTriggerDetail^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotificationActionTriggerDetail^>(info[0]))
      {
        try 
        {
          winRtInstance = (::Windows::UI::Notifications::ToastNotificationActionTriggerDetail^) NodeRT::Utils::GetObjectInstance(info[0]);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else
      {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
	    	return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      ToastNotificationActionTriggerDetail *wrapperInstance = new ToastNotificationActionTriggerDetail(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


  



    static void ArgumentGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotificationActionTriggerDetail^>(info.This()))
      {
        return;
      }

      ToastNotificationActionTriggerDetail *wrapper = ToastNotificationActionTriggerDetail::Unwrap<ToastNotificationActionTriggerDetail>(info.This());

      try 
      {
        Platform::String^ result = wrapper->_instance->Argument;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    
    static void UserInputGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info)
    {
      HandleScope scope;
      
      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Notifications::ToastNotificationActionTriggerDetail^>(info.This()))
      {
        return;
      }

      ToastNotificationActionTriggerDetail *wrapper = ToastNotificationActionTriggerDetail::Unwrap<ToastNotificationActionTriggerDetail>(info.This());

      try 
      {
        ::Windows::Foundation::Collections::ValueSet^ result = wrapper->_instance->UserInput;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation.Collections", "ValueSet", result));
        return;
      }
      catch (Platform::Exception ^exception)
      {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
    


  private:
    ::Windows::UI::Notifications::ToastNotificationActionTriggerDetail^ _instance;
    static Persistent<FunctionTemplate> s_constructorTemplate;

    friend v8::Local<v8::Value> WrapToastNotificationActionTriggerDetail(::Windows::UI::Notifications::ToastNotificationActionTriggerDetail^ wintRtInstance);
    friend ::Windows::UI::Notifications::ToastNotificationActionTriggerDetail^ UnwrapToastNotificationActionTriggerDetail(Local<Value> value);
  };
  Persistent<FunctionTemplate> ToastNotificationActionTriggerDetail::s_constructorTemplate;

  v8::Local<v8::Value> WrapToastNotificationActionTriggerDetail(::Windows::UI::Notifications::ToastNotificationActionTriggerDetail^ winRtInstance)
  {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr)
    {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(ToastNotificationActionTriggerDetail::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::UI::Notifications::ToastNotificationActionTriggerDetail^ UnwrapToastNotificationActionTriggerDetail(Local<Value> value)
  {
     return ToastNotificationActionTriggerDetail::Unwrap<ToastNotificationActionTriggerDetail>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitToastNotificationActionTriggerDetail(Local<Object> exports)
  {
    ToastNotificationActionTriggerDetail::Init(exports);
  }

} } } } 

NAN_MODULE_INIT(init)
{
  if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED)))
  {
    Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"error in CoInitializeEx()")));
    return;
  }
  
  NodeRT::Windows::UI::Notifications::InitNotificationSettingEnum(target);
  NodeRT::Windows::UI::Notifications::InitToastDismissalReasonEnum(target);
  NodeRT::Windows::UI::Notifications::InitBadgeTemplateTypeEnum(target);
  NodeRT::Windows::UI::Notifications::InitTileFlyoutTemplateTypeEnum(target);
  NodeRT::Windows::UI::Notifications::InitTileTemplateTypeEnum(target);
  NodeRT::Windows::UI::Notifications::InitToastTemplateTypeEnum(target);
  NodeRT::Windows::UI::Notifications::InitPeriodicUpdateRecurrenceEnum(target);
  NodeRT::Windows::UI::Notifications::InitToastHistoryChangedTypeEnum(target);
  NodeRT::Windows::UI::Notifications::InitAdaptiveNotificationContentKindEnum(target);
  NodeRT::Windows::UI::Notifications::InitNotificationMirroringEnum(target);
  NodeRT::Windows::UI::Notifications::InitNotificationKindsEnum(target);
  NodeRT::Windows::UI::Notifications::InitUserNotificationChangedKindEnum(target);
  NodeRT::Windows::UI::Notifications::InitShownTileNotification(target);
  NodeRT::Windows::UI::Notifications::InitNotification(target);
  NodeRT::Windows::UI::Notifications::InitNotificationBinding(target);
  NodeRT::Windows::UI::Notifications::InitIAdaptiveNotificationContent(target);
  NodeRT::Windows::UI::Notifications::InitAdaptiveNotificationText(target);
  NodeRT::Windows::UI::Notifications::InitTileUpdater(target);
  NodeRT::Windows::UI::Notifications::InitTileUpdateManagerForUser(target);
  NodeRT::Windows::UI::Notifications::InitTileNotification(target);
  NodeRT::Windows::UI::Notifications::InitScheduledTileNotification(target);
  NodeRT::Windows::UI::Notifications::InitTileFlyoutUpdater(target);
  NodeRT::Windows::UI::Notifications::InitTileFlyoutNotification(target);
  NodeRT::Windows::UI::Notifications::InitBadgeUpdater(target);
  NodeRT::Windows::UI::Notifications::InitBadgeUpdateManagerForUser(target);
  NodeRT::Windows::UI::Notifications::InitBadgeNotification(target);
  NodeRT::Windows::UI::Notifications::InitToastNotifier(target);
  NodeRT::Windows::UI::Notifications::InitToastNotification(target);
  NodeRT::Windows::UI::Notifications::InitScheduledToastNotification(target);
  NodeRT::Windows::UI::Notifications::InitToastDismissedEventArgs(target);
  NodeRT::Windows::UI::Notifications::InitToastFailedEventArgs(target);
  NodeRT::Windows::UI::Notifications::InitNotificationVisual(target);
  NodeRT::Windows::UI::Notifications::InitToastNotificationHistory(target);
  NodeRT::Windows::UI::Notifications::InitToastNotificationManagerForUser(target);
  NodeRT::Windows::UI::Notifications::InitUserNotificationChangedEventArgs(target);
  NodeRT::Windows::UI::Notifications::InitUserNotification(target);
  NodeRT::Windows::UI::Notifications::InitKnownAdaptiveNotificationHints(target);
  NodeRT::Windows::UI::Notifications::InitKnownNotificationBindings(target);
  NodeRT::Windows::UI::Notifications::InitKnownAdaptiveNotificationTextStyles(target);
  NodeRT::Windows::UI::Notifications::InitTileUpdateManager(target);
  NodeRT::Windows::UI::Notifications::InitBadgeUpdateManager(target);
  NodeRT::Windows::UI::Notifications::InitTileFlyoutUpdateManager(target);
  NodeRT::Windows::UI::Notifications::InitToastNotificationManager(target);
  NodeRT::Windows::UI::Notifications::InitToastActivatedEventArgs(target);
  NodeRT::Windows::UI::Notifications::InitToastNotificationHistoryChangedTriggerDetail(target);
  NodeRT::Windows::UI::Notifications::InitToastNotificationActionTriggerDetail(target);

  NodeRT::Utils::RegisterNameSpace("Windows.UI.Notifications", target);
}


NODE_MODULE(binding, init)