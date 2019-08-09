exception CanvasError;

type t;

include PWA_DomElementLike.Make({
  type nonrec t = t;
});

[@bs.get] external width: t => int = "width";
[@bs.get] external height: t => int = "height";

[@bs.set] external setWidth: (t, int) => unit = "width";
[@bs.set] external setHeight: (t, int) => unit = "height";

// MDN: If the contextType doesn't match a possible drawing context, null is returned.
[@bs.send] [@bs.return nullable]
external getContext: (t, string) => option(PWA__.canvasContext) =
  "getContext";

[@bs.send] [@bs.return nullable]
external getContext2: (t, string, Js.t({.})) => option(PWA__.canvasContext) =
  "getContext";

[@bs.send]
external getContext2d: (t, [@bs.as "2d"] _) => PWA_CanvasRenderingContext2D.t =
  "getContext";

[@bs.send]
external getContext2d1:
  (t, [@bs.as "2d"] _, Js.t({.})) => PWA_CanvasRenderingContext2D.t =
  "getContext";

[@bs.send] external captureStream: t => PWA_MediaStream.t = "captureStream";

[@bs.send]
external captureStream1: (t, ~framerate: float) => PWA_MediaStream.t =
  "captureStream";

[@bs.send] external toDataURL: t => string = "toDataURL";

[@bs.send] external toDataURL1: (t, ~type_: string) => string = "toDataURL";

[@bs.send]
external toDataURL2: (t, ~type_: string, ~quality: float) => string =
  "toDataURL";

// toBlob is not available in old MS Edge

[@bs.send]
external toBlob1_: (t, Js.Nullable.t(FileReader.Blob.t) => unit) => unit =
  "toBlob";

[@bs.send]
external toBlob2_:
  (t, Js.Nullable.t(FileReader.Blob.t) => unit, ~type_: string) => unit =
  "toBlob";

[@bs.send]
external toBlob3_:
  (
    t,
    Js.Nullable.t(FileReader.Blob.t) => unit,
    ~type_: string,
    ~quality: float
  ) =>
  unit =
  "toBlob";

let toBlob2 = (self, ~type_, ~quality) => {
  Js.Promise.make((~resolve, ~reject) =>
    self->toBlob3_(~type_, ~quality, blob =>
      switch (blob->Js.Nullable.toOption) {
      | None => reject(. CanvasError)
      | Some(blob) => resolve(. blob)
      }
    )
  );
};

let toBlob1 = (self, ~type_) => {
  Js.Promise.make((~resolve, ~reject) =>
    self->toBlob2_(~type_, blob =>
      switch (blob->Js.Nullable.toOption) {
      | None => reject(. CanvasError)
      | Some(blob) => resolve(. blob)
      }
    )
  );
};

let toBlob = self => {
  Js.Promise.make((~resolve, ~reject) =>
    self->toBlob1_(blob =>
      switch (blob->Js.Nullable.toOption) {
      | None => reject(. CanvasError)
      | Some(blob) => resolve(. blob)
      }
    )
  );
};

let asCanvasElement: Dom.element => option(t) = [%raw
  {|
function(element) {
  return (element instanceof HTMLCanvasElement) ? element : undefined;
}
|}
];

let createElement = doc =>
  doc
  ->PWA_Document.createElement("canvas")
  ->asCanvasElement
  ->Belt.Option.getExn;