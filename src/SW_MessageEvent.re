include SW_Event;

/* TODO test */
[@bs.get] external data: t => SW_Types.any = "data";
[@bs.get] external origin: t => string = "origin";
[@bs.get] external lastEventId: t => string = "lastEventId";
[@bs.get] external source: t => SW_Types.any = "source";
[@bs.get] external ports: t => array(SW_MessagePort.t) = "source";