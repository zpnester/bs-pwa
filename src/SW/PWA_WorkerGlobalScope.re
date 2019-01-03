include PWA_EventTarget;

[@bs.send] external importScripts: (t, string) => unit = "importScripts";

[@bs.val] external self: t = "self";