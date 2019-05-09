type t = Dom.errorEvent;

include PWA_Event.Make({
  type nonrec t = t;
});

/* TODO test */

[@bs.get] external message: t => string = "message";
[@bs.get] external filename: t => string = "filename";
[@bs.get] external lineno: t => int = "lineno";
[@bs.get] external colno: t => int = "colno";
[@bs.get] [@bs.return nullable]
external error: t => option(Js.Json.t) = "error";