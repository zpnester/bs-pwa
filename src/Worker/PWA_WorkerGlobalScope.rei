type t;

include (module type of
  PWA_EventTarget.Make({
    type nonrec t = t;
  }));

[@bs.send] external importScripts: (t, string) => unit = "importScripts";

let self_: t;

// TODO navigator
// TODO location

include (module type of
  PWA_WindowOrWorkerGlobalScope.Make({
    type nonrec t = t;
  }));