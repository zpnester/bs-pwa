type t;

[@bs.val] external self: t = "self";
[@bs.val] external window: t = "window";

let navigator: t => PWA_Navigator.t;