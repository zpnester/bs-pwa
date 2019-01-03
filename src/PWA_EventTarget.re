type t;


[@bs.send]
external addEventListener: (t, PWA_EventType.t(t, 'e), 'e => unit) => unit =
  "addEventListener";

[@bs.send]
external removeEventListener: (t, PWA_EventType.t(t, 'e) => unit) => unit =
  "removeEventListener";