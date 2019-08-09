module Make = (M: {type t;}) => {
  include PWA_DomElementLike.Make(M);
  include PWA_HTMLElement.Make(M);

  /* setSrcObject: As of November 2017, browsers only support MediaStream */

  [@bs.get] [@bs.return nullable]
  external srcObject: M.t => option(PWA_MediaStream.t) = "srcObject";

  [@bs.set]
  external setSrcObject_: (M.t, Js.Null.t(PWA_MediaStream.t)) => unit =
    "srcObject";

  let setSrcObject = (self, stream) =>
    setSrcObject_(self, stream->Js.Null.fromOption);

  [@bs.get] external src: M.t => string = "src";
  [@bs.set] external setSrc: (M.t, string) => unit = "src";

  // audioTracks

  [@bs.get] external playbackRate: M.t => float = "playbackRate";
  [@bs.set] external setPlaybackRate: (M.t, float) => unit = "playbackRate";

  [@bs.get] external autoplay: M.t => bool = "autoplay";
  [@bs.set] external setAutoplay: (M.t, bool) => unit = "autoplay";

  [@bs.get] external buffered: M.t => bool = "autoplay";

  [@bs.get] external paused: M.t => bool = "paused";

  [@bs.get] external muted: M.t => bool = "muted";
  [@bs.set] external setMuted: (M.t, bool) => unit = "muted";

  [@bs.get] external loop: M.t => bool = "loop";

  [@bs.get] external volume: M.t => float = "volume";

  [@bs.send] external play: M.t => Js.Promise.t(unit) = "play";
  [@bs.send] external pause: M.t => unit = "pause";
  [@bs.send] external canPlayType: (M.t, string) => string = "canPlayType";
  [@bs.send]
  external captureStream: M.t => PWA_MediaStream.t = "captureStream";
};