type t;

[@bs.send] external importScripts: (t, string) => unit = "importScripts";

[@bs.val] external self: t = "self";