include SW_WorkerGlobalScope;

[@bs.get]
external registration: t => SW_ServiceWorkerRegistration.t = "registration";

let notificationclick: SW_EventType.t(t, SW_NotificationEvent.t) =
  SW_EventType.unsafe("notificationclick");

let activate: SW_EventType.t(t, SW_Event.t) =
  SW_EventType.unsafe("activate");
let notificationclose: SW_EventType.t(t, SW_NotificationEvent.t) =
  SW_EventType.unsafe("notificationclose");

let install: SW_EventType.t(t, SW_InstallEvent.t) =
  SW_EventType.unsafe("install");
let fetch: SW_EventType.t(t, SW_FetchEvent.t) = SW_EventType.unsafe("fetch");

let push: SW_EventType.t(t, SW_PushEvent.t) = SW_EventType.unsafe("push");

let sync: SW_EventType.t(t, SW_SyncEvent.t) = SW_EventType.unsafe("sync");

let message: SW_EventType.t(t, SW_MessageEvent.t) =
  SW_EventType.unsafe("message");

[@bs.get] external clients: t => SW_Clients.t = "clients";

let pushsubscriptionchange: SW_EventType.t(t, SW_PushEvent.t) =
  SW_EventType.unsafe("pushsubscriptionchange");

[@bs.send] external skipWaiting: t => Js.Promise.t(unit) = "skipWaiting";


