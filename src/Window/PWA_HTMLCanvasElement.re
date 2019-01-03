exception CanvasError;

type t;

[@bs.get] external width: t => float = "width";
[@bs.get] external height: t => float = "height";

[@bs.set] external setWidth: (t, float) => unit = "width";
[@bs.set] external setHeight: (t, float) => unit = "height";

let getContext2d: t => PWA_CanvasRenderingContext2D.t = [%raw
  {|
function(self) {
    return self.getContext("2d")
}
|}
];
/* let getContext2d = self => {
       getContext2d_(  self)->Js.Nullable.toOption;
   }; */

/* 2 params omitted */
[@bs.send] external toDataURL: t => string = "toDataURL";

let asCanvasElement_: Dom.element => Js.Nullable.t(t) = [%raw {|
    function(element) {
      return (element instanceof HTMLCanvasElement) ? element : null;
    }
|}];
let asCanvasElement = elem => elem->asCanvasElement_ ->Js.Nullable.toOption;

/* TODO */
[@bs.send]
external toBlob_: (t, Js.Nullable.t(FileReader.Blob.t) => unit) => unit =
  "toBlob";

let toBlob = self =>
  Js.Promise.make((~resolve, ~reject) =>
    toBlob_(self, blob =>
      switch (blob->Js.Nullable.toOption) {
      | None => reject(. CanvasError)
      | Some(blob) => resolve(. blob)
      }
    )
  );

let create: PWA_WindowGlobalScope.t => t = [%raw
  {|
    function(window) {
        return window.document.createElement("canvas");
    }
|}
];