type t;

[@bs.get] [@bs.return nullable] external files_: t => option(PWA_FileList.t) = "files";
let files = self => self->files_ ->Belt.Option.map(PWA_FileList.toArray);

[@bs.get] external value: t => string = "value";

[@bs.set] external onchange: (t, Dom.event => unit) => unit = "onchange";

let asInputElement_: Dom.element => Js.Nullable.t(t) = [%raw {|
function(element) {
  return (element instanceof HTMLInputElement) ? element : null;
}
|}];
let asInputElement = elem => elem->asInputElement_ ->Js.Nullable.toOption;