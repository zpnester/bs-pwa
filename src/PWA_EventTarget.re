
module Make = (M: { type t; }) => {
  [@bs.send]
  external addEventListener: (M.t, PWA_EventType.t(M.t, 'e), 'e => unit) => unit =
    "addEventListener";

  [@bs.send]
  external removeEventListener: (M.t, PWA_EventType.t(M.t, 'e) => unit) => unit =
    "removeEventListener";
};