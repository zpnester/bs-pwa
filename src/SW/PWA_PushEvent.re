type t;

include PWA_ExtendableEvent.Make({
  type nonrec t = t;
});

[@bs.get] external data: t => PWA_PushMessageData.t = "data";
