type t;

type init = {
	.
	"candidate": Js.Nullable.t(string),
	"sdpMid": Js.Nullable.t(string),
	"sdpMLineIndex": Js.Nullable.t(int),
	"usernameFragment": Js.Nullable.t(string),
};


[@bs.new] external make_: Js.Nullable.t(init) => t = "RTCIceCandidate";

let make = (~init=?, ()) => {
	make_(init->Js.Nullable.fromOption);
};

/* TODO test all */

[@bs.get] external candidate: t => string = "candidate";

[@bs.get] external component: t => string = "component";

[@bs.get] external foundation: t => string = "foundation";

[@bs.get] external ip: t => string = "ip";

[@bs.get] external port: t => int = "port";

[@bs.get] external priority : t => float = "priority";

[@bs.get] external protocol : t => string = "protocol";

[@bs.get] external relatedAddress_ : t => Js.Null.t(string) = "relatedAddress";
let relatedAddress = self => relatedAddress_(self)->Js.Null.toOption;



[@bs.get] external relatedPort_ : t => Js.Null.t(int) = "relatedPort";
let relatedPort = self => relatedPort_(self)->Js.Null.toOption;

[@bs.get] external sdpMid_ : t => Js.Null.t(string) = "sdpMid";
let sdpMid = self => sdpMid_(self)->Js.Null.toOption;


[@bs.get] external sdpMLineIndex_ : t => Js.Null.t(int) = "sdpMLineIndex";
[@bs.get] external sdpMLineIndex_ : t => Js.Null.t(int) = "sdpMLineIndex";
let sdpMLineIndex = self => sdpMLineIndex_(self)->Js.Null.toOption;



[@bs.get] external tcpType_ : t => Js.Null.t(string) = "tcpType";
let tcpType = self => tcpType_(self)->Js.Null.toOption;


[@bs.get] external type_ : t => string = "type";

[@bs.get] external usernameFragment : t => string = "usernameFragment";



[@bs.send] external toJSON: t => init = "toJSON"




 