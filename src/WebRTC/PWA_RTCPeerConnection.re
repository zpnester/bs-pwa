type t;

include PWA_EventTarget.Make({
  type nonrec t = t;
});

module Configuration = {
  type t;

  [@bs.obj]
  external make:
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
    t =
    "";

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

[@bs.new] external make: unit => t = "RTCPeerConnection";

[@bs.new] external make1: Configuration.t => t = "RTCPeerConnection";

/* TODO delete if not implemented in browsers */
[@bs.get] [@bs.return nullable]
external canTrickleIceCandidates: t => option(bool) =
  "canTrickleIceCandidates";

[@bs.get] [@bs.return nullable]
external connectionState: t => option(string) = "connectionState";

/* TODO test */
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

[@bs.get] [@bs.return nullable]
external pendingRemoteDescription: t => option(PWA_RTCSessionDescription.t) =
  "pendingRemoteDescription";

[@bs.get] external signalingState: t => string = "signalingState";

/* these are marked experimental and undefined (in chrome) in newly created obj */
/* defaultIceServers */
/* peerIdentity */
/* sctp */

/* onaddstream deprecated */

let connectionstatechange: PWA_EventType.t(t, PWA_Event.t) =
  PWA_EventType.unsafe("connectionstatechange");

/* TODO test */
let datachannel: PWA_EventType.t(t, {. "channel": PWA_RTCDataChannel.t}) =
  PWA_EventType.unsafe("datachannel");

let icecandidate: PWA_EventType.t(t, PWA_RTCPeerConnectionIceEvent.t) =
  PWA_EventType.unsafe("icecandidate");

let iceconnectionstatechange: PWA_EventType.t(t, PWA_Event.t) =
  PWA_EventType.unsafe("iceconnectionstatechange");

let icegatheringstatechange: PWA_EventType.t(t, PWA_Event.t) =
  PWA_EventType.unsafe("icegatheringstatechange");

let identityresult: PWA_EventType.t(t, {. "assertion": string}) =
  PWA_EventType.unsafe("identityresult ");

type identity_error_event = {
  .
  "idp": string,
  "loginUrl": Js.Nullable.t(string),
  "protocol": string,
};

let idpassertionerror: PWA_EventType.t(t, identity_error_event) =
  PWA_EventType.unsafe("idpassertionerror");

let idpvalidationerror: PWA_EventType.t(t, identity_error_event) =
  PWA_EventType.unsafe("idpvalidationerror");

let negotiationneeded: PWA_EventType.t(t, PWA_Event.t) =
  PWA_EventType.unsafe("negotiationneeded");

let peeridentity: PWA_EventType.t(t, PWA_Event.t) =
  PWA_EventType.unsafe("peeridentity");

/* peeridentity deprecated */

let signalingstatechange: PWA_EventType.t(t, PWA_Event.t) =
  PWA_EventType.unsafe("signalingstatechange ");

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
  ) =
  PWA_EventType.unsafe("track");

[@bs.send]
external addIceCandidate:
  (t, PWA_RTCIceCandidate.Init.t) => Js.Promise.t(unit) =
  "addIceCandidate";

/* addStream deprecated */
/*[@bs.send] external addStream: (t, PWA_MediaStream.t) => unit = "addStream";*/

[@bs.send]
external addTrack:
  (t, PWA_MediaStreamTrack.t, PWA_MediaStream.t) => PWA_RTCRtpSender.t =
  "addTrack";

[@bs.send] [@bs.variadic]
external addTrack_:
  (t, PWA_MediaStreamTrack.t, array(PWA_MediaStream.t)) => PWA_RTCRtpSender.t =
  "addTrack";

[@bs.send] external close: t => unit = "close";

[@bs.send]
external createAnswer_:
  (t, Js.Nullable.t({. "voiceActivityDetection": Js.Nullable.t(bool)})) =>
  Js.Promise.t(PWA_RTCSessionDescription.Init.t) =
  "createAnswer";

let createAnswer = (self, ~voiceActivityDetection=?, ()) => {
  let options =
    if (voiceActivityDetection->Belt.Option.isNone) {
      Js.Nullable.undefined;
    } else {
      Js.Nullable.return({
        "voiceActivityDetection":
          voiceActivityDetection->Js.Nullable.fromOption,
      });
    };

  createAnswer_(self, options);
};

[@bs.send]
external createDataChannel_:
  (t, string, Js.Nullable.t(PWA_RTCDataChannel.Init.t)) =>
  PWA_RTCDataChannel.t =
  "createDataChannel";

let createDataChannel = (self, ~label, ~init=?, ()) => {
  createDataChannel_(self, label, init->Js.Nullable.fromOption);
};

[@bs.send]
external createOffer_:
  (
    t,
    Js.Nullable.t({
      .
      "iceRestart": Js.Nullable.t(bool),
      "voiceActivityDetection": Js.Nullable.t(bool),
    })
  ) =>
  Js.Promise.t(PWA_RTCSessionDescription.Init.t) =
  "createOffer";

let createOffer = (self, ~iceRestart=?, ~voiceActivityDetection=?, ()) => {
  let options =
    if (iceRestart->Belt.Option.isNone
        && voiceActivityDetection->Belt.Option.isNone) {
      Js.Nullable.undefined;
    } else {
      Js.Nullable.return({
        "iceRestart": iceRestart->Js.Nullable.fromOption,
        "voiceActivityDetection":
          voiceActivityDetection->Js.Nullable.fromOption,
      });
    };

  createOffer_(self, options);
};

[@bs.val] [@bs.scope "RTCPeerConnection"]
external generateCertificate:
  ([@bs.unwrap] [ | `String(string) | `Object(Js.t({..}))]) =>
  Js.Promise.t(PWA_RTCCertificate.t) =
  "generateCertificate";

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

// [@bs.send]
// external setConfiguration: (t, Configuration.t) => unit = "setConfiguration";

[@bs.send]
external setLocalDescription:
  (t, PWA_RTCSessionDescription.Init.t) => Js.Promise.t(unit) =
  "setLocalDescription";

[@bs.send]
external setRemoteDescription:
  (t, PWA_RTCSessionDescription.Init.t) => Js.Promise.t(unit) =
  "setRemoteDescription";

/* getIdentityAssertion */
/* getLocalSreams is deprecated */
/* getRemoteStreams is deprecated */
/* getStreamById is deprecated */
/* removeStream is deprecated */
/* setIdentityProvider undefined */