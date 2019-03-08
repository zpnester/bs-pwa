type t;

include PWA_Event.Make({
  type nonrec t = t;
});

[@bs.get] [@bs.return nullable]
external candidate: t => option(PWA_RTCIceCandidate.t) = "candidate";
