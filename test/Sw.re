open Expect;

Js.log("hello sw");

let self = "A"->Js.String.toLowerCase;
Js.log(self);

open PWA;
open ServiceWorkerPrelude;
open ServiceWorkerGlobalScope;
open Js.Promise;
open Clients;
open Belt;

let self = self;

expectToEqual(
  self_->registration->ServiceWorkerRegistration.scope,
  "http://localhost:8081/",
);

self_->importScripts("1.js");

Js.log2("sw registration", self_->registration);
Js.log2(
  "push manager",
  self_->registration->ServiceWorkerRegistration.pushManager,
);

self_->addEventListener(install, _ => Js.log("on install"));

self_->addEventListener(activate, _ => Js.log("on activate"));

self_->skipWaiting;

self_->addEventListener(fetch, _ => Js.log("on fetch"));
self_->addEventListener(
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
    expectToEqual(e->MessageEvent.origin->Js.typeof, "string");
    expectToEqual(e->lastEventId->Js.typeof, "string");
    expectToEqual(e->source->Js.typeof, "object");
    expectToEqual(e->ports, [||]);

    let reg = self_->registration;

    reg->PWA_ServiceWorkerRegistration.getNotifications
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

    let clients = self_->clients;

    let opts = Clients.MatchAllOptions.make(~_type=ClientType.window, ());
    clients->matchAll1(opts)
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

    let notif =
      Notification.Options.make(
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
      );

    self_
    ->registration
    ->ServiceWorkerRegistration.showNotification2("Test Notification", notif)
    |> Js.Promise.then_(() => {
         Js.log("notification fired");
         resolve();
       })
    |> ignore;
  },
);

self_->addEventListener(
  notificationclick,
  event => {
    open NotificationEvent;
    open Notification;
    Js.log("on notification click");

    /* expect smiley face click */
    expectToEqual(event->action, Some("a1"));
    expectToEqual(event->notification->tag, Some("tag1"));
    expectToEqual(event->notification->timestamp->Js.typeof, "number");

    if (event->action == Some("left")) {
      self_->clients->openWindow("/")
      |> then_(wc => {
           /* validate type */
           wc
           ->Option.getExn
           ->WindowClient.asClient
           ->WindowClient.asWindowClient
           ->Option.getExn
           ->ignore;
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

self_->addEventListener(notificationclose, _ =>
  Js.log("on notification close")
);

self_->addEventListener(push, _ => Js.log("on push"));

self_->addEventListener(pushsubscriptionchange, _ =>
  Js.log("on pushsubscriptionchange")
);

self_->addEventListener(sync, _ => Js.log("on sync"));