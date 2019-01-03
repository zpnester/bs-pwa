type t;

[@bs.set]
external setSrcObject:
  (
    t,
    [@bs.unwrap] [
      | `MediaStream(PWA_MediaStream.t)
      | `Blob(FileReader.Blob.t)
    ]
  ) =>
  unit =
  "srcObject";

[@bs.send] external play: t => Js.Promise.t(unit) = "play";
[@bs.send] external pause: t => unit = "pause";

[@bs.get] external videoWidth: t => float = "videoWidth";
[@bs.get] external videoHeight: t => float = "videoHeight";

external fromDomUnsafe: Dom.element => t = "%identity";