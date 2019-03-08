type t;

[@bs.send]
external getUserMedia: (t, Js.t({..})) => Js.Promise.t(PWA_MediaStream.t) =
  "getUserMedia";
