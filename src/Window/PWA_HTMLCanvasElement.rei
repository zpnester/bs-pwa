exception CanvasError;

type t;

let width: t => int;
let height: t => int;

let setWidth: (t, int) => unit;
let setHeight: (t, int) => unit;

let getContext2d: t => PWA_CanvasRenderingContext2D.t;

let asCanvasElement: Dom.element => option(t);

let toDataURL: t => string;

let toBlob: t => Js.Promise.t(FileReader.Blob.t);

let create: PWA_WindowGlobalScope.t => t;