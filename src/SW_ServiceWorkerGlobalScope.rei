include (module type of SW_WorkerGlobalScope);

let registration: t => SW_ServiceWorkerRegistration.t;

let notificationclick: SW_EventType.t(t, SW_NotificationEvent.t);
let activate: SW_EventType.t(t, SW_Event.t);
let notificationclose: SW_EventType.t(t, SW_NotificationEvent.t);
let install: SW_EventType.t(t, SW_InstallEvent.t);
let fetch: SW_EventType.t(t, SW_FetchEvent.t);
let push: SW_EventType.t(t, SW_PushEvent.t);
let sync: SW_EventType.t(t, SW_SyncEvent.t);
let message: SW_EventType.t(t, SW_MessageEvent.t);
let pushsubscriptionchange: SW_EventType.t(t, SW_PushEvent.t);

let clients: t => SW_Clients.t;
let skipWaiting: t => Js.Promise.t(unit);