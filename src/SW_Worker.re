include SW_AbstractWorker;

open SW_Types;

[@bs.send]
external postMessage_: (t, 'a, Js.Nullable.t(array(transferable))) => unit =
  "postMessage";

let postMessage =
    (self: t, message: 'a, ~transfer: option(array(transferable))=?, ()) =>
  self->postMessage_(message, Js.Nullable.fromOption(transfer));

[@bs.send] external terminate: t => unit = "terminate";

let messageerror: SW_EventType.t(unit) = SW_EventType.unsafe("messageerror");
let message: SW_EventType.t(SW_MessageEvent.t) =
  SW_EventType.unsafe("message");