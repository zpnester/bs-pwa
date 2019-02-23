
module Make = (M: { type t; }) => {
  [@bs.send]
  external addEventListener: (M.t, PWA_EventType.t(M.t, 'a), 'a => unit) => unit =
    "addEventListener";

  [@bs.send]
  external removeEventListener: (M.t, PWA_EventType.t(M.t, 'a), 'a => unit) => unit =
    "removeEventListener";

 
   /* [@bs.send]
  external addEventListener2: (M.t, PWA_EventType.t2(M.t, 'a, 'b), ('a, 'b) => unit) => unit =
    "addEventListener";

  [@bs.send]
  external removeEventListener2: (M.t, PWA_EventType.t2(M.t, 'a, 'b), ('a, 'b) => unit) => unit =
    "removeEventListener";*/
};

