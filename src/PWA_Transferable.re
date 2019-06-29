open PWA__;

type t;

external arrayBuffer: Js.Typed_array.ArrayBuffer.t => t = "%identity";
external messagePort: messagePort => t = "%identity";
