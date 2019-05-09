type t = PWA__.messageEvent;

include PWA_Event.Make({
  type nonrec t = t;
});

type message_source;

[@bs.get] external data: t => Js.Json.t = "data";
[@bs.get] external origin: t => string = "origin";
[@bs.get] external lastEventId: t => string = "lastEventId";
[@bs.get] external source: t => message_source = "source";
[@bs.get] external ports: t => array(PWA_MessagePort.t) = "ports";