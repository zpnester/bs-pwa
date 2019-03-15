type t;

include (module type of
  PWA_DomElementLike.Make({
    type nonrec t = t;
  }));
include (module type of
  PWA_HTMLElement.Make({
    type nonrec t = t;
  }));

let files: t => option(array(FileReader.File.t));

[@bs.get] external value: t => string = "value";
[@bs.set] external setValue: (t, string) => unit = "value";

let asInputElement: Dom.element => option(t);

let createElement: PWA_Document.t => t;
