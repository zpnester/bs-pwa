include PWA_WorkerGlobalScope;

[@bs.get]
external registration: t => PWA_ServiceWorkerRegistration.t = "registration";

let notificationclick: PWA_EventType.t(t, PWA_NotificationEvent.t) =
  PWA_EventType.unsafe("notificationclick");

let activate: PWA_EventType.t(t, PWA_ActivateEvent.t) =
  PWA_EventType.unsafe("activate");
let notificationclose: PWA_EventType.t(t, PWA_NotificationEvent.t) =
  PWA_EventType.unsafe("notificationclose");

let install: PWA_EventType.t(t, PWA_InstallEvent.t) =
  PWA_EventType.unsafe("install");
let fetch: PWA_EventType.t(t, PWA_FetchEvent.t) = PWA_EventType.unsafe("fetch");

let push: PWA_EventType.t(t, PWA_PushEvent.t) = PWA_EventType.unsafe("push");

let sync: PWA_EventType.t(t, PWA_SyncEvent.t) = PWA_EventType.unsafe("sync");

let message: PWA_EventType.t(t, PWA_MessageEvent.t) =
  PWA_EventType.unsafe("message");

[@bs.get] external clients: t => PWA_Clients.t = "clients";

let pushsubscriptionchange: PWA_EventType.t(t, PWA_ExtendableEvent.t) =
  PWA_EventType.unsafe("pushsubscriptionchange");

[@bs.send] external skipWaiting: t => Js.Promise.t(unit) = "skipWaiting";








