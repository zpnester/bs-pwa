type t;

include PWA_DomElementLike.Make({
  type nonrec t = t;
});
include PWA_HTMLElement.Make({
  type nonrec t = t;
});

[@bs.get] external disabled: t => bool = "disabled";
[@bs.set] external setDisabled: (t, bool) => unit = "disabled";

let asButtonElement_: Dom.element => Js.Nullable.t(t) = [%raw
  {|
function(element) {
  return (element instanceof HTMLButtonElement) ? element : null;
}
|}
];
let asButtonElement = elem => elem->asButtonElement_->Js.Nullable.toOption;

let createElement = doc =>
  doc
  ->PWA_Document.createElement("button")
  ->asButtonElement
  ->Belt.Option.getExn;
