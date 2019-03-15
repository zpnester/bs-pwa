type t;

module Init = {
  type t = {
    .
    "_type": Js.Nullable.t(string),
    "sdp": Js.Nullable.t(string),
  };
};

/* ctor deprecated */

[@bs.send] external toJSON: t => Init.t = "toJSON";
