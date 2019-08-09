type t;
type ctor;

exception NotificationError(Js.Promise.error);

module Action = PWA_Notification_Action;

type permission = [ | `granted | `denied | `default];

let permission: unit => permission;

let requestPermission: unit => Js.Promise.t(permission);

[@bs.get] [@bs.return nullable]
external actions: t => option(array(PWA_Notification_Action.t)) = "actions";
[@bs.get] [@bs.return nullable] external badge: t => option(string) = "badge";
[@bs.get] [@bs.return nullable] external body: t => option(string) = "body";
[@bs.get] [@bs.return nullable]
external data: t => option(Js.Json.t) = "data";
[@bs.get] [@bs.return nullable] external dir: t => option(string) = "dir";
[@bs.get] [@bs.return nullable] external tag: t => option(string) = "tag";
[@bs.get] [@bs.return nullable] external icon: t => option(string) = "icon";
[@bs.get] [@bs.return nullable] external image: t => option(string) = "image";
[@bs.get] [@bs.return nullable]
external renotify: t => option(bool) = "renotify";
[@bs.get] [@bs.return nullable] external silent: t => option(bool) = "silent";

[@bs.get] [@bs.return nullable]
external timestamp: t => option(float) = "timestamp";
[@bs.get] [@bs.return nullable] external title: t => option(string) = "title";

[@bs.get] [@bs.return nullable]
external vibrate: t => option(Js.Json.t) = "vibrate";

[@bs.send] external close: t => unit = "close";

[@bs.set] external setOnclick: (t, PWA_Event.t => unit) => unit = "onclick";

module Options = PWA_NotificationOptions;

// new, avoid external

let make: string => t;
let make2: (string, Options.t) => t;