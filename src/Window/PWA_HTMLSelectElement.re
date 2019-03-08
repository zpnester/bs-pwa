type t;

include PWA_DomElementLike.Make({
	type nonrec t = t;
});
include PWA_HTMLElement.Make({
	type nonrec t = t;
});

[@bs.get] external disabled: t => bool = "disabled";
[@bs.set] external setDisabled: (t, bool) => unit = "disabled";

[@bs.get] external selectedIndex: t => int = "selectedIndex";
[@bs.set] external setSelectedIndex: (t, int) => unit = "selectedIndex";



/* TODO array like of NODES or OPTIONS? */
[@bs.get] external options_: t => Js.Array.array_like(PWA_HTMLOptionElement.t) = "options";
let options = self => {
    options_(self)->Js.Array.from
}


let asSelectElement_: Dom.element => Js.Nullable.t(t) = [%raw {|
function(element) {
  return (element instanceof HTMLSelectElement  ) ? element : null;
}
|}];
let asSelectElement = elem => elem->asSelectElement_ ->Js.Nullable.toOption;

let createElement = doc => doc->PWA_Document.createElement("select")
  ->asSelectElement->Belt.Option.getExn;