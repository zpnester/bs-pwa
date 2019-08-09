type t;

include PWA_DomElementLike.Make({
  type nonrec t = t;
});
include PWA_HTMLElement.Make({
  type nonrec t = t;
});

[@bs.get] external disabled: t => bool = "disabled";
[@bs.set] external setDisabled: (t, bool) => unit = "disabled";

let asButtonElement: Dom.element => option(t) = [%raw
  {|
function(element) {
  if (element instanceof HTMLButtonElement) {
    return element;
  }
}
|}
];

let createElement = doc =>
  doc
  ->PWA_Document.createElement("button")
  ->asButtonElement
  ->Belt.Option.getExn;