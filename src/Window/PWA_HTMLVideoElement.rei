type t;

let setSrcObject: (t, PWA_MediaStream.t) => unit;

let play: t => Js.Promise.t(unit);
let pause: t => unit;

let videoWidth: t => float;
let videoHeight: t => float;

let asVideoElement: Dom.element => option(t);