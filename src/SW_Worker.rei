include (module type of SW_AbstractWorker);

open SW_Types;

let postMessage: (t, 'a, ~transfer: array(transferable)=?, unit) => unit;
let terminate: t => unit;

let messageerror: SW_EventType.t(unit);
let message: SW_EventType.t(SW_MessageEvent.t);