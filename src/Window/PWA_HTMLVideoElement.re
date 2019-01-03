type t;

/* As of November 2017, browsers only support MediaStream */
[@bs.set] external setSrcObject: (t, PWA_MediaStream.t) => unit = "srcObject";

[@bs.send] external play: t => Js.Promise.t(unit) = "play";
[@bs.send] external pause: t => unit = "pause";

[@bs.get] external videoWidth: t => float = "videoWidth";
[@bs.get] external videoHeight: t => float = "videoHeight";

let asVideoElement_: Dom.element => Js.Nullable.t(t) = [%raw
  {|
function(element) {
  return (element instanceof HTMLVideoElement) ? element : null;
}
|}
];
let asVideoElement = elem => elem->asVideoElement_->Js.Nullable.toOption;