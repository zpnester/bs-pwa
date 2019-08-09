type t;

[@bs.send]
external get_: (t, string) => Js.Promise.t(Js.Nullable.t(PWA_Client.t)) =
  "get";

let get = (self, id) =>
  get_(self, id)
  |> Js.Promise.then_(maybeClient =>
       Js.Promise.resolve(Js.Nullable.toOption(maybeClient))
     );

module MatchAllOptions = {
  type t;
  [@bs.obj]
  external make:
    (~includeUncontrolled: bool=?, ~_type: PWA_ClientType.t=?, unit) => t =
    "";
};

[@bs.send]
external matchAll: t => Js.Promise.t(array(PWA_Client.t)) = "matchAll";

[@bs.send]
external matchAll1:
  (t, MatchAllOptions.t) => Js.Promise.t(array(PWA_Client.t)) =
  "matchAll";

[@bs.send]
external openWindow_:
  (t, string) => Js.Promise.t(Js.Nullable.t(PWA_WindowClient.t)) =
  "openWindow";

let openWindow = (self, url) =>
  self->openWindow_(url)
  |> Js.Promise.then_(maybeClient =>
       Js.Promise.resolve(Js.Nullable.toOption(maybeClient))
     );

[@bs.send] external claim: t => Js.Promise.t(unit) = "claim";