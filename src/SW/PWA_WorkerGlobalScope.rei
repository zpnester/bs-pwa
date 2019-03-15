type t = PWA_SW__.swGlobalScope;

include (module type of
  PWA_EventTarget.Make({
    type nonrec t = t;
  }));

[@bs.send] external importScripts: (t, string) => unit = "importScripts";

let self: t;
