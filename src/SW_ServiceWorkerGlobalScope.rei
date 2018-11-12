include (module type of SW_WorkerGlobalScope);

let clients: t => SW_Clients.t;
let registration: t => SW_ServiceWorkerRegistration.t;
let caches: t => SW_CacheStorage.t;
let skipWaiting: t => Js.Promise.t(unit);

let install: SW_EventType.t(SW_InstallEvent.t);
let activate: SW_EventType.t(SW_Event.t);
let message: SW_EventType.t(SW_MessageEvent.t);
let fetch: SW_EventType.t(SW_FetchEvent.t);
let notificationclick: SW_EventType.t(SW_NotificationEvent.t);
let notificationclose: SW_EventType.t(SW_NotificationEvent.t);
let push: SW_EventType.t(SW_PushEvent.t);
let pushsubscriptionchange: SW_EventType.t(SW_PushEvent.t);
let sync: SW_EventType.t(SW_SyncEvent.t);