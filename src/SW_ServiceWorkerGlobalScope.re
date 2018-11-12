include SW_WorkerGlobalScope;

[@bs.get] external clients: t => SW_Clients.t = "clients";
[@bs.get]
external registration: t => SW_ServiceWorkerRegistration.t = "registration";
[@bs.get] external caches: t => SW_CacheStorage.t = "caches";

[@bs.send] external skipWaiting: t => Js.Promise.t(unit) = "skipWaiting";

let install: SW_EventType.t(SW_InstallEvent.t) =
  SW_EventType.unsafe("install");
let activate: SW_EventType.t(SW_Event.t) = SW_EventType.unsafe("activate");
let message: SW_EventType.t(SW_MessageEvent.t) =
  SW_EventType.unsafe("message");
let fetch: SW_EventType.t(SW_FetchEvent.t) = SW_EventType.unsafe("fetch");
let notificationclick: SW_EventType.t(SW_NotificationEvent.t) =
  SW_EventType.unsafe("notificationclick");
let notificationclose: SW_EventType.t(SW_NotificationEvent.t) =
  SW_EventType.unsafe("notificationclose");
let push: SW_EventType.t(SW_PushEvent.t) = SW_EventType.unsafe("push");
let pushsubscriptionchange: SW_EventType.t(SW_PushEvent.t) =
  SW_EventType.unsafe("pushsubscriptionchange");
let sync: SW_EventType.t(SW_SyncEvent.t) = SW_EventType.unsafe("sync");