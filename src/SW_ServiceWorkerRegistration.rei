type t;

let getNotifications:
  (t, ~tag: string=?, unit) => Js.Promise.t(array(SW_Notification.t));

let active: t => option(SW_ServiceWorker.t);
let installing: t => option(SW_ServiceWorker.t);
let waiting: t => option(SW_ServiceWorker.t);

/* docs says it returns promise of message event, got promise of undefined when tested */
let showNotification:
  (
    t,
    string,
    ~actions: array(SW_Notification_Action.t)=?,
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

let pushManager: t => option(SW_PushManager.t);