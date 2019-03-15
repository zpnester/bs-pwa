type t;

// TODO transferList

[@bs.send] external postMessage: (t, 'a) => unit = "postMessage";
