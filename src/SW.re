module ServiceWorkerGlobalScope = SW_ServiceWorkerGlobalScope;
module ServiceWorkerRegistration = SW_ServiceWorkerRegistration;
module ServiceWorker = SW_ServiceWorker;
module Client = SW_Client;
module ClientType = SW_ClientType;
module Clients = SW_Clients;
module Event = SW_Event;
module Notification = SW_Notification;
module NotificationEvent = SW_NotificationEvent;
module Notification_Permission = SW_Notification_Permission;
module Notification_Action = SW_Notification_Action;
module WindowClient = SW_WindowClient;
module PushMessageData = SW_PushMessageData;
module PushEvent = SW_PushEvent;
module MessagePort = SW_MessagePort;
module MessageEvent = SW_MessageEvent;

/* this does not work with .rei */
[@bs.val] external self: SW_ServiceWorkerGlobalScope.t = "self";