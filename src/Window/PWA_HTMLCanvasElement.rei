exception CanvasError;

type t;

let width: t => float;
let height: t => float;

let setWidth: (t, float) => unit;
let setHeight: (t, float) => unit;

let getContext2d: t => PWA_CanvasRenderingContext2D.t;

let asCanvasElement: Dom.element => option(t);

let toDataURL: t => string;

let toBlob: t => Js.Promise.t(FileReader.Blob.t);

let create: PWA_WindowGlobalScope.t => t;