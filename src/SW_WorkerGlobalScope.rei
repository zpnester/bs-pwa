include (module type of SW_EventTarget);

open SW_Types;

/* let self: t; */
let navigator: t => worker_navigator;
let location: t => worker_location;
let caches: t => SW_CacheStorage.t;
let indexedDB: t => idb_factory;
let isSecureContext: t => bool;
let origin: t => string;
let importScripts: (t, string) => unit;

let atob: (t, string) => string;
let btoa: (t, string) => string;

/* clearInterval */
/* clearTimeout */
/* createImageBitmap */

/* only basic fetch stuff here */
let fetch: (t, string) => Js.Promise.t(SW_Response.t);

/* setInterval */
/* setTimeout */

let error: SW_EventType.t(SW_Event.t);
let offline: SW_EventType.t(SW_Event.t);
let online: SW_EventType.t(SW_Event.t);
let languagechange: SW_EventType.t(SW_Event.t);