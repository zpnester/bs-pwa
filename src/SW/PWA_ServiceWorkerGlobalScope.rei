include (module type of PWA_WorkerGlobalScope);

let registration: t => PWA_ServiceWorkerRegistration.t;

let notificationclick: PWA_EventType.t(t, PWA_NotificationEvent.t);

let activate: PWA_EventType.t(t, PWA_ActivateEvent.t);

let notificationclose: PWA_EventType.t(t, PWA_NotificationEvent.t);

let install: PWA_EventType.t(t, PWA_InstallEvent.t);

let fetch: PWA_EventType.t(t, PWA_FetchEvent.t);

let push: PWA_EventType.t(t, PWA_PushEvent.t);

let sync: PWA_EventType.t(t, PWA_SyncEvent.t);

let message: PWA_EventType.t(t, PWA_MessageEvent.t);

let clients: t => PWA_Clients.t;

let pushsubscriptionchange: PWA_EventType.t(t, PWA_PushSubscriptionChangeEvent.t);

let skipWaiting: t => Js.Promise.t(unit);