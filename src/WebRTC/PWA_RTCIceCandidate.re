type t;

module Init = {
  type t = {
    .
    "candidate": Js.Nullable.t(string),
    "sdpMLineIndex": Js.Nullable.t(int),
    "sdpMid": Js.Nullable.t(string),
    "usernameFragment": Js.Nullable.t(string),
  };
};

[@bs.new] external make: unit => t = "RTCIceCandidate";
[@bs.new] external make1: Init.t => t = "RTCIceCandidate";

/* TODO test all */

[@bs.get] external candidate: t => string = "candidate";

[@bs.get] external component: t => string = "component";

[@bs.get] external foundation: t => string = "foundation";

[@bs.get] external ip: t => string = "ip";

[@bs.get] external port: t => int = "port";

[@bs.get] external priority: t => float = "priority";

[@bs.get] external protocol: t => string = "protocol";

[@bs.get] [@bs.return nullable]
external relatedAddress: t => option(string) = "relatedAddress";

[@bs.get] [@bs.return nullable]
external relatedPort: t => option(int) = "relatedPort";

[@bs.get] [@bs.return nullable]
external sdpMid: t => option(string) = "sdpMid";

[@bs.get] [@bs.return nullable]
external sdpMLineIndex: t => option(int) = "sdpMLineIndex";

[@bs.get] [@bs.return nullable]
external tcpType: t => option(string) = "tcpType";

[@bs.get] external type_: t => string = "type";

[@bs.get] external usernameFragment: t => string = "usernameFragment";

[@bs.send] external toJSON: t => Init.t = "toJSON";