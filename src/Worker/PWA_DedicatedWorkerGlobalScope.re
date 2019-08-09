type t;

include PWA_WorkerGlobalScope.Make({
  type nonrec t = t;
});

include PWA_WithPostMessage.Make({
  type nonrec t = t;
});

[@bs.get] external name: t => string = "name";

[@bs.send] external close: t => unit = "close";