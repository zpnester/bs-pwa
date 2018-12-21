open SW;
open WindowGlobalScope;
open Navigator;
open Belt;
open ServiceWorkerContainer;
open ServiceWorker;
open Js.Promise;
open Expect;
Notification.requestPermission()
|> then_(p => {
     expectToEqual(p, Notification.Permission.granted);
     let n = Notification.make("hi", ~body="hello", ());

     expectToEqual(n->Notification.icon, Some(""));
     expectToEqual(n->Notification.title, Some("hi"));
     expectToEqual(n->Notification.body, Some("hello"));
     expectToEqual(n->Notification.actions, Some([||]));
     resolve();
   })
|> ignore;

switch (self->navigator->serviceWorker) {
| Some(c) =>
  c->register("/sw.wp.js")
  |> then_(reg => {
       Js.log2("window registration", reg);
       Js.log("register OK");
       resolve();
     })
  |> catch(e => {
       Js.log2("err", e);
       resolve();
     })
| None => resolve()
};

switch (self->navigator->serviceWorker->Option.flatMap(controller)) {
| Some(sw) =>
  Js.Global.setTimeout(() => sw->postMessage("hello"), 3000) |> ignore;
  Js.log("posted");
| None => Js.log("no sw")
};