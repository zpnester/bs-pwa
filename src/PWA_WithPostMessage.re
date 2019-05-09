open PWA__;

module Make = (M: {type t;}) => {
  let message: PWA_EventType.t(M.t, messageEvent) =
    PWA_EventType.unsafe("message");

  // TODO test
  let messageerror: PWA_EventType.t(M.t, messageEvent) =
    PWA_EventType.unsafe("messageerror");

  [@bs.send] external postMessage: (M.t, 'message) => unit = "postMessage";

  [@bs.send]
  external postMessageWithTransferList:
    (M.t, 'message, array(PWA_Transferable.t)) => unit =
    "postMessage";
};