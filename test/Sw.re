open Expect;

Js.log("hello sw");

open SW;
open ServiceWorkerGlobalScope;
open ServiceWorkerRegistration;
open Js.Promise;
open Belt;
open Clients;

self->importScripts("1.js");

Js.log2("sw registration", self->registration);
Js.log2("push manager", self->registration->pushManager);

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
    | Some(port) => port->SW_MessagePort.postMessage("response via port")
    | _ => Js.log("no port")
    };

    Js.log2("data", e->data);
    Js.log2("origin", e->origin);
    Js.log2("lastEventId", e->lastEventId);
    Js.log2("source", e->source);
    Js.log2("ports", e->ports);

    let reg = self->registration;

    reg->SW_ServiceWorkerRegistration.getNotifications()
    |> then_(ns => {
         Js.log2("notifications", ns);
         resolve();
       })
    |> ignore;

    Js.log2(
      "active",
      reg->SW_ServiceWorkerRegistration.active->Belt.Option.isSome,
    );
    Js.log2(
      "installing",
      reg->SW_ServiceWorkerRegistration.installing->Belt.Option.isSome,
    );
    Js.log2(
      "waiting",
      reg->SW_ServiceWorkerRegistration.waiting->Belt.Option.isSome,
    );

    let clients = self->clients;
    clients->matchAll()
    |> then_(arr => {
         arr
         |> Js.Array.forEachi((c, i) => {
              c->SW_Client.postMessage("message for client");
              Js.log2("client id", c->SW_Client.id);
              Js.log2("client type_", c->SW_Client.type_);
              Js.log2("client url", c->SW_Client.url);
            });

         Js.log2("clients", arr);
         resolve();
       })
    |> ignore;

    clients->get("/")
    |> then_(cl => {
         Js.log2("client", cl);
         resolve();
       })
    |> ignore;

    Js.log2("clients", clients);

    self
    ->registration
    ->showNotification(
        "Test Notification",
        ~body="Hello there",
        ~icon="https://image.flaticon.com/icons/png/512/1374/1374680.png",
        ~badge="https://image.flaticon.com/icons/png/512/1374/1374680.png",
        ~image="https://image.flaticon.com/icons/png/512/1374/1374679.png",
        ~tag="tag1",
        /* ~requireInteraction=true, */
        ~actions=[|
          Notification.Action.make(~title="Open window", ~action="left", ()),
          Notification.Action.make(~title="Do nothing", ~action="right", ()),
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

    Js.log2("action", event->action);
    Js.log2("tag", event->notification->tag);
    Js.log2("timestamp", event->notification->timestamp);

    if (event->action == Some("left")) {
      self->clients->openWindow("/")
      |> then_(wc => {
           Js.log2("wc", wc);
           wc->Belt.Option.getExn->SW_WindowClient.navigate("/elsewhere");
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