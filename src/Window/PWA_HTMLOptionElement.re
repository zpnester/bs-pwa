type t;

include PWA_HTMLElement.Make({ type nonrec t = t; });



[@bs.get] external value: t => string = "value";
[@bs.set] external setValue: (t, string) => unit = "value";


let asOptionElement_: Dom.element => Js.Nullable.t(t) = [%raw {|
function(element) {
  return (element instanceof HTMLOptionElement) ? element : null;
}
|}];
let asOptionElement = elem => elem->asOptionElement_ ->Js.Nullable.toOption;

let createElement = doc => doc->PWA_Document.createElement("option")
  ->asOptionElement->Belt.Option.getExn;