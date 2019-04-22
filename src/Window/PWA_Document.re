type t = Dom.document;

include PWA_EventTarget.Make({
  type nonrec t = t;
});

// TODO public, rename?
[@bs.send]
external querySelectorAll_: (t, string) => Js.Array.array_like(Dom.element) =
  "querySelectorAll";
  
let querySelectorAll = (self, selectors) =>
  querySelectorAll_(self, selectors)->Js.Array.from;

[@bs.send] [@bs.return nullable]
external querySelector: (t, string) => option(Dom.element) = "querySelector";

[@bs.send] [@bs.return nullable]
external getElementById: (t, string) => option(Dom.element) =
  "getElementById";

[@bs.send]
external createElement: (t, string) => Dom.element = "createElement";
