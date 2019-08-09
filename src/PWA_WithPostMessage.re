open PWA__;

module Make = (M: {type t;}) => {
  [@bs.send] external postMessage: (M.t, 'message) => unit = "postMessage";

  [@bs.send]
  external postMessage2: (M.t, 'message, array(PWA_Transferable.t)) => unit =
    "postMessage";
};

module Make2 = (M: {type t;}) => {
  include Make(M);

  let message: PWA_EventType.t(M.t, messageEvent) =
    PWA_EventType.unsafe("message");

  // TODO test
  let messageerror: PWA_EventType.t(M.t, messageEvent) =
    PWA_EventType.unsafe("messageerror");
};