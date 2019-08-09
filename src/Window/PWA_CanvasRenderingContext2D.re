type t;

let asCanvasRenderingContext2D: PWA__.canvasContext => t = [%raw
  {|
function(context) {
  if (context instanceof CanvasRenderingContext2D) {
    return context
  }
}
|}
];

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