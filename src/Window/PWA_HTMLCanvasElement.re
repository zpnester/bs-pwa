exception CanvasError;

type t;

include PWA_DomElementLike.Make({ type nonrec t = t;});


[@bs.get] external width: t => int = "width";
[@bs.get] external height: t => int = "height";

[@bs.set] external setWidth: (t, int) => unit = "width";
[@bs.set] external setHeight: (t, int) => unit = "height";

let getContext2d: t => PWA_CanvasRenderingContext2D.t = [%raw
  {|
function(self) {
    return self.getContext("2d")
}
|}
];


let getContextWebgl: t => PWA_WebGLRenderingContext.t = [%raw
  {|
function(self) {
    return self.getContext("webgl")
}
|}
];

[@bs.send] external captureStream: (t, ~frameRate: float=?, unit) => PWA_MediaStream.t = "captureStream";



[@bs.send] external toDataURL: (t, ~type_: string=?, ~quality: float=?, unit) => string = "toDataURL";

let asCanvasElement_: Dom.element => Js.Nullable.t(t) = [%raw {|
    function(element) {
      return (element instanceof HTMLCanvasElement) ? element : null;
    }
|}];
let asCanvasElement = elem => elem->asCanvasElement_ ->Js.Nullable.toOption;


[@bs.send]
external toBlob_: (t, Js.Nullable.t(FileReader.Blob.t) => unit, 
    ~type_: string=?, ~quality: float=?, unit) => unit =
  "toBlob";

let toBlob = (self, ~type_=?, ~quality=?, ()) =>
  Js.Promise.make((~resolve, ~reject) =>
    toBlob_(self, ~type_?, ~quality?, blob =>
      switch (blob->Js.Nullable.toOption) {
      | None => reject(. CanvasError)
      | Some(blob) => resolve(. blob)
      }
    , ())
  );

let asCanvasElement_: Dom.element => Js.Nullable.t(t) = [%raw
  {|
function(element) {
  return (element instanceof HTMLCanvasElement) ? element : null;
}
|}
];
let asCanvasElement = elem => elem->asCanvasElement_->Js.Nullable.toOption;

let createElement: PWA_Document.t => t = [%raw
  {|
    function(document) {
        return document.createElement("canvas");
    }
|}
];