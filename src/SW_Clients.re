type t;

type match_all_options = {
  .
  "includeUncontrolled": Js.Nullable.t(bool),
  "type": Js.Nullable.t(SW_ClientType.t),
};


[@bs.send]
external get_: (t, string) => Js.Promise.t(Js.Nullable.t(SW_Client.t)) =
  "get";

let get = (self, id) =>
  get_(self, id)
  |> Js.Promise.then_(maybe_client =>
       Js.Promise.resolve(Js.Nullable.toOption(maybe_client))
     );

[@bs.send]
external matchAll_:
  (t, Js.Nullable.t(match_all_options)) => Js.Promise.t(array(SW_Client.t)) =
  "matchAll";

let matchAll =
    (
      self: t,
      ~includeUncontrolled: option(bool)=?,
      ~type_: option(SW_ClientType.t)=?,
      (),
    ) => {
  let opts =
    if (includeUncontrolled->Belt.Option.isNone && type_->Belt.Option.isNone) {
      Js.Nullable.undefined;
    } else {
      Js.Nullable.return({
        "includeUncontrolled": Js.Nullable.fromOption(includeUncontrolled),
        "type": Js.Nullable.fromOption(type_),
      });
    };
  self->matchAll_(opts);
};

[@bs.send]
external openWindow_:
  (t, string) => Js.Promise.t(Js.Nullable.t(SW_WindowClient.t)) =
  "openWindow";

let openWindow = (self, url) =>
  self->openWindow_(url)
  |> Js.Promise.then_(maybeClient =>
       Js.Promise.resolve(Js.Nullable.toOption(maybeClient))
     );

[@bs.send] external claim: t => Js.Promise.t(unit) = "claim";