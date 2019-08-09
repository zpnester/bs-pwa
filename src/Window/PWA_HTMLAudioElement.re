type t;

include PWA_HTMLMediaElement.Make({
  type nonrec t = t;
});

let asAudioElement: Dom.element => option(t) = [%raw
  {|
function(element) {
  return (element instanceof HTMLAudioElement) ? element : undefined;
}
|}
];

let createElement = doc =>
  doc
  ->PWA_Document.createElement("audio")
  ->asAudioElement
  ->Belt.Option.getExn;