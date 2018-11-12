type t;

open SW_Types;

module Action = SW_Notification_Action;

let scope: t => any;

let installing: t => option(SW_ServiceWorker.t);
let waiting: t => option(SW_ServiceWorker.t);
let active: t => option(SW_ServiceWorker.t);
/* navigationPreload  */
/* pushManager */
/* onupdatefound */
/* inherits EventTarget */
let getNotifications:
  (t, ~tag: string=?, unit) => Js.Promise.t(array(SW_Notification.t));

let showNotification:
  (
    t,
    string,
    ~actions: array(Action.t)=?,
    ~badge: string=?,
    ~body: string=?,
    ~dir: string=?,
    ~icon: string=?,
    ~image: string=?,
    ~lang: string=?,
    ~renotify: bool=?,
    ~requireInteraction: bool=?,
    ~tag: any=?,
    ~vibrate: any=?,
    ~data: any=?,
    unit
  ) =>
  Js.Promise.t(SW_NotificationEvent.t);
let update: t => unit;
let unregister: t => Js.Promise.t(bool);