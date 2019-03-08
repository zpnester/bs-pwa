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

let value: t => string;
let setValue: (t, string) => unit;

let placeholder: t => string;
let setPlaceholder: (t, string) => unit;

/* let change: PWA_EventType.t(t, Dom.event); */

let asInputElement: Dom.element => option(t);

let createElement: PWA_Document.t => t;
