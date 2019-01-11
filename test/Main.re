open PWA;
open WindowGlobalScope;
open Navigator;
open Belt;
open ServiceWorkerContainer;
open ServiceWorker;
open Js.Promise;
open Expect;

[@bs.val] external alert: string => unit = "";

let isArrayBuffer: Js.Typed_array.ArrayBuffer.t => bool = [%raw
  {|
function(ab) {
  return ab instanceof ArrayBuffer;
}
|}
];

/* test when push subscribed */

/* window
->navigator
->Navigator.serviceWorkerExn
->ServiceWorkerContainer.getRegistration
|> then_(reg => {
     let reg = reg->Option.getExn;
     reg
     ->ServiceWorkerRegistration.pushManager
     ->Option.getExn
     ->PushManager.getSubscription;
   })
|> then_(sub => {
     let sub = sub->Option.getExn;

     expectToEqual(sub->PushSubscription.endpoint->Js.typeof, "string");
     /* expectToEqual(sub->PushSubscription.expirationTime->Js.typeof, "number"); */
     expectToEqual(sub->PushSubscription.expirationTime->Option.isNone, true);
     expectToEqual(
       sub->PushSubscription.getKey("auth")->isArrayBuffer,
       true,
     );
     expectToEqual(sub->PushSubscription.options->Js.typeof, "object");
     Js.log2("options", sub->PushSubscription.options);

     Js.log2("toJSON", sub->PushSubscription.toJSON);
     expectToEqual(sub->PushSubscription.toJSON->Js.typeof, "object");
     resolve();
   }); */

Notification.requestPermission()
|> then_(p => {
     expectToEqual(p, `granted);
     let n = Notification.make("hi", ~body="hello", ());
     n->Notification.onclick(_ => Js.log("clicked"));

     expectToEqual(n->Notification.icon, Some(""));
     expectToEqual(n->Notification.title, Some("hi"));
     expectToEqual(n->Notification.body, Some("hello"));
     expectToEqual(n->Notification.actions, Some([||]));
     resolve();
   })
|> ignore;

switch (window->navigator->serviceWorker) {
| Some(c) =>
  c->register("/sw.js")
  |> then_(reg => {
       Js.log2("window registration", reg);
       Js.log("register OK");
       expectToEqual(
         reg->ServiceWorkerRegistration.scope,
         "http://localhost:8081/",
       );
       reg->ServiceWorkerRegistration.addEventListener(
         ServiceWorkerRegistration.updatefound, () =>
         Js.log("updatefound event")
       );
       resolve();
     })
  |> catch(e => {
       Js.log2("err", e);
       failwith("fail");
     })
| None => resolve()
};

switch (window->navigator->serviceWorker->Option.flatMap(controller)) {
| Some(sw) =>
  Js.Global.setTimeout(() => sw->postMessage("hello"), 3000) |> ignore;
  Js.log("posted");
| None => Js.log("no sw")
};

let getVideoUnsafe: unit => PWA_HTMLVideoElement.t = [%raw
  {|
function(unit) {
  return document.getElementById("video");
}
|}
];

/* let getCanvasUnsafe: unit => PWA_HTMLCanvasElement.t = [%raw {|
   function(unit) {
     return document.getElementById("canvas");
   }
   |}]; */

type img;
[@bs.set] external src: (img, string) => unit = "src";

let image = [%bs.raw {|
(document.getElementById("image"))
|}];

type button;
[@bs.set] external onclick: (button, unit => unit) => unit = "onclick";

let video = getVideoUnsafe();
let canvas = HTMLCanvasElement.create(window);

let getElementById: string => option(Dom.element) = [%raw
  {|
  function(id) {
    return document.getElementById(id);
  }
|}
];

let take: button = [%raw {|
(document.getElementById("take"))
|}];

let tracks: button = [%raw {|
(document.getElementById("tracks"))
|}];

let stop: button = [%raw {|
(document.getElementById("stop"))
|}];

let stream = ref(None);

take->onclick(() => {
  open HTMLCanvasElement;
  canvas->setWidth(video->HTMLVideoElement.videoWidth);
  canvas->setHeight(video->HTMLVideoElement.videoHeight);
  let ctx = canvas->getContext2d;
  ctx->PWA_CanvasRenderingContext2D.drawImage(
    `Video(video),
    ~dx=0.0,
    ~dy=0.0,
  );
  /* image->src(canvas->toDataURL); */
  canvas->toBlob
  |> then_(blob => blob->FileReader.toDataURL)
  |> then_(dataUrl => {
       image->src(dataUrl);
       resolve();
     })
  |> ignore;
});

