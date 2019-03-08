exception CanvasError;

type t;

include (module type of
  PWA_DomElementLike.Make({
    type nonrec t = t;
  }));

let width: t => int;
let height: t => int;

let setWidth: (t, int) => unit;
let setHeight: (t, int) => unit;

let captureStream: (t, ~frameRate: float=?, unit) => PWA_MediaStream.t;

let getContext2d: t => PWA_CanvasRenderingContext2D.t;
let getContextWebgl: t => PWA_WebGLRenderingContext.t;

let asCanvasElement: Dom.element => option(t);

let toDataURL: (t, ~type_: string=?, ~quality: float=?, unit) => string;

let toBlob:
  (t, ~type_: string=?, ~quality: float=?, unit) =>
  Js.Promise.t(FileReader.Blob.t);

let createElement: PWA_Document.t => t;
