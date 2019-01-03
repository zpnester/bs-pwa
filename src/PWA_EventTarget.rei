type t;

let addEventListener: (t, PWA_EventType.t(t, 'e), 'e => unit) => unit;
let removeEventListener: (t, PWA_EventType.t(t, 'e) => unit) => unit;