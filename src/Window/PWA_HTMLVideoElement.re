type t;

include PWA_HTMLMediaElement.Make({
  type nonrec t = t;
});

// int
[@bs.get] external videoWidth: t => int = "videoWidth";
[@bs.get] external videoHeight: t => int = "videoHeight";

let asVideoElement: Dom.element => option(t) = [%raw
  {|
function(element) {
  return (element instanceof HTMLVideoElement) ? element : undefined;
}
|}
];

let createElement = doc =>
  doc
  ->PWA_Document.createElement("video")
  ->asVideoElement
  ->Belt.Option.getExn;