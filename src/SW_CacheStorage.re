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
  (t, 
  [@bs.unwrap] [`Request(SW_Request.t) | `String(string) ], 
  Js.Nullable.t(match_options)) =>
  Js.Promise.t(Js.Nullable.t(SW_Response.t)) =
  "match";

let match = (self: t, request: [ `Request(SW_Request.t) | `String(string) ], ~ignoreSearch: option(bool)=?,
  ~ignoreMethod: option(bool)=?, ~ignoreVary: option(bool)=?, ~cacheName: option(string)=?, ()
   ) => {
     let opts = if (Js.Option.isNone(ignoreSearch) && Js.Option.isNone(ignoreMethod) &&
      Js.Option.isNone(ignoreVary) && Js.Option.isNone(cacheName)) {
          Js.Nullable.undefined
      } else {
        Js.Nullable.return({
        "ignoreSearch": Js.Nullable.fromOption(ignoreSearch),
        "ignoreMethod": Js.Nullable.fromOption(ignoreMethod),
        "ignoreVary": Js.Nullable.fromOption(ignoreVary),
        "cacheName": Js.Nullable.fromOption(cacheName),
      });
      }
      self->matchJs(request, opts)
      |> Js.Promise.then_(maybeResponse => Js.Promise.resolve(Js.Nullable.toOption(maybeResponse)))
   };


[@bs.send] external has: (t, string) => Js.Promise.t(bool) = "has";

[@bs.send] external open_: (t, string) => Js.Promise.t(SW_Cache.t) = "open";

[@bs.send] external delete: (t, string) => Js.Promise.t(bool) = "delete";

[@bs.send] external keys: t => Js.Promise.t(array(string)) = "keys";
