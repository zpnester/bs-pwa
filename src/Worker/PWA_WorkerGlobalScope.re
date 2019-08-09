module Make = (M: {type t;}) => {
  include PWA_EventTarget.Make(M);
  include PWA_WindowOrWorkerGlobalScope.Make(M);

  [@bs.send] external importScripts: (M.t, string) => unit = "importScripts";
  // TODO navigator
  // TODO location
};