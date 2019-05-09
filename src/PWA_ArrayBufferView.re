type t;

external int8Array: Js.Typed_array.Int8Array.t => t = "%identity";
external unt8Array: Js.Typed_array.Uint8Array.t => t = "%identity";
external uint8ClampedArray: Js.Typed_array.Uint8ClampedArray.t => t =
  "%identity";
external int16Array: Js.Typed_array.Int16Array.t => t = "%identity";
external uint16Array: Js.Typed_array.Uint16Array.t => t = "%identity";
external int32Array: Js.Typed_array.Int32Array.t => t = "%identity";
external uint32Array: Js.Typed_array.Uint32Array.t => t = "%identity";
external float32Array: Js.Typed_array.Float32Array.t => t = "%identity";
external float64Array: Js.Typed_array.Float64Array.t => t = "%identity";
external dataView: Js.Typed_array.DataView.t => t = "%identity";