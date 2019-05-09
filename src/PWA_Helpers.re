let isArrayBuffer_: Js.Json.t => bool = [%raw
  {|
    function(value) {
        return value instanceof ArrayBuffer;
    }
|}
];

external asArrayBufferUnsafe__: Js.Json.t => Js.Typed_array.ArrayBuffer.t =
  "%identity";

let asArrayBuffer = x =>
  if (x->isArrayBuffer_) {
    Some(asArrayBufferUnsafe__(x));
  } else {
    None;
  };