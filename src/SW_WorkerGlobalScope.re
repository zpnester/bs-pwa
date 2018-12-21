include SW_EventTarget;

[@bs.send] external importScripts: (t, string) => unit = "importScripts";

/* this does not work with .rei */
[@bs.val] external self: t = "self";