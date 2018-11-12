type t;

open SW_Types;

let id: t => string;
let type_: t => string;
let url: t => string;

let postMessage: (t, 'a, ~transfer: array(transferable)=?, unit) => unit;