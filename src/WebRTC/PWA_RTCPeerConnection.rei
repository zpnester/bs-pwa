type t;

include (module type of
  PWA_EventTarget.Make({
    type nonrec t = t;
  }));

module Configuration: {
  type t;

  let make:
    (
      ~bundlePolicy: string=?,
      ~certificates: array(PWA_RTCCertificate.t)=?,
      ~iceCandidatePoolSize: int=?,
      ~iceServers: array(PWA_RTCIceServer.t)=?,
      ~iceTransportPolicy: string=?,
      ~peerIdentity: string=?,
      ~rtcpMuxPolicy: string=?,
      unit
    ) =>
    t;

  let bundlePolicy: t => option(string);

  let certificates: t => option(array(PWA_RTCCertificate.t));

  let iceCandidatePoolSize: t => option(int);

  let iceServers: t => option(array(PWA_RTCIceServer.t));

  let iceTransportPolicy: t => option(string);

  let peerIdentity: t => option(string);

  let rtcpMuxPolicy: t => option(string);
};

let make: (~config: Configuration.t=?, unit) => t;

let canTrickleIceCandidates: t => option(bool);

[@bs.get] external connectionState: t => string = "connectionState";

let currentLocalDescription: t => option(PWA_RTCSessionDescription.t);
let currentRemoteDescription: t => option(PWA_RTCSessionDescription.t);
let iceConnectionState: t => string;
let iceGatheringState: t => string;
let localDescription: t => option(PWA_RTCSessionDescription.t);
let pendingLocalDescription: t => option(PWA_RTCSessionDescription.t);
let remoteDescription: t => option(PWA_RTCSessionDescription.t);
let pendingRemoteDescription: t => option(PWA_RTCSessionDescription.t);
let signalingState: t => string;

let connectionstatechange: PWA_EventType.t(t, PWA_Event.t);

let datachannel: PWA_EventType.t(t, {. "channel": PWA_RTCDataChannel.t});

let icecandidate: PWA_EventType.t(t, PWA_RTCPeerConnectionIceEvent.t);

let iceconnectionstatechange: PWA_EventType.t(t, PWA_Event.t);

let icegatheringstatechange: PWA_EventType.t(t, PWA_Event.t);

let identityresult: PWA_EventType.t(t, {. "assertion": string});

let idpassertionerror:
  PWA_EventType.t(
    t,
    {
      .
      "idp": string,
      "loginUrl": Js.Nullable.t(string),
      "protocol": string,
    },
  );

let idpvalidationerror:
  PWA_EventType.t(
    t,
    {
      .
      "idp": string,
      "loginUrl": Js.Nullable.t(string),
      "protocol": string,
    },
  );

let negotiationneeded: PWA_EventType.t(t, PWA_Event.t);

let peeridentity: PWA_EventType.t(t, PWA_Event.t);

let signalingstatechange: PWA_EventType.t(t, PWA_Event.t);

let track:
  PWA_EventType.t(
    t,
    {
      .
      "receiver": PWA_RTCRtpReceiver.t,
      "streams": array(PWA_MediaStream.t),
      "track": PWA_MediaStreamTrack.t,
      "transceiver": PWA_RTCRtpTransceiver.t,
    },
  );
let addIceCandidate: (t, PWA_RTCIceCandidate.init) => Js.Promise.t(unit);

/*let addStream: (t, PWA_MediaStream.t) => unit; */

let addTrack:
  (t, PWA_MediaStreamTrack.t, PWA_MediaStream.t) => PWA_RTCRtpSender.t;

let addTrack2:
  (t, PWA_MediaStreamTrack.t, PWA_MediaStream.t, PWA_MediaStream.t) =>
  PWA_RTCRtpSender.t;

let close: t => unit;

let createAnswer:
  (t, ~voiceActivityDetection: bool=?, unit) =>
  Js.Promise.t(PWA_RTCSessionDescription.init);

let createDataChannel:
  (t, ~label: string, ~init: PWA_RTCDataChannel.Init.t=?, unit) =>
  PWA_RTCDataChannel.t;

let createOffer:
  (t, ~iceRestart: bool=?, ~voiceActivityDetection: bool=?, unit) =>
  Js.Promise.t(PWA_RTCSessionDescription.init);

/* both seems to work */
// [@bs.val] [@bs.scope "RTCPeerConnection"]
// external generateCertificate:
//   ([@bs.unwrap] [ | `String(string) | `Object(Js.t({..}))]) =>
//   Js.Promise.t(PWA_RTCCertificate.t) =
//   "generateCertificate";

let generateCertificate:
  [ | `String(string) | `Object(Js.t({..}))] =>
  Js.Promise.t(PWA_RTCCertificate.t);

let getConfiguration: t => Configuration.t;

let getReceivers: t => array(PWA_RTCRtpReceiver.t);

let getSenders: t => array(PWA_RTCRtpSender.t);

let getStats:
  (t, ~selector: PWA_MediaStream.t=?, unit) => Js.Promise.t(Js.t({..}));

let removeTrack: (t, PWA_RTCRtpSender.t) => unit;

let setConfiguration: (t, Configuration.t) => unit;

let setLocalDescription:
  (t, PWA_RTCSessionDescription.init) => Js.Promise.t(unit);

let setRemoteDescription:
  (t, PWA_RTCSessionDescription.init) => Js.Promise.t(unit);
