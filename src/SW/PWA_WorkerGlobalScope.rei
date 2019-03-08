type t;

include (module type of
  PWA_EventTarget.Make({
    type nonrec t = t;
  }));

let importScripts: (t, string) => unit;

[@bs.val] external self: t = "self";
