type t;

open SW_Types;

let permission: SW_Notification_Permission.t;

let actions: t => option(array(any));
let badge: t => option(string);
let body: t => option(string);
let data: t => option(any);
let dir: t => option(string);
let tag: t => option(string);
let icon: t => option(string);
let image: t => option(string);
let renotify: t => option(bool);
let silent: t => option(bool);
let timestamp: t => option(dom_time_stamp);
let title: t => option(string);
let vibrate: t => option(any);

/* not available in workers? */
let requestPermission: unit => Js.Promise.t(SW_Notification_Permission.t);
let close: t => unit;