type t;

let scope: t => string;

let getNotifications:
  (t, ~tag: string=?, unit) => Js.Promise.t(array(PWA_Notification.t));

let active: t => option(PWA_ServiceWorker.t);
let installing: t => option(PWA_ServiceWorker.t);
let waiting: t => option(PWA_ServiceWorker.t);

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

let pushManager: t => option(PWA_PushManager.t);

/* "experimental technology" */
let updatefound: PWA_EventType.t(t, unit);