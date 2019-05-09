include PWA_WorkerGlobalScope;

[@bs.get] external name: t => string = "name";

[@bs.send] external close: t => unit = "close";

include PWA_WithPostMessage.Make({
  type nonrec t = t;
});