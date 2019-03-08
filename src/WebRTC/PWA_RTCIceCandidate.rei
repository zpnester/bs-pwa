type t;

/* sort of abstract type, passed from icecandidate event to addIceCandidate */
type init = {
  .
  "candidate": Js.Nullable.t(string),
  "sdpMLineIndex": Js.Nullable.t(int),
  "sdpMid": Js.Nullable.t(string),
  "usernameFragment": Js.Nullable.t(string),
};

let make: (~init: init=?, unit) => t;

let candidate: t => string;
let component: t => string;
let foundation: t => string;
let ip: t => string;
let port: t => int;
let priority: t => float;
let protocol: t => string;
let relatedAddress: t => option(string);
let relatedPort: t => option(int);
let sdpMid: t => option(string);
let sdpMLineIndex: t => option(int);
let tcpType: t => option(string);
let type_: t => string;
let usernameFragment: t => string;
let toJSON: t => init;
