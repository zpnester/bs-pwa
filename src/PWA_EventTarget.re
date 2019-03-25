type t;

module Make_ = (M: {type t;}) => {
  [@bs.send]
  external addEventListener_: (M.t, string, PWA_Event.t => unit) => unit =
    "addEventListener";

  [@bs.send]
  external removeEventListener_: (M.t, string, PWA_Event.t => unit) => unit =
    "removeEventListener";
};

module Make = (M: {type t;}) => {
  [@bs.send]
  external addEventListener:
    (M.t, PWA_EventType.t(M.t, 'a), 'a => unit) => unit =
    "addEventListener";

  [@bs.send]
  external removeEventListener:
    (M.t, PWA_EventType.t(M.t, 'a), 'a => unit) => unit =
    "removeEventListener";

  include Make_(M);
};

// raw event target has only string version, includers include everything
include Make_({
  type nonrec t = t;
});

// ctor - bad browser support
