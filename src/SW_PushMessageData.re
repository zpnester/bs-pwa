
type t;

/* blob */
/* arraybuffer */
[@bs.send] external json: t => Js.Json.t = "json";
[@bs.send] external text: t => string = "text";