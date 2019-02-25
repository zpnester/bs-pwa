type t;

include (module type of PWA_HTMLMediaElement.Make({ type nonrec t = t; }));


let videoWidth: t => int;
let videoHeight: t => int;

let asVideoElement: Dom.element => option(t);

let createElement: PWA_Document.t => t;