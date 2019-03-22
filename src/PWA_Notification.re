type t;
type ctor;

let ctor_: Js.Nullable.t(ctor) = [%raw
  {|
( (typeof Notification === "function") ? Notification : null)
|}
];

let ctor = ctor_->Js.Nullable.toOption;
exception NotificationError(Js.Promise.error);

module Action = PWA_Notification_Action;

let toPermission_ =
  fun
  | "granted" => `granted
  | "denied" => `denied
  | "default" => `default
  | _ => failwith("unexpected permision");

[@bs.get] external permission_: ctor => string = "permission";

let permission = ctor => permission_(ctor)->toPermission_;

// safari uses callback

[@bs.send] [@bs.return nullable]
external requestPermission_:
  (ctor, string => unit) => option(Js.Promise.t(string)) =
  "requestPermission";

let requestPermission = ctor =>
  Js.Promise.make((~resolve, ~reject) => {
    // pass callback that resolves promise
    let maybePromise =
      requestPermission_(ctor, res => resolve(. res->toPermission_));

    // if promise returned - forward result
    switch (maybePromise) {
    | Some(promise) =>
      promise
      |> Js.Promise.then_(res => {
           resolve(. res->toPermission_);
           Js.Promise.resolve();
         })
      |> Js.Promise.catch(err => {
           reject(. NotificationError(err));
           Js.Promise.resolve();
         })
      |> ignore
    | None => ()
    };
  });

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

type show_notification_options = {
  .
  "actions": Js.Nullable.t(array(PWA_Notification_Action.t)),
  "badge": Js.Nullable.t(string),
  "body": Js.Nullable.t(string),
  "dir": Js.Nullable.t(string),
  "icon": Js.Nullable.t(string),
  "image": Js.Nullable.t(string),
  "lang": Js.Nullable.t(string),
  "renotify": Js.Nullable.t(bool),
  "requireInteraction": Js.Nullable.t(bool),
  "tag": Js.Nullable.t(string),
  "vibrate": Js.Nullable.t(Js.Json.t),
  "data": Js.Nullable.t(Js.Json.t),
};

let make_: (ctor, string, Js.Nullable.t(show_notification_options)) => t = [%raw
  {|
function(ctor, title, options) {
  return new ctor(title, options);
}
|}
];

let make =
    (
      self: ctor,
      title: string,
      ~actions: option(array(PWA_Notification_Action.t))=?,
      ~badge: option(string)=?,
      ~body: option(string)=?,
      ~dir: option(string)=?,
      ~icon: option(string)=?,
      ~image: option(string)=?,
      ~lang: option(string)=?,
      ~renotify: option(bool)=?,
      ~requireInteraction: option(bool)=?,
      ~tag: option(string)=?,
      ~vibrate: option(Js.Json.t)=?,
      ~data: option(Js.Json.t)=?,
      (),
    ) => {
  open Belt.Option;
  let opts =
    if (isNone(actions)
        && isNone(badge)
        && isNone(body)
        && isNone(dir)
        && isNone(icon)
        && isNone(image)
        && isNone(lang)
        && isNone(renotify)
        && isNone(requireInteraction)
        && isNone(tag)
        && isNone(vibrate)
        && isNone(data)) {
      Js.Nullable.undefined;
    } else {
      Js.Nullable.return({
        "actions": Js.Nullable.fromOption(actions),
        "badge": Js.Nullable.fromOption(badge),
        "body": Js.Nullable.fromOption(body),
        "dir": Js.Nullable.fromOption(dir),
        "icon": Js.Nullable.fromOption(icon),
        "image": Js.Nullable.fromOption(image),
        "lang": Js.Nullable.fromOption(lang),
        "renotify": Js.Nullable.fromOption(renotify),
        "requireInteraction": Js.Nullable.fromOption(requireInteraction),
        "tag": Js.Nullable.fromOption(tag),
        "vibrate": Js.Nullable.fromOption(vibrate),
        "data": Js.Nullable.fromOption(data),
      });
    };
  make_(self, title, opts);
};
