type t;

/* blob */
[@bs.send] external arraybuffer: t => Js.Typed_array.ArrayBuffer.t = "json";
[@bs.send] external json: t => Js.Json.t = "json";
[@bs.send] external text: t => string = "text";