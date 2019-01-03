type t;

[@bs.send] external postMessage: (t, 'a) => unit = "postMessage";