open PWA__;

type t;

external fromArrayBuffer: Js.Typed_array.ArrayBuffer.t => t = "%identity";
external fromMessagePort: messagePort => t = "%identity";

external makeUnsafe: 'unsafe => t = "%identity";