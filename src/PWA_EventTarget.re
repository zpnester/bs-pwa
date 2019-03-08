
module Make = (M: { type t; }) => {
  [@bs.send]
  external addEventListener: (M.t, PWA_EventType.t(M.t, 'a), 'a => unit) => unit =
    "addEventListener";

  [@bs.send]
  external removeEventListener: (M.t, PWA_EventType.t(M.t, 'a), 'a => unit) => unit =
    "removeEventListener";
    

    [@bs.send]
  external addEventListener_: (M.t, string, PWA_Event.t => unit) => unit =
    "addEventListener";

  [@bs.send]
  external removeEventListener_: (M.t, string, PWA_Event.t => unit) => unit =
    "removeEventListener";

 
};

