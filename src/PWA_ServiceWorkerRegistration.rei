type t;

include (module type of
  PWA_EventTarget.Make({
    type nonrec t = t;
  }));

[@bs.get] external scope: t => string = "scope";

let getNotifications:
  (t, ~tag: string=?, unit) => Js.Promise.t(array(PWA_Notification.t));

[@bs.get] [@bs.return nullable]
external active: t => option(PWA_ServiceWorker.t) = "active";

[@bs.get] [@bs.return nullable]
external installing: t => option(PWA_ServiceWorker.t) = "installing";

[@bs.get] [@bs.return nullable]
external waiting: t => option(PWA_ServiceWorker.t) = "waiting";

/* docs says it returns promise of message event, got promise of undefined when tested */
let showNotification:
  (
    t,
    string,
    ~actions: array(PWA_Notification_Action.t)=?,
    ~badge: string=?,
    ~body: string=?,
    ~dir: string=?,
    ~icon: string=?,
    ~image: string=?,
    ~lang: string=?,
    ~renotify: bool=?,
    ~requireInteraction: bool=?,
    ~tag: string=?,
    ~vibrate: 'a=?,
    ~data: 'b=?,
    unit
  ) =>
  Js.Promise.t(unit);

[@bs.get] [@bs.return nullable]
external pushManager: t => option(PWA_PushManager.t) = "pushManager";

/* "experimental technology" */
let updatefound: PWA_EventType.t(t, unit);
