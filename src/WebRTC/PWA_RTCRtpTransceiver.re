type t;

[@bs.get] external currentDirection_: t => Js.Nullable.t(string) = "currentDirection";
let currentDirection = self => currentDirection_(self)->Js.Nullable.toOption;

[@bs.get] external direction: t => string = "direction";

[@bs.get] external mid_: t => Js.Nullable.t(string) = "mid";
let mid = self => mid_(self)->Js.Nullable.toOption;

[@bs.get] external receiver: t => PWA_RTCRtpReceiver.t = "receiver";

[@bs.get] external sender: t => PWA_RTCRtpSender.t = "sender";

[@bs.get] external stopped: t => bool = "stopped";

/* TODO */
[@bs.send] external setCodecPreferences: (t, Js.t({..})) => unit = "setCodecPreferences";

[@bs.send] external stop: t => unit = "stop";





