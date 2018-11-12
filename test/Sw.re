open Expect;

Js.log("hello sw");

open SW;
open EventTarget;
open ServiceWorkerGlobalScope;
open ServiceWorkerRegistration;
open Js.Promise;
open SW_Prelude;

/* expectToEqual(Notification.permission, "default"); */

self->registration->showNotification("hello sw", ());

self->addEventListener(install, event => Js.log("on install"));

self->addEventListener(
  activate,
  event => {
    Js.log("on activate");
    self->registration->showNotification("on activate", ());
    ();
  },
);

self->addEventListener(message, event => Js.log("on message"));

self->addEventListener(fetch, event => Js.log("on fetch"));

self->addEventListener(
  notificationclick,
  event => {
    Js.log("on notificationclick");
    open Notification;
    open NotificationEvent;
    Js.log(event);
    Js.log2("notification action:", event->action);
    Js.log2("notification title:", event->notification->title);

    self->clients->Clients.matchAll()
    |> then_(clients => {
         Js.log2("clients", clients);
         resolve();
       });
    ();
  },
);

self->addEventListener(notificationclose, event =>
  Js.log("on notificationclose")
);

self->addEventListener(push, event => Js.log("on push"));

self->addEventListener(pushsubscriptionchange, event =>
  Js.log("on pushsubscriptionchange")
);

self->addEventListener(sync, event => Js.log("on sync"));