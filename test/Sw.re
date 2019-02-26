open Expect;

Js.log("hello sw");

open PWA;
open ServiceWorkerGlobalScope;
open Js.Promise;
open Clients;

expectToEqual(self->registration->ServiceWorkerRegistration.scope, "http://localhost:8081/");

self->importScripts("1.js");

Js.log2("sw registration", self->registration);
Js.log2("push manager", self->registration->ServiceWorkerRegistration.pushManager);

self->addEventListener(install, _ => Js.log("on install"));

self->addEventListener(activate, _ => Js.log("on activate"));

self->skipWaiting;

self->addEventListener(fetch, _ => Js.log("on fetch"));
self->addEventListener(
  message,
  e => {
    open MessageEvent;
    Js.log("on message");

    expectToEqualAny(e->ports, [||]);
    switch (e->ports->Belt.Array.get(0)) {
    | Some(port) => port->PWA_MessagePort.postMessage("response via port")
    | _ => Js.log("no port")
    };

    expectToEqual(e->data->Js.typeof, "string");
    expectToEqual(e->origin->Js.typeof, "string");
    expectToEqual(e->lastEventId->Js.typeof, "string");
    expectToEqual(e->source->Js.typeof, "object");
    expectToEqual(e->ports, [||]);

    let reg = self->registration;

    reg->PWA_ServiceWorkerRegistration.getNotifications()
    |> then_(ns => {
         Js.log2("notifications", ns);
         resolve();
       })
    |> ignore;

    Js.log2(
      "active",
      reg->PWA_ServiceWorkerRegistration.active->Belt.Option.isSome,
    );
    Js.log2(
      "installing",
      reg->PWA_ServiceWorkerRegistration.installing->Belt.Option.isSome,
    );
    Js.log2(
      "waiting",
      reg->PWA_ServiceWorkerRegistration.waiting->Belt.Option.isSome,
    );

    let clients = self->clients;

    clients->matchAll()
    |> then_(arr => {
        expectToEqual(arr->Array.length, 1);

         arr
         |> Js.Array.forEach(c => {
              c->PWA_Client.postMessage("message for client");
              expectToEqual(c->PWA_Client.id->Js.typeof, "string");
              expectToEqual(c->PWA_Client.type_->Js.typeof, "string");
              expectToEqual(c->PWA_Client.url->Js.typeof, "string");
            });

         resolve();
       })
    |> ignore;

    clients->get("/")
    |> then_(cl => {
         expectToEqual(cl, None);
         resolve();
       })
    |> ignore;


    self
    ->registration
    ->ServiceWorkerRegistration.showNotification(
        "Test Notification",
        ~body="Hello there",
        ~icon="https://image.flaticon.com/icons/png/512/1374/1374680.png",
        ~badge="https://image.flaticon.com/icons/png/512/1374/1374680.png",
        ~image="https://image.flaticon.com/icons/png/512/1374/1374679.png",
        ~tag="tag1",
        /* ~requireInteraction=true, */
        ~actions=[|
          Notification.Action.make(~title="Open window", ~action="left", ()),
          /*Notification.Action.make(~title="Do nothing", ~action="right", ()),*/
          Notification.Action.make(
            ~action="a1",
            ~title="Click",
            ~icon=
              "https://upload.wikimedia.org/wikipedia/commons/thumb/e/e6/Noto_Emoji_KitKat_263a.svg/1200px-Noto_Emoji_KitKat_263a.svg.png",
            (),
          ),
        |],
        (),
      )
    |> Js.Promise.then_(() => {
         Js.log("notification fired");
         resolve();
       })
    |> ignore;
  },
);

self->addEventListener(
  notificationclick,
  event => {
    open NotificationEvent;
    open Notification;
    Js.log("on notification click");

    /* expect smiley face click */
    /*expectToEqual(event->action, Some("a1")); */
    /*expectToEqual(event->notification->tag, Some("tag1")); */
    /*expectToEqual(event->notification->timestamp->Js.typeof, "number");*/

    if (event->action == Some("left")) {
      self->clients->openWindow("/")
      |> then_(wc => {
          /* validate type */
          wc->Belt.Option.getExn->WindowClient.asClient->WindowClient.asWindowClient->Belt.Option.getExn;
          wc->Belt.Option.getExn->PWA_WindowClient.navigate("/elsewhere");
         })
      |> then_(wc => {
           Js.log2("navigated", wc);
           resolve();
         })
      |> ignore;
      ();
    };
  },
);

self->addEventListener(notificationclose, _ =>
  Js.log("on notification close")
);

self->addEventListener(push, _ => Js.log("on push"));

self->addEventListener(pushsubscriptionchange, _ =>
  Js.log("on pushsubscriptionchange")
);

self->addEventListener(sync, _ => Js.log("on sync"));