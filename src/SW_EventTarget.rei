type t;

type event;

let addEventListener: (t, SW_EventType.t('a), 'a => unit) => unit;
let dispatchEvent: (t, event) => bool;
let removeEventListener: (t, 'a => unit) => unit;