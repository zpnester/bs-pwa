type t;

[@bs.get] external endpoint: t => string = "endpoint";
[@bs.get] [@bs.return nullable]
external expirationTime: t => option(float) = "expirationTime";

/* TODO */
[@bs.get] external options: t => Js.Json.t = "options";
/* subscriptionId deprecated */

[@bs.send]
external getKey: (t, string) => Js.Typed_array.ArrayBuffer.t = "getKey";
[@bs.send] external toJSON: t => Js.Json.t = "toJSON";
[@bs.send] external unsubscribe: t => Js.Promise.t(bool) = "unsubscribe";
