type t;

[@bs.get] external id: t => string = "id";
[@bs.get] external ended: t => bool = "ended";
[@bs.get] external active: t => bool = "active";

[@bs.send] external getTracks: t => array(PWA_MediaStreamTrack.t) = "getTracks";
[@bs.send] external getAudioTracks: t => array(PWA_MediaStreamTrack.t) = "getAudioTracks";
[@bs.send] external getVideoTracks: t => array(PWA_MediaStreamTrack.t) = "getVideoTracks";


[@bs.send] [@bs.return nullable] external getTrackById: (t, string) => option(PWA_MediaStreamTrack.t) = "getTrackById";

[@bs.send] external clone: t => t = "clone";

/* addTrack */
/* removeTrack */