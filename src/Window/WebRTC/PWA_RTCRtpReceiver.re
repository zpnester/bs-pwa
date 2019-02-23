type t;



[@bs.get] external track: t => PWA_MediaStreamTrack.t = "track";

/* same type? */

[@bs.get] external rtcpTransport: t => PWA_RTCDtlsTransport.t = "rtcpTransport";

[@bs.get] external transport: t => PWA_RTCDtlsTransport.t = "transport";


[@bs.send] external getContributingSources: t => array({
	.
	"audioLevel": float,
	"source": int,
	"timestamp": float
}) = "getContributingSources";


[@bs.get] external getParameters: t => Js.t({..}) = "getParameters";


[@bs.get] external getStats: t => Js.Promise.t(Js.t({..})) = "getStats";

/* TODO docs say it returns same as getContributingSources */
[@bs.get] external getSynchronizationSources: t => array({
	.
	"voiceActivityFlag": Js.Nullable.t(bool)
}) = 
"getSynchronizationSources";
 



