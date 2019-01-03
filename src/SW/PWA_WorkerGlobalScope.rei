include (module type of PWA_EventTarget);

let importScripts: (t, string) => unit;

[@bs.val] external self: t = "self";
