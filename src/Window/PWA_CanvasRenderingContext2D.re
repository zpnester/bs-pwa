type t;


// CSSImageValue, an HTMLImageElement, an SVGImageElement, an HTMLVideoElement,
// an HTMLCanvasElement, an ImageBitmap, or an OffscreenCanvas

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
