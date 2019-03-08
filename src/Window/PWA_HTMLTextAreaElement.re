
type t;

include PWA_DomElementLike.Make({
	type nonrec t = t;
});
include PWA_HTMLElement.Make({
	type nonrec t = t;
});

[@bs.get] external disabled: t => bool = "disabled";
[@bs.set] external setDisabled: (t, bool) => unit = "disabled";

[@bs.get] external value: t => string = "value";
[@bs.set] external setValue: (t, string) => unit = "value";

[@bs.get] external placeholder: t => string = "placeholder";
[@bs.set] external setPlaceholder: (t, string) => unit = "placeholder";


let asTextAreaElement_: Dom.element => Js.Nullable.t(t) = [%raw {|
function(element) {
  return (element instanceof HTMLTextAreaElement) ? element : null;
}
|}];
let asTextAreaElement = elem => elem->asTextAreaElement_ ->Js.Nullable.toOption;

let createElement = doc => doc->PWA_Document.createElement("textarea")
  ->asTextAreaElement->Belt.Option.getExn;