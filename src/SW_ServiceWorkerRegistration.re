type t;

open SW_Types;

module Action = SW_Notification_Action;

[@bs.get] external scope: t => any = "scope";

[@bs.get]
external installing_: t => Js.Nullable.t(SW_ServiceWorker.t) = "installing";

let installing = self => self->installing_->Js.Nullable.toOption;

[@bs.get]
external waiting_: t => Js.Nullable.t(SW_ServiceWorker.t) = "waiting";

let waiting = self => self->waiting_->Js.Nullable.toOption;

[@bs.get] external active_: t => Js.Nullable.t(SW_ServiceWorker.t) = "active";

let active = self => self->active_->Js.Nullable.toOption;

/* navigationPreload  */
/* pushManager */
/* onupdatefound */
/* inherits EventTarget */

[@bs.send]
external getNotifications_:
  (t, Js.Nullable.t({. "tag": string})) =>
  Js.Promise.t(array(SW_Notification.t)) =
  "getNotifications";

let getNotifications = (self: t, ~tag: option(string)=?, ()) => {
  let opts =
    switch (tag) {
    | Some(tag) => Js.Nullable.return({"tag": tag})
    | None => Js.Nullable.undefined
    };

  self->getNotifications_(opts);
};

type show_notification_options = {
  .
  "actions": Js.Nullable.t(array(Action.t)),
  "badge": Js.Nullable.t(string),
  "body": Js.Nullable.t(string),
  "dir": Js.Nullable.t(string),
  "icon": Js.Nullable.t(string),
  "image": Js.Nullable.t(string),
  "lang": Js.Nullable.t(string),
  "renotify": Js.Nullable.t(bool),
  "requireInteraction": Js.Nullable.t(bool),
  "tag": Js.Nullable.t(any),
  "vibrate": Js.Nullable.t(any),
  "data": Js.Nullable.t(any),
};

/* returns notification event, not notification */
[@bs.send]
external showNotification_:
  (t, string, Js.Nullable.t(show_notification_options)) =>
  Js.Promise.t(SW_NotificationEvent.t) =
  "showNotification";

let showNotification =
    (
      self: t,
      title: string,
      ~actions: option(array(Action.t))=?,
      ~badge: option(string)=?,
      ~body: option(string)=?,
      ~dir: option(string)=?,
      ~icon: option(string)=?,
      ~image: option(string)=?,
      ~lang: option(string)=?,
      ~renotify: option(bool)=?,
      ~requireInteraction: option(bool)=?,
      ~tag: option(any)=?,
      ~vibrate: option(any)=?,
      ~data: option(any)=?,
      (),
    ) => {
  open Belt.Option;
  let opts =
    if (isNone(actions)
        && isNone(badge)
        && isNone(body)
        && isNone(dir)
        && isNone(icon)
        && isNone(image)
        && isNone(lang)
        && isNone(renotify)
        && isNone(requireInteraction)
        && isNone(tag)
        && isNone(vibrate)
        && isNone(data)) {
      Js.Nullable.undefined;
    } else {
      Js.Nullable.return({
        "actions": Js.Nullable.fromOption(actions),
        "badge": Js.Nullable.fromOption(badge),
        "body": Js.Nullable.fromOption(body),
        "dir": Js.Nullable.fromOption(dir),
        "icon": Js.Nullable.fromOption(icon),
        "image": Js.Nullable.fromOption(image),
        "lang": Js.Nullable.fromOption(lang),
        "renotify": Js.Nullable.fromOption(renotify),
        "requireInteraction": Js.Nullable.fromOption(requireInteraction),
        "tag": Js.Nullable.fromOption(tag),
        "vibrate": Js.Nullable.fromOption(vibrate),
        "data": Js.Nullable.fromOption(data),
      });
    };

  self->showNotification_(title, opts);
};

[@bs.send] external update: t => unit = "update";

[@bs.send] external unregister: t => Js.Promise.t(bool) = "unregister";