type t;

type init = {. "_type": Js.Nullable.t(string), "sdp": Js.Nullable.t(string)};

/* ctor deprecated */

[@bs.send] external toJSON: t => init = "toJSON";