let fetchBlob: string => Js.Promise.t(FileReader.Blob.t) = [%raw
  {|
function(url) {
  return fetch(url).then(res => res.blob())
}
|}
];

let createObjectURL: FileReader.Blob.t => string = [%raw
  {|
function(blob) {
  return URL.createObjectURL(blob);
}
|}
];

[@bs.set] external videoSrc: (HTMLVideoElement.t, string) => unit = "src";
/* let dataUrl = createObjectURL(blob) */

window
->navigator
->Navigator.mediaDevicesExn
->MediaDevices.getUserMediaUnsafe({
    "video": {
      "width": 320,
      "height": 240,
    },
    /* "audio": true */
  })
|> then_(media => {
     stream := Some(media);
     /* let clone = media->MediaStream.clone;
        Js.log2("clone", clone); */

     expectToEqual(media->MediaStream.id->Js.typeof, "string");
     expectToEqual(media->MediaStream.active, true);

     Js.log2("setting stream", media);
     video->HTMLVideoElement.setSrcObject(media);

     /* fetchBlob("/1.mp4")
        |> then_(blob => {
          blob->FileReader.toDataURL
        })
        |> then_(dataUrl => {
          video->videoSrc(dataUrl);
          resolve();
        })
         |> ignore; */

     resolve();
   });

stop->onclick(() => {
  let ts = (stream^)->Option.getExn->MediaStream.getTracks;
  ts->Array.forEach(MediaStreamTrack.stop);
  /* stream := None; */
});

tracks->onclick(() => {
  Js.log("tracks");
  let stream = (stream^)->Option.getExn;
  let ts = stream->MediaStream.getTracks;
  ts->Array.forEach(t => {
    open MediaStreamTrack;
    expectToEqual(t->id->Js.typeof, "string");
    expectToEqual(t->enabled->Js.typeof, "boolean");
    expectToEqual(t->kind->Js.typeof, "string");
    expectToEqual(t->label->Js.typeof, "string");
    expectToEqual(t->muted->Js.typeof, "boolean");
    expectToEqual(t->readyState->Js.typeof, "string");
    Js.log2("id", t->id);
    Js.log2("enabled", t->enabled);
    Js.log2("kind", t->kind);
    Js.log2("label", t->label);
    Js.log2("muted", t->muted);
    Js.log2("readyState", t->readyState);
    Js.log("---------");
  });

  let first = stream->MediaStream.getVideoTracks->Array.get(0)->Option.getExn;
  Js.log2(
    "by id",
    stream->MediaStream.getTrackById(first->MediaStreamTrack.id),
  );

  Js.log2("audio tracks", stream->MediaStream.getAudioTracks);
  Js.log2("video tracks", stream->MediaStream.getVideoTracks);
});

open HTMLInputElement;

let file: HTMLInputElement.t =
  getElementById("file")
  ->Option.flatMap(HTMLInputElement.asInputElement)
  ->Option.getExn;

expectToEqual(file->value, "");

file->HTMLInputElement.onchange(_ => {
  expectToEqual(
    file->files->Option.getExn->Array.length->Js.typeof,
    "number",
  );
  Js.log(file->files);

  switch (file->files->Option.getExn->Array.get(0)) {
  | Some(file) =>
    file->FileReader.File.asBlob->FileReader.toDataURL
    |> then_(dataUrl => {
         image->src(dataUrl);
         resolve();
       })
    |> ignore
  | None => Js.log("no files")
  };
});

expectToEqual(file->HTMLInputElement.files, Some([||]));

let date: HTMLInputElement.t =
  getElementById("date")
  ->Option.flatMap(HTMLInputElement.asInputElement)
  ->Option.getExn;
expectToEqual(date->files, None);
expectToEqual(date->value, "");

date->onchange(_ => {
  expectToEqual(date->value->Js.String.length, 10);
  expectToEqual(date->files, None);
});