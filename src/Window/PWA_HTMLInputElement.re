open FileReader;

type t;

include PWA_DomElementLike.Make({
	type nonrec t = t;
});
include PWA_HTMLElement.Make({
	type nonrec t = t;
});

[@bs.get] [@bs.return nullable] external files_: t => option(Js.Array.array_like(File.t)) = "files";
let files = self => self->files_ ->Belt.Option.map(Js.Array.from);

[@bs.get] external value: t => string = "value";
[@bs.set] external setValue: (t, string) => unit = "value";

/* let change: PWA_EventType.t(t, Dom.event) = PWA_EventType.unsafe("change");
*/

let asInputElement_: Dom.element => Js.Nullable.t(t) = [%raw {|
function(element) {
  return (element instanceof HTMLInputElement) ? element : null;
}
|}];
let asInputElement = elem => elem->asInputElement_ ->Js.Nullable.toOption;

let createElement = doc => doc->PWA_Document.createElement("input")
  ->asInputElement->Belt.Option.getExn;