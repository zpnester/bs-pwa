include (module type of PWA_WorkerGlobalScope);

[@bs.get]
external registration: t => PWA_ServiceWorkerRegistration.t = "registration";

let notificationclick: PWA_EventType.t(t, PWA_NotificationEvent.t);

let activate: PWA_EventType.t(t, PWA_ActivateEvent.t);

let notificationclose: PWA_EventType.t(t, PWA_NotificationEvent.t);

let install: PWA_EventType.t(t, PWA_InstallEvent.t);

let fetch: PWA_EventType.t(t, PWA_FetchEvent.t);

let push: PWA_EventType.t(t, PWA_PushEvent.t);

let sync: PWA_EventType.t(t, PWA_SyncEvent.t);

let message: PWA_EventType.t(t, PWA_MessageEvent.t);

[@bs.get] external clients: t => PWA_Clients.t = "clients";

let pushsubscriptionchange:
  PWA_EventType.t(t, PWA_PushSubscriptionChangeEvent.t);

[@bs.send] external skipWaiting: t => Js.Promise.t(unit) = "skipWaiting";
