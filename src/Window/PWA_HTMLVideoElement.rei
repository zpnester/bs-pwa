type t;

include (module type of
  PWA_HTMLMediaElement.Make({
    type nonrec t = t;
  }));

[@bs.get] external videoWidth: t => int = "videoWidth";
[@bs.get] external videoHeight: t => int = "videoHeight";

let asVideoElement: Dom.element => option(t);

let createElement: PWA_Document.t => t;