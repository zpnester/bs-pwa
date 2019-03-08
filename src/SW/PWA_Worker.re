type t;

include PWA_EventTarget.Make({ type nonrec t = t; });


/* transferable omitted */
[@bs.send] external postMessage: (t, 'a) => unit = "postMessage";