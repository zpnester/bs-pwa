type t;

/* TODO */
[@bs.send]
external getUserMediaUnsafe:
  (t, Js.t({..})) => Js.Promise.t(PWA_MediaStream.t) =
  "getUserMedia";