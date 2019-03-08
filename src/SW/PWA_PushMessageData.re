type t;

[@bs.send] external blob: t => FileReader.Blob.t = "blob";
[@bs.send] external arrayBuffer: t => Js.Typed_array.ArrayBuffer.t = "arrayBuffer";
[@bs.send] external json: t => Js.Json.t = "json";
[@bs.send] external text: t => string = "text";