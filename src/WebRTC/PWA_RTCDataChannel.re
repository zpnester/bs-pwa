type t;

include PWA_EventTarget.Make({
  type nonrec t = t;
});

module Init = {
  type t;

  [@bs.obj]
  external make:
    (
      ~ordered: bool=?,
      ~maxPacketLifeTime: int=?,
      ~maxRetransmits: int=?,
      ~protocol: string=?,
      ~negotiated: bool=?,
      ~id: int=?,
      unit
    ) =>
    t =
    "";
};

[@bs.get] external binaryType: t => string = "binaryType";
[@bs.set] external setBinaryType: (t, string) => unit = "binaryType";

[@bs.get] external bufferedAmount: t => int = "bufferedAmount";


[@bs.get]
external bufferedAmountLowThreshold: t => int = "bufferedAmountLowThreshold";
[@bs.set]
external setBufferedAmountLowThreshold: (t, int) => unit =
  "bufferedAmountLowThreshold";

[@bs.get] [@bs.return nullable] external id: t => option(int) = "id";

[@bs.get] external label: t => string = "label";

// TODO delete if not implemented in browsers
[@bs.get] [@bs.return nullable]
external maxPacketLifeTime: t => option(int) = "maxPacketLifeTime";

[@bs.get] [@bs.return nullable] external maxRetransmits: t => option(int) = "maxRetransmits";

[@bs.get]  [@bs.return nullable]  external negotiated: t => option(bool) = "negotiated";

[@bs.get] external ordered: t => bool = "ordered";

[@bs.get] external protocol: t => string = "protocol";

[@bs.get] external readyState: t => string = "readyState";

let bufferedamountlow: PWA_EventType.t(t, PWA_Event.t) =
  PWA_EventType.unsafe("bufferedamountlow");

/* name clash with close method, just use string version of addEventListener */
// let closeEvent: PWA_EventType.t(t, PWA_Event.t) = PWA_EventType.unsafe("close");

let error: PWA_EventType.t(t, PWA_ErrorEvent.t) =
  PWA_EventType.unsafe("error");

let message: PWA_EventType.t(t, PWA_MessageEvent.t) =
  PWA_EventType.unsafe("message");

let open_: PWA_EventType.t(t, PWA_Event.t) = PWA_EventType.unsafe("open");

[@bs.send] external close: t => unit = "close";

[@bs.send]
external send:
  (
    t,
    [@bs.unwrap] [
      | `String(string)
      | `Blob(FileReader.Blob.t)
      | `ArrayBuffer(Js.Typed_array.ArrayBuffer.t)
      | `Int8Array(Js.Typed_array.Int8Array.t)
      | `Uint8Array(Js.Typed_array.Uint8Array.t)
      | `Uint8ClampedArray(Js.Typed_array.Uint8ClampedArray.t)
      | `Int16Array(Js.Typed_array.Int16Array.t)
      | `Uint16Array(Js.Typed_array.Uint16Array.t)
      | `Int32Array(Js.Typed_array.Int32Array.t)
      | `Uint32Array(Js.Typed_array.Uint32Array.t)
      | `Float32Array(Js.Typed_array.Float32Array.t)
      | `Float64Array(Js.Typed_array.Float64Array.t)
      | `DataView(Js.Typed_array.DataView.t)
    ]
  ) =>
  unit =
  "send";
