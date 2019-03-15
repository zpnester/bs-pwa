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

  [@bs.get] [@bs.return nullable]
  external bundlePolicy: t => option(string) = "bundlePolicy";

  [@bs.get] [@bs.return nullable]
  external certificates: t => option(array(PWA_RTCCertificate.t)) =
    "certificates";

  [@bs.get] [@bs.return nullable]
  external iceCandidatePoolSize: t => option(int) = "iceCandidatePoolSize";

  [@bs.get] [@bs.return nullable]
  external iceServers: t => option(array(PWA_RTCIceServer.t)) = "iceServers";

  [@bs.get] [@bs.return nullable]
  external iceTransportPolicy: t => option(string) = "iceTransportPolicy";

  [@bs.get] [@bs.return nullable]
  external peerIdentity_: t => option(string) = "peerIdentity";

  [@bs.get] [@bs.return nullable]
  external rtcpMuxPolicy: t => option(string) = "rtcpMuxPolicy";
};

// constructor, avoid external
let make: (~config: Configuration.t=?, unit) => t;

[@bs.get] [@bs.return nullable]
external canTrickleIceCandidates: t => option(bool) =
  "canTrickleIceCandidates";

[@bs.get] external connectionState: t => string = "connectionState";

[@bs.get] [@bs.return nullable]
external currentLocalDescription: t => option(PWA_RTCSessionDescription.t) =
  "currentLocalDescription";

[@bs.get] [@bs.return nullable]
external currentRemoteDescription: t => option(PWA_RTCSessionDescription.t) =
  "currentRemoteDescription";

[@bs.get] external iceConnectionState: t => string = "iceConnectionState";
[@bs.get] external iceGatheringState: t => string = "iceGatheringState";

[@bs.get] [@bs.return nullable]
external localDescription: t => option(PWA_RTCSessionDescription.t) =
  "localDescription";

[@bs.get] [@bs.return nullable]
external pendingLocalDescription: t => option(PWA_RTCSessionDescription.t) =
  "pendingLocalDescription";
 
[@bs.get] [@bs.return nullable]
external remoteDescription: t => option(PWA_RTCSessionDescription.t) =
  "remoteDescription";

[@bs.get]  [@bs.return nullable]
external pendingRemoteDescription: t => option(PWA_RTCSessionDescription.t) =
  "pendingRemoteDescription";

[@bs.get] external signalingState: t => string = "signalingState";

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

[@bs.send]
external addIceCandidate:
  (t, PWA_RTCIceCandidate.Init.t) => Js.Promise.t(unit) =
  "addIceCandidate";

/*let addStream: (t, PWA_MediaStream.t) => unit; */

[@bs.send]
external addTrack:
  (t, PWA_MediaStreamTrack.t, PWA_MediaStream.t) => PWA_RTCRtpSender.t =
  "addTrack";

[@bs.send]
external addTrack2:
  (t, PWA_MediaStreamTrack.t, PWA_MediaStream.t, PWA_MediaStream.t) =>
  PWA_RTCRtpSender.t =
  "addTrack";

[@bs.send] external close: t => unit = "close";

let createAnswer:
  (t, ~voiceActivityDetection: bool=?, unit) =>
  Js.Promise.t(PWA_RTCSessionDescription.Init.t);

let createDataChannel:
  (t, ~label: string, ~init: PWA_RTCDataChannel.Init.t=?, unit) =>
  PWA_RTCDataChannel.t;

let createOffer:
  (t, ~iceRestart: bool=?, ~voiceActivityDetection: bool=?, unit) =>
  Js.Promise.t(PWA_RTCSessionDescription.Init.t);

// global, avoid external

let generateCertificate:
  [ | `String(string) | `Object(Js.t({..}))] =>
  Js.Promise.t(PWA_RTCCertificate.t);

[@bs.send]
external getConfiguration: t => Configuration.t = "getConfiguration";

[@bs.send]
external getReceivers: t => array(PWA_RTCRtpReceiver.t) = "getReceivers";

[@bs.send] external getSenders: t => array(PWA_RTCRtpSender.t) = "getSenders";

[@bs.send]
external getStats:
  (t, ~selector: PWA_MediaStream.t=?, unit) => Js.Promise.t(Js.t({..})) =
  "getStats";

[@bs.send]
external removeTrack: (t, PWA_RTCRtpSender.t) => unit = "removeTrack";

[@bs.send]
external setConfiguration: (t, Configuration.t) => unit = "setConfiguration";

[@bs.send]
external setLocalDescription:
  (t, PWA_RTCSessionDescription.Init.t) => Js.Promise.t(unit) =
  "setLocalDescription";

[@bs.send]
external setRemoteDescription:
  (t, PWA_RTCSessionDescription.Init.t) => Js.Promise.t(unit) =
  "setRemoteDescription";
