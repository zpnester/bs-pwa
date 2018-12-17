type t;

let permission: SW_Notification_Permission.t;

let actions: t => option(array(SW_Notification_Action.t));
let badge: t => option(string);
let body: t => option(string);
let data: t => option(Js.Json.t);
let dir: t => option(string);
let tag: t => option(string);
let icon: t => option(string);
let image: t => option(string);
let renotify: t => option(bool);
let silent: t => option(bool);
let timestamp: t => option(float);
let title: t => option(string);
let vibrate: t => option(Js.Json.t);
let close: t => unit;