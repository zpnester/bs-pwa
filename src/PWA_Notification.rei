type t;
type ctor;

module Action = PWA_Notification_Action;

let ctor: option(ctor);

let permission: ctor => [ | `granted | `denied | `default];
let requestPermission:
  ctor => Js.Promise.t([ | `granted | `denied | `default]);

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

[@bs.set] external onclick: (t, PWA_Event.t => unit) => unit = "onclick";

let make:
  (
    ctor,
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
