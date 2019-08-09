type t;

include PWA_EventTarget.Make({
  type nonrec t = t;
});

[@bs.get] external scope: t => string = "scope";

/* navigationPreload */

[@bs.send]
external getNotifications: t => Js.Promise.t(array(PWA_Notification.t)) =
  "getNotifications";

[@bs.send]
external getNotifications1:
  (t, {. "tag": string}) => Js.Promise.t(array(PWA_Notification.t)) =
  "getNotifications";

[@bs.get] [@bs.return nullable]
external active: t => option(PWA_ServiceWorker.t) = "active";

[@bs.get] [@bs.return nullable]
external installing: t => option(PWA_ServiceWorker.t) = "installing";

[@bs.get] [@bs.return nullable]
external waiting: t => option(PWA_ServiceWorker.t) = "waiting";

[@bs.send]
external showNotificationWithOptions:
  (t, string, PWA_Notification.Options.t) => Js.Promise.t(unit) =
  "showNotification";

[@bs.send]
external showNotification: (t, string) => Js.Promise.t(unit) =
  "showNotification";

[@bs.get] [@bs.return nullable]
external pushManager: t => option(PWA_PushManager.t) = "pushManager";

let updatefound: PWA_EventType.t(t, unit) =
  PWA_EventType.unsafe("updatefound");