type t = Dom.document;

include (module type of PWA_EventTarget.Make({ type nonrec t = t; }));

let querySelectorAll: (t, string) => array(Dom.element);

let querySelector: (t, string) => option(Dom.element);

let getElementById: (t, string) => option(Dom.element);

let createElement: (t, string) => Dom.element;