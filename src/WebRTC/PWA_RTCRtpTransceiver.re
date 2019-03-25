type t;

[@bs.get] [@bs.return nullable]
external currentDirection: t => option(string) = "currentDirection";

[@bs.get] external direction: t => string = "direction";

[@bs.get] [@bs.return nullable] external mid: t => option(string) = "mid";

[@bs.get] external receiver: t => PWA_RTCRtpReceiver.t = "receiver";

[@bs.get] external sender: t => PWA_RTCRtpSender.t = "sender";

[@bs.get] external stopped: t => bool = "stopped";

[@bs.send]
external setCodecPreferences: (t, Js.t({..})) => unit = "setCodecPreferences";

[@bs.send] external stop: t => unit = "stop";
