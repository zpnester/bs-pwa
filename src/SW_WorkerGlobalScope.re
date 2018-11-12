include SW_EventTarget;

open SW_Types;

[@bs.get] external navigator: t => worker_navigator = "navigator";

/* TODO */
/* [@bs.val] external self: t = "self"; */

[@bs.get] external location: t => worker_location = "location";

[@bs.get] external caches: t => SW_CacheStorage.t = "caches";
[@bs.get] external indexedDB: t => idb_factory = "indexedDB";
[@bs.get] external isSecureContext: t => bool = "isSecureContext";
[@bs.get] external origin: t => string = "origin";
[@bs.send] external importScripts: (t, string) => unit = "importScripts";

/* TODO ret type */
[@bs.send] external atob: (t, string) => string = "atob";
[@bs.send] external btoa: (t, string) => string = "btoa";

/* clearInterval */
/* clearTimeout */
/* createImageBitmap */

/* only basic fetch stuff here */
[@bs.send]
external fetch: (t, string) => Js.Promise.t(SW_Response.t) = "fetch";

/* setInterval */
/* setTimeout */

let error: SW_EventType.t(SW_Event.t) = SW_EventType.unsafe("error");
let offline: SW_EventType.t(SW_Event.t) = SW_EventType.unsafe("offline");
let online: SW_EventType.t(SW_Event.t) = SW_EventType.unsafe("online");
let languagechange: SW_EventType.t(SW_Event.t) =
  SW_EventType.unsafe("languagechange");