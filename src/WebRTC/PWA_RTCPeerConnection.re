
type t;


/* TODO remove */
/*include PWA_EventTarget.Make({
	type nonrec t = t;
});
*/

module Configuration = {
	type t;

	[@bs.obj] external make: (
		~bundlePolicy: string=?,
		~certificates: array(PWA_RTCCertificate.t)=?,
		~iceCandidatePoolSize: int=?,
		~iceServers: array(PWA_RTCIceServer.t)=?,
		~iceTransportPolicy: string=?,
		~peerIdentity: string=?,
		~rtcpMuxPolicy: string=?,
		unit) => t = "";

	[@bs.get] external bundlePolicy_: t => Js.Nullable.t(string) = "bundlePolicy";
	let bundlePolicy = self => bundlePolicy_(self)->Js.Nullable.toOption;

	[@bs.get] external certificates_: t => Js.Nullable.t(array(PWA_RTCCertificate.t)) = 
		"certificates";
	let certificates = self => certificates_(self)->Js.Nullable.toOption;	

	[@bs.get] external iceCandidatePoolSize_: t => Js.Nullable.t(int) = "iceCandidatePoolSize";
	let iceCandidatePoolSize = self => iceCandidatePoolSize_(self)->Js.Nullable.toOption;

	[@bs.get] external iceServers_: t => Js.Nullable.t(array(PWA_RTCIceServer.t)) = "iceServers";
	let iceServers = self => iceServers_(self)->Js.Nullable.toOption;

	[@bs.get] external iceTransportPolicy_: t => Js.Nullable.t(string) = "iceTransportPolicy";
	let iceTransportPolicy = self => iceTransportPolicy_(self)->Js.Nullable.toOption;

	[@bs.get] external peerIdentity_: t => Js.Nullable.t(string) = "peerIdentity";
	let peerIdentity = self => peerIdentity_(self)->Js.Nullable.toOption;

	[@bs.get] external rtcpMuxPolicy_: t => Js.Nullable.t(string) = "rtcpMuxPolicy";
	let rtcpMuxPolicy = self => rtcpMuxPolicy_(self)->Js.Nullable.toOption;


};


[@bs.new] external make_: Js.Nullable.t(Configuration.t) => t = "RTCPeerConnection";

let make = (~config=?, ()) => {
	make_(config->Js.Nullable.fromOption)
};


/*let make = (~config: option())*/

/* TODO test */
[@bs.get] external canTrickleIceCandidates_: t => Js.Undefined.t(bool) = "canTrickleIceCandidates";
let canTrickleIceCandidates = self => canTrickleIceCandidates_(self)->Js.Undefined.toOption;

 
[@bs.get] external connectionState: t => string = "connectionState";


/* TODO test */
[@bs.get] external currentLocalDescription_: t => Js.Null.t(PWA_RTCSessionDescription.t) = "currentLocalDescription";
let currentLocalDescription = self => currentLocalDescription_(self)->Js.Null.toOption;

[@bs.get] external currentRemoteDescription_: t => Js.Null.t(PWA_RTCSessionDescription.t) = "currentRemoteDescription";
let currentRemoteDescription = self => currentRemoteDescription_(self)->Js.Null.toOption;

[@bs.get] external iceConnectionState: t => string = "iceConnectionState";
[@bs.get] external iceGatheringState: t => string = "iceGatheringState";

[@bs.get] external localDescription_: t => Js.Null.t(PWA_RTCSessionDescription.t) = "localDescription";
let localDescription = self => localDescription_(self)->Js.Null.toOption;

[@bs.get] external pendingLocalDescription_: t => Js.Null.t(PWA_RTCSessionDescription.t) = "pendingLocalDescription";
let pendingLocalDescription = self => pendingLocalDescription_(self)->Js.Null.toOption;

[@bs.get] external remoteDescription_: t => Js.Null.t(PWA_RTCSessionDescription.t) = "remoteDescription";
let remoteDescription = self => remoteDescription_(self)->Js.Null.toOption;

[@bs.get] external pendingRemoteDescription_: t => Js.Null.t(PWA_RTCSessionDescription.t) = "pendingRemoteDescription";
let pendingRemoteDescription = self => pendingRemoteDescription_(self)->Js.Null.toOption;
   
[@bs.get] external signalingState: t => string= "signalingState";

/* these are marked experimental and undefined (in chrome) in newly created obj */
/* defaultIceServers */
/* peerIdentity */
/* sctp */


/* onaddstream deprecated */

/* TODO test */
let connectionstatechange: PWA_EventType.t(t, PWA_Event.t) = PWA_EventType.unsafe("connectionstatechange");



/* TODO test */
let datachannel: PWA_EventType.t(t, { 
	.
	"channel": PWA_RTCDataChannel.t
}) = PWA_EventType.unsafe("datachannel");

/* TODO test*/
let icecandidate: PWA_EventType.t(t, {
	.
	"candidate": Js.Nullable.t(PWA_RTCIceCandidate.t),
	"url": Js.Nullable.t(string),  /* TODO test */
}) = PWA_EventType.unsafe("icecandidate");

let iceconnectionstatechange: PWA_EventType.t(t, PWA_Event.t) = 
	PWA_EventType.unsafe("iceconnectionstatechange");

let icegatheringstatechange: PWA_EventType.t(t, PWA_Event.t) = 
	PWA_EventType.unsafe("icegatheringstatechange");

let identityresult: PWA_EventType.t(t, {
	.
	"assertion": string
}) = 
	PWA_EventType.unsafe("identityresult ");


type identity_error_event = {
	.
	"idp": string,
	"loginUrl": Js.Nullable.t(string),
	"protocol": string
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

let signalingstatechange : PWA_EventType.t(t, PWA_Event.t) = 
	PWA_EventType.unsafe("signalingstatechange ");


let track: PWA_EventType.t(t, {
	.
	"receiver": PWA_RTCRtpReceiver.t,
	"streams": array(PWA_MediaStream.t),
	"track": PWA_MediaStreamTrack.t,
	"transceiver": PWA_RTCRtpTransceiver.t
}) = 
	PWA_EventType.unsafe("track");



[@bs.send] external addIceCandidate: 
(t, PWA_RTCIceCandidate.init) => Js.Promise.t(unit) = "addIceCandidate";



[@bs.send] external addStream: (t, PWA_MediaStream.t) => unit = "addStream";

[@bs.send] external addTrack: (t, PWA_MediaStreamTrack.t, PWA_MediaStream.t) => 
PWA_RTCRtpSender.t = "addTrack";

[@bs.send] external addTrack2: (t, PWA_MediaStreamTrack.t, PWA_MediaStream.t, PWA_MediaStream.t) => 
PWA_RTCRtpSender.t = "addTrack";

[@bs.send] external close: t => unit = "close";

[@bs.send] external createAnswer_: (t, Js.Nullable.t({
	.
	"voiceActivityDetection": Js.Nullable.t(bool)
})) => Js.Promise.t(PWA_RTCSessionDescription.init) = "createAnswer";

let createAnswer = (self, ~voiceActivityDetection=?, ()) => {
	let options = if (voiceActivityDetection->Belt.Option.isNone) {
		Js.Nullable.undefined
	} else {
		Js.Nullable.return({
			"voiceActivityDetection": voiceActivityDetection->Js.Nullable.fromOption
		})
	};

	createAnswer_(self, options);
};

[@bs.send] external createDataChannel_: (t, string, Js.Nullable.t(PWA_RTCDataChannel.Init.t)) => 
	PWA_RTCDataChannel.t = "createDataChannel";


let createDataChannel = (self, ~label, ~init=?, ()) => {
	createDataChannel_(self, label, init->Js.Nullable.fromOption);
};
 
[@bs.send] external createOffer_: (t, Js.Nullable.t({
	.
	"iceRestart": Js.Nullable.t(bool),
	"voiceActivityDetection": Js.Nullable.t(bool)
})) => Js.Promise.t(PWA_RTCSessionDescription.init) = "createOffer"; 


let createOffer = (self, ~iceRestart=?, ~voiceActivityDetection=?, ()) => {
	let options = if (iceRestart->Belt.Option.isNone && voiceActivityDetection->Belt.Option.isNone) {
		Js.Nullable.undefined
	} else {
		Js.Nullable.return({
			"iceRestart": iceRestart->Js.Nullable.fromOption,
			"voiceActivityDetection": voiceActivityDetection->Js.Nullable.fromOption
		})
	};

	createOffer_(self, options);
};


[@bs.val] [@bs.scope "RTCPeerConnection"] external generateCertificate: 
([@bs.unwrap] [`String(string) | `Object(Js.t({..}))]) => 
	Js.Promise.t(PWA_RTCCertificate.t) = "generateCertificate"; 


[@bs.send] external getConfiguration: t => Configuration.t = "getConfiguration";

[@bs.send] external getReceivers: t => array(PWA_RTCRtpReceiver.t) = "getReceivers";

[@bs.send] external getSenders: t => array(PWA_RTCRtpSender.t) = "getSenders";

[@bs.send] external getStats: (t, ~selector: PWA_MediaStream.t=?, unit) => 
	Js.Promise.t(Js.t({..})) = "getStats";

[@bs.send] external removeTrack: (t, PWA_RTCRtpSender.t) => unit= "removeTrack";

[@bs.send] external setConfiguration: (t, Configuration.t) => unit= "setConfiguration";


[@bs.send] external setLocalDescription: (t, PWA_RTCSessionDescription.init) => Js.Promise.t(unit) = "setLocalDescription";


[@bs.send] external setRemoteDescription: (t, PWA_RTCSessionDescription.init) => Js.Promise.t(unit) = "setRemoteDescription";



/* getIdentityAssertion */
/* getLocalSreams is deprecated */
/* getRemoteStreams is deprecated */
/* getStreamById is deprecated */
/* removeStream is deprecated */
/* setIdentityProvider undefined */


