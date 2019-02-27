type t;

include PWA_HTMLMediaElement.Make({ type nonrec t = t; });


[@bs.get] external videoWidth: t => int = "videoWidth";
[@bs.get] external videoHeight: t => int = "videoHeight";


let asVideoElement_: Dom.element => Js.Nullable.t(t) = [%raw
  {|
function(element) {
  return (element instanceof HTMLVideoElement) ? element : null;
}
|}
];
let asVideoElement = elem => elem->asVideoElement_->Js.Nullable.toOption;

let createElement = doc => doc->PWA_Document.createElement("video")
	->asVideoElement->Belt.Option.getExn;