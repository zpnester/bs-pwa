exception CanvasError;

type t;

include (module type of
  PWA_DomElementLike.Make({
    type nonrec t = t;
  }));

[@bs.get] external width: t => int = "width";
[@bs.get] external height: t => int = "height";

[@bs.set] external setWidth: (t, int) => unit = "width";
[@bs.set] external setHeight: (t, int) => unit = "height";

[@bs.send]
external captureStream: (t, ~frameRate: float=?, unit) => PWA_MediaStream.t =
  "captureStream";

let getContext2d: t => PWA_CanvasRenderingContext2D.t;
let getContextWebgl: t => PWA_WebGLRenderingContext.t;

let asCanvasElement: Dom.element => option(t);

[@bs.send]
external toDataURL: (t, ~type_: string=?, ~quality: float=?, unit) => string =
  "toDataURL";

let toBlob:
  (t, ~type_: string=?, ~quality: float=?, unit) =>
  Js.Promise.t(FileReader.Blob.t);

let createElement: PWA_Document.t => t;
