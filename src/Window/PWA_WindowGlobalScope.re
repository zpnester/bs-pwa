type t;


[@bs.val] external self: t = "self";
[@bs.val] external window: t = "window";

[@bs.get] external navigator: t => PWA_Navigator.t = "navigator";
