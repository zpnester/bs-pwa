type t;

/* this does not work with .rei */
[@bs.val] external self: t = "self";

[@bs.get] external navigator: t => SW_Navigator.t = "navigator";