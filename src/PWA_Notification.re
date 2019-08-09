type t;
type ctor;

exception NotificationError(Js.Promise.error);

module Action = PWA_Notification_Action;

[@bs.deriving jsConverter]
type permission = [ | `granted | `denied | `default];

[@bs.val] [@bs.scope "Notification"]
external permission_: string = "permission";

let unwrapPermission = (p: option(permission)): permission => {
  switch (p) {
  | Some(p) => p
  | None => failwith("unknown_permission")
  };
};

// () is required

let permission = () => permission_->permissionFromJs->unwrapPermission;

[@bs.val] [@bs.scope "Notification"] [@bs.return nullable]
external requestPermission_: (string => unit) => option(Js.Promise.t(string)) =
  "requestPermission";

let requestPermission = () =>
  Js.Promise.make((~resolve, ~reject) => {
    // pass callback that resolves promise
    let maybePromise =
      requestPermission_(res =>
        resolve(. res->permissionFromJs->unwrapPermission)
      );

    // if promise returned - forward result
    switch (maybePromise) {
    | Some(promise) =>
      promise
      |> Js.Promise.then_(res => {
           resolve(. res->permissionFromJs->unwrapPermission);
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

[@bs.set] external setOnclick: (t, PWA_Event.t => unit) => unit = "onclick";

module Options = PWA_NotificationOption;

[@bs.new] external make: string => t = "Notification";
[@bs.new] external makeWithOptions: (string, Options.t) => t = "Notification";