type t;

[@bs.get] external src: t => string= "src";
[@bs.set] external setSrc: (t, string) => unit= "src";



/* setSrcObject: As of November 2017, browsers only support MediaStream */

[@bs.get] external srcObject_: t => Js.Null.t(PWA_MediaStream.t) = "srcObject";
let srcObject = self => srcObject_(self)->Js.Null.toOption;

[@bs.set] external setSrcObject_: (t, Js.Null.t(PWA_MediaStream.t)) => unit = "srcObject";
let setSrcObject = (self, stream) => setSrcObject_(self, stream->Js.Null.fromOption);



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