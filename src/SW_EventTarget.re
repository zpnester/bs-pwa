type t;

[@bs.send]
external addEventListener: (t, SW_EventType.t(t, 'e), 'e => unit) => unit =
  "addEventListener";

[@bs.send]
external removeEventListener: (t, SW_EventType.t(t, 'e) => unit) => unit =
  "removeEventListener";