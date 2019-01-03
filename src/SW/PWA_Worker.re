type t;

/* transferable omitted */
[@bs.send] external postMessage: (t, 'a) => unit = "postMessage";