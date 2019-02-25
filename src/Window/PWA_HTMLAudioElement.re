type t;

include PWA_HTMLMediaElement.Make({ type nonrec t = t; });

let asAudioElement_: Dom.element => Js.Nullable.t(t) = [%raw
  {|
function(element) {
  return (element instanceof HTMLAudioElement) ? element : null;
}
|}
];
let asAudioElement = elem => elem->asAudioElement_->Js.Nullable.toOption;

let createElement: PWA_Document.t => t = [%raw
  {|
    function(document) {
        return document.createElement("audio");
    }
|}
];