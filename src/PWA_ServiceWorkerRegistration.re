type t;

include PWA_EventTarget.Make({
  type nonrec t = t;
});

[@bs.get] external scope: t => string = "scope";

/* navigationPreload */

[@bs.send]
external getNotifications_:
  (t, Js.Nullable.t({. "tag": string})) =>
  Js.Promise.t(array(PWA_Notification.t)) =
  "getNotifications";

let getNotifications = (self: t, ~tag: option(string)=?, ()) => {
  let opts =
    switch (tag) {
    | Some(tag) => Js.Nullable.return({"tag": tag})
    | None => Js.Nullable.undefined
    };

  self->getNotifications_(opts);
};

[@bs.get]
external active_: t => Js.Nullable.t(PWA_ServiceWorker.t) = "active";

let active = self => self->active_->Js.Nullable.toOption;

[@bs.get]
external installing_: t => Js.Nullable.t(PWA_ServiceWorker.t) = "installing";

let installing = self => self->installing_->Js.Nullable.toOption;

[@bs.get]
external waiting_: t => Js.Nullable.t(PWA_ServiceWorker.t) = "waiting";

let waiting = self => self->waiting_->Js.Nullable.toOption;

/* same as in Notification */
type show_notification_options('a, 'b) = {
  .
  "actions": Js.Nullable.t(array(PWA_Notification_Action.t)),
  "badge": Js.Nullable.t(string),
  "body": Js.Nullable.t(string),
  "dir": Js.Nullable.t(string),
  "icon": Js.Nullable.t(string),
  "image": Js.Nullable.t(string),
  "lang": Js.Nullable.t(string),
  "renotify": Js.Nullable.t(bool),
  "requireInteraction": Js.Nullable.t(bool),
  "tag": Js.Nullable.t(string),
  "vibrate": Js.Nullable.t('a),
  "data": Js.Nullable.t('b),
};

[@bs.send]
external showNotification_:
  (t, string, Js.Nullable.t(show_notification_options('a, 'b))) =>
  Js.Promise.t(unit) =
  "showNotification";

let showNotification =
    (
      self: t,
      title: string,
      ~actions: option(array(PWA_Notification_Action.t))=?,
      ~badge: option(string)=?,
      ~body: option(string)=?,
      ~dir: option(string)=?,
      ~icon: option(string)=?,
      ~image: option(string)=?,
      ~lang: option(string)=?,
      ~renotify: option(bool)=?,
      ~requireInteraction: option(bool)=?,
      ~tag: option(string)=?,
      ~vibrate: option('a)=?,
      ~data: option('b)=?,
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

[@bs.get]
external pushManager_: t => Js.Nullable.t(PWA_PushManager.t) = "pushManager";

let pushManager = self => pushManager_(self)->Js.Nullable.toOption;

let updatefound: PWA_EventType.t(t, unit) =
  PWA_EventType.unsafe("updatefound");
