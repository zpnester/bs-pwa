type t = PWA_SW__.swGlobalScope;

include PWA_EventTarget.Make({
  type nonrec t = t;
});

[@bs.send] external importScripts: (t, string) => unit = "importScripts";

let self = PWA_SW__.selfSw;
