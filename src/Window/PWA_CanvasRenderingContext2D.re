type t;

/* TODO */
[@bs.send]
external drawImage:
  (
    t,
    [@bs.unwrap] [ | `Video(PWA_HTMLVideoElement.t) | `Canvas(t)],
    ~dx: float,
    ~dy: float
  ) =>
  unit =
  "drawImage";
