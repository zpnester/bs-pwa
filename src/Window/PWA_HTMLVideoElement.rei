type t;

let src: t => string;
let setSrc: (t, string) => unit;

let srcObject: t => option(PWA_MediaStream.t);
let setSrcObject: (t, option(PWA_MediaStream.t)) => unit;

let play: t => Js.Promise.t(unit);
let pause: t => unit;

let videoWidth: t => float;
let videoHeight: t => float;

let asVideoElement: Dom.element => option(t);