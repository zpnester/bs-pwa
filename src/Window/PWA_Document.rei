type t = Dom.document;

include (module type of
  PWA_EventTarget.Make({
    type nonrec t = t;
  }));

let querySelectorAll: (t, string) => array(Dom.element);

[@bs.send] [@bs.return nullable]
external querySelector: (t, string) => option(Dom.element) = "querySelector";

[@bs.send] [@bs.return nullable]
external getElementById: (t, string) => option(Dom.element) =
  "getElementById";

[@bs.send]
external createElement: (t, string) => Dom.element = "createElement";
