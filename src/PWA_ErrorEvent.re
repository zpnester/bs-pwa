type t;

include PWA_Event.Make({
  type nonrec t = t;
});

/* TODO test */

[@bs.get] external message: t => string = "message";
[@bs.get] external filename: t => string = "filename";
[@bs.get] external lineno: t => int = "lineno";
[@bs.get] external colno: t => int = "colno";
[@bs.get] external error_: t => Js.Null.t(Js.Json.t) = "error";
let error = self => error_(self)->Js.Null.toOption;
