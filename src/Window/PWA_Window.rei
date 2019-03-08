type t;

include (module type of PWA_EventTarget.Make({ type nonrec t = t; }));


[@bs.val] external self: t = "self";
[@bs.val] external window: t = "window";

let navigator: t => PWA_Navigator.t;
let document: t => PWA_Document.t;

let alert: (t, string) => unit;
let alertAny: (t, 'a) => unit;