type t;

module Action = PWA_Notification_Action;

type permission = [ | `granted | `denied | `default];

let permission: permission;
let requestPermission: unit => Js.Promise.t(permission);

let actions: t => option(array(PWA_Notification_Action.t));
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

let onclick: (t, PWA_Event.t => unit) => unit;

let make:
  (
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
    ~vibrate: Js.Json.t=?,
    ~data: Js.Json.t=?,
    unit
  ) =>
  t;