type t;

open SW_Types;

/* static */
[@bs.val] [@bs.scope "Notification"]
external permission: SW_Notification_Permission.t = "permission";

[@bs.get] external actions_: t => Js.Nullable.t(array(any)) = "actions";
[@bs.get] external badge_: t => Js.Nullable.t(string) = "badge";
[@bs.get] external body_: t => Js.Nullable.t(string) = "body";
[@bs.get] external data_: t => Js.Nullable.t(any) = "data";
[@bs.get] external dir_: t => Js.Nullable.t(string) = "dir";
[@bs.get] external tag_: t => Js.Nullable.t(string) = "tag";
[@bs.get] external icon_: t => Js.Nullable.t(string) = "icon";
[@bs.get] external image_: t => Js.Nullable.t(string) = "image";
[@bs.get] external renotify_: t => Js.Nullable.t(bool) = "renotify";
[@bs.get] external silent_: t => Js.Nullable.t(bool) = "silent";

[@bs.get]
external timestamp_: t => Js.Nullable.t(dom_time_stamp) = "timestamp";
[@bs.get] external title_: t => Js.Nullable.t(string) = "title";

[@bs.get] external vibrate_: t => Js.Nullable.t(any) = "vibrate";

let actions = (self: t) => self->actions_->Js.Nullable.toOption;
let badge = (self: t) => self->badge_->Js.Nullable.toOption;
let body = (self: t) => self->body_->Js.Nullable.toOption;
let data = (self: t) => self->data_->Js.Nullable.toOption;
let dir = (self: t) => self->dir_->Js.Nullable.toOption;
let tag = (self: t) => self->tag_->Js.Nullable.toOption;
let icon = (self: t) => self->icon_->Js.Nullable.toOption;
let image = (self: t) => self->image_->Js.Nullable.toOption;
let renotify = (self: t) => self->renotify_->Js.Nullable.toOption;
let silent = (self: t) => self->silent_->Js.Nullable.toOption;

let timestamp = (self: t) => self->timestamp_->Js.Nullable.toOption;
let title = (self: t) => self->title_->Js.Nullable.toOption;

let vibrate = (self: t) => self->vibrate_->Js.Nullable.toOption;

/* TODO onclick onclose onerror onshow */

/* static */
[@bs.val] [@bs.scope "Notification"]
external requestPermission:
  unit => Js.Promise.t(SW_Notification_Permission.t) =
  "requestPermission";

[@bs.send] external close: t => unit = "close";