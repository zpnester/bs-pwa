type t = PWA__.messagePort;

include PWA_WithPostMessage.Make({
  type nonrec t = t;
});

[@bs.send] external close: t => unit = "close";
[@bs.send] external start: t => unit = "start";