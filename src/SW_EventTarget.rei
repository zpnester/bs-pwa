type t;

let addEventListener: (t, SW_EventType.t(t, 'e), 'e => unit) => unit;
let removeEventListener: (t, SW_EventType.t(t, 'e) => unit) => unit;