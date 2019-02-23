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

module URL = PWA.URL;

let u1 = URL.make("http://a.b");

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
      expectToEqual(sub->PushSubscription.expirationTime->Js.typeof, "number"); 
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

module Notification = PWA.Notification;

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

let onUpdateFound = () =>
   Js.log("updatefound event");
 

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
        ServiceWorkerRegistration.updatefound, onUpdateFound);

      /* reg->ServiceWorkerRegistration.removeEventListener(ServiceWorkerRegistration.updatefound,
          onUpdateFound);*/
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
let canvas = HTMLCanvasElement.createElement(window);

expectToEqual(canvas->HTMLCanvasElement.asDomElement
  ->HTMLCanvasElement.asCanvasElement->Option.isSome, true);

/*let canvasStream = canvas->HTMLCanvasElement.captureStream(~frameRate=60.0, ());*/
/*[%debugger];*/

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
  canvas->toBlob(~type_="image/jpeg", ~quality=0.1, ())
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


     

let stopCamera = () => {
  let ts = (stream^)->Option.getExn->MediaStream.getTracks;
  ts->Array.forEach(MediaStreamTrack.stop);
  /* stream := None; */
}


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

     /* do not remove */
     /* let clone = media->MediaStream.clone;
        Js.log2("clone", clone); */

     expectToEqual(media->MediaStream.id->Js.typeof, "string");
     expectToEqual(media->MediaStream.active, true);

     Js.log2("setting stream", media); 
     video->HTMLVideoElement.setSrcObject(Some(media));

     stopCamera();

     /* do not remove */
      fetchBlob("/1.mp4")
        |> then_(blob => {
          blob->FileReader.toDataURL

          /*let dataUrl = URL.createObjectURL(`Blob(blob));
          expectToEqual(dataUrl->Js.typeof, "string");
          resolve(dataUrl)*/
        })
        |> then_(dataUrl => {
          video->HTMLVideoElement.setSrc(dataUrl);
          resolve();
        })
         |> ignore; 

     resolve();
   });


stop->onclick(() => {
  stopCamera();
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



open RTCPeerConnection;
let peer = RTCPeerConnection.make_(Js.Nullable.return(
  Configuration.make(~iceCandidatePoolSize=2, ())
));

expectToEqual(peer->canTrickleIceCandidates, None);
expectToEqual(peer->connectionState, "new");
expectToEqual(peer->currentLocalDescription, None);
expectToEqual(peer->currentRemoteDescription, None);
expectToEqual(peer->iceConnectionState->Js.typeof, "string");
expectToEqual(peer->iceGatheringState->Js.typeof, "string");
expectToEqual(peer->localDescription, None);
expectToEqual(peer->pendingLocalDescription, None);
expectToEqual(peer->remoteDescription, None);
expectToEqual(peer->pendingRemoteDescription, None);

generateCertificate(`Object({
  "name": "RSASSA-PKCS1-v1_5",
    "hash": "SHA-256",
    "modulusLength": 2048,
    "publicExponent": Js.Typed_array.Uint8Array.make([| 1, 0, 1 |])
}))
|> then_(cert => {
  expectToEqual(cert->PWA_RTCCertificate.expires->Js.typeof, "number");

  resolve();
})
|> catch(err => {
  Js.log(err);
  resolve();
})

expectToEqual(peer->getConfiguration->Configuration.iceCandidatePoolSize, Some(2));
peer->setConfiguration(Configuration.make(~iceCandidatePoolSize=3, ()));
expectToEqual(peer->getConfiguration->Configuration.iceCandidatePoolSize, Some(3));

expectToEqual(peer->getReceivers, [||]);
expectToEqual(peer->getSenders, [||]);

peer->getStats()
|> then_(stats => {
  Js.log2("stats", stats);
  resolve();
});



let audio: HTMLAudioElement.t = [%bs.raw {|
(document.querySelector("audio"))
|}];

/*audio->HTMLAudioElement.setPlaybackRate(5.0);*/
expectToEqual(audio->HTMLAudioElement.playbackRate, 1.0);


expectToEqual(audio->HTMLAudioElement.loop, false);
expectToEqual(audio->HTMLAudioElement.autoplay, false);
expectToEqual(audio->HTMLAudioElement.canPlayType("audio/mp3"), "probably");

expectToEqual(audio->HTMLAudioElement.asDomElement->
  HTMLAudioElement.asAudioElement->Option.isSome, true);
expectToEqual(audio->HTMLAudioElement.asDomElement->
  HTMLVideoElement.asVideoElement->Option.isSome, false);

/* do not remove */
/*let audioStream = audio->HTMLAudioElement.captureStream;*/







Js.log("sync OK, wait for async");