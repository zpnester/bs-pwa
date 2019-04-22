type t;

include PWA_EventTarget.Make({
  type nonrec t = t;
});

[@bs.send] external importScripts: (t, string) => unit = "importScripts";

[@bs.val] external self_: t = "self";
