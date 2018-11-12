type t;

type match_options = {
  .
  "ignoreSearch": Js.Nullable.t(bool),
  "ignoreMethod": Js.Nullable.t(bool),
  "ignoreVary": Js.Nullable.t(bool),
  "cacheName": Js.Nullable.t(string),
};

[@bs.send]
external matchJs:
  (
    t,
    [@bs.unwrap] [ | `Request(SW_Request.t) | `String(string)],
    Js.Nullable.t(match_options)
  ) =>
  Js.Promise.t(Js.Nullable.t(SW_Response.t)) =
  "match";

let match =
    (
      self: t,
      request: [ | `Request(SW_Request.t) | `String(string)],
      ~ignoreSearch: option(bool)=?,
      ~ignoreMethod: option(bool)=?,
      ~ignoreVary: option(bool)=?,
      ~cacheName: option(string)=?,
      (),
    ) => {
  let opts =
    if (Js.Option.isNone(ignoreSearch)
        && Js.Option.isNone(ignoreMethod)
        && Js.Option.isNone(ignoreVary)
        && Js.Option.isNone(cacheName)) {
      Js.Nullable.undefined;
    } else {
      Js.Nullable.return({
        "ignoreSearch": Js.Nullable.fromOption(ignoreSearch),
        "ignoreMethod": Js.Nullable.fromOption(ignoreMethod),
        "ignoreVary": Js.Nullable.fromOption(ignoreVary),
        "cacheName": Js.Nullable.fromOption(cacheName),
      });
    };
  self->matchJs(request, opts)
  |> Js.Promise.then_(maybeResponse =>
       Js.Promise.resolve(Js.Nullable.toOption(maybeResponse))
     );
};

[@bs.send]
external matchAllJs:
  (
    t,
    [@bs.unwrap] [ | `Request(SW_Request.t) | `String(string)],
    Js.Nullable.t(match_options)
  ) =>
  Js.Promise.t(array(SW_Response.t)) =
  "match";

let matchAll =
    (
      self: t,
      request: [ | `Request(SW_Request.t) | `String(string)],
      ~ignoreSearch: option(bool)=?,
      ~ignoreMethod: option(bool)=?,
      ~ignoreVary: option(bool)=?,
      ~cacheName: option(string)=?,
      (),
    ) => {
  let opts =
    if (Js.Option.isNone(ignoreSearch)
        && Js.Option.isNone(ignoreMethod)
        && Js.Option.isNone(ignoreVary)
        && Js.Option.isNone(cacheName)) {
      Js.Nullable.undefined;
    } else {
      Js.Nullable.return({
        "ignoreSearch": Js.Nullable.fromOption(ignoreSearch),
        "ignoreMethod": Js.Nullable.fromOption(ignoreMethod),
        "ignoreVary": Js.Nullable.fromOption(ignoreVary),
        "cacheName": Js.Nullable.fromOption(cacheName),
      });
    };
  self->matchAllJs(request, opts);
};

[@bs.send]
external add:
  (t, [@bs.unwrap] [ | `Request(SW_Request.t) | `String(string)]) =>
  Js.Promise.t(unit) =
  "add";

[@bs.send]
external addAll: (t, array(string)) => Js.Promise.t(unit) = "addAll";

[@bs.send]
external put: (t, SW_Request.t, SW_Response.t) => Js.Promise.t(unit) = "put";

[@bs.send]
external deleteJs:
  (
    t,
    [@bs.unwrap] [ | `Request(SW_Request.t) | `String(string)],
    Js.Nullable.t(match_options)
  ) =>
  Js.Promise.t(bool) =
  "delete";

let delete =
    (
      self: t,
      request: [ | `Request(SW_Request.t) | `String(string)],
      ~ignoreSearch: option(bool)=?,
      ~ignoreMethod: option(bool)=?,
      ~ignoreVary: option(bool)=?,
      ~cacheName: option(string)=?,
      (),
    ) => {
  let opts =
    if (Js.Option.isNone(ignoreSearch)
        && Js.Option.isNone(ignoreMethod)
        && Js.Option.isNone(ignoreVary)
        && Js.Option.isNone(cacheName)) {
      Js.Nullable.undefined;
    } else {
      Js.Nullable.return({
        "ignoreSearch": Js.Nullable.fromOption(ignoreSearch),
        "ignoreMethod": Js.Nullable.fromOption(ignoreMethod),
        "ignoreVary": Js.Nullable.fromOption(ignoreVary),
        "cacheName": Js.Nullable.fromOption(cacheName),
      });
    };
  self->deleteJs(request, opts);
};

/* TODO request only or string allowed also? */
[@bs.send]
external keysJs:
  (t, Js.Nullable.t(SW_Request.t), Js.Nullable.t(match_options)) =>
  Js.Promise.t(array(SW_Request.t)) =
  "keys";

let keys =
    (
      self: t,
      ~request: option(SW_Request.t)=?,
      ~ignoreSearch: option(bool)=?,
      ~ignoreMethod: option(bool)=?,
      ~ignoreVary: option(bool)=?,
      ~cacheName: option(string)=?,
      (),
    ) => {
  let opts =
    if (Js.Option.isNone(ignoreSearch)
        && Js.Option.isNone(ignoreMethod)
        && Js.Option.isNone(ignoreVary)
        && Js.Option.isNone(cacheName)) {
      Js.Nullable.undefined;
    } else {
      Js.Nullable.return({
        "ignoreSearch": Js.Nullable.fromOption(ignoreSearch),
        "ignoreMethod": Js.Nullable.fromOption(ignoreMethod),
        "ignoreVary": Js.Nullable.fromOption(ignoreVary),
        "cacheName": Js.Nullable.fromOption(cacheName),
      });
    };
  self->keysJs(Js.Nullable.fromOption(request), opts);
};