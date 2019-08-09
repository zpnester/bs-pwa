[%%debugger.chrome];

open PWA;
open WindowPrelude;
open Window;
open Navigator;
open Belt;
open ServiceWorkerContainer;
open ServiceWorker;
open Js.Promise;
open Expect;

let isEdge: bool = [%raw {|
(navigator.appVersion.indexOf("Edge") != -1)
|}];
let isMacOs: bool = [%raw
  {|
(navigator.appVersion.indexOf("Macintosh") != -1)
|}
];

let isSafari = isMacOs;

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

// window
// ->navigator
// ->Navigator.serviceWorker
// ->Option.getExn
// ->ServiceWorkerContainer.getRegistration
// |> then_(reg => {
//      let reg = reg->Option.getExn;
//      reg
//      ->ServiceWorkerRegistration.pushManager
//      ->Option.getExn
//      ->PushManager.getSubscription;
//    })
// |> then_(sub => {
//      let sub = sub->Option.getExn;

//      expectToEqual(sub->PushSubscription.endpoint->Js.typeof, "string");
//      expectToEqual(sub->PushSubscription.expirationTime->Js.typeof, "number");
//      expectToEqual(sub->PushSubscription.expirationTime->Option.isNone, true);
//      expectToEqual(
//        sub->PushSubscription.getKey("auth")->isArrayBuffer,
//        true,
//      );
//      expectToEqual(sub->PushSubscription.options->Js.typeof, "object");
//      Js.log2("options", sub->PushSubscription.options);

//      Js.log2("toJSON", sub->PushSubscription.toJSON);
//      expectToEqual(sub->PushSubscription.toJSON->Js.typeof, "object");
//      resolve();
//    });

module Notification = PWA.Notification;

Notification.requestPermission()
|> then_(p => {
     expectToEqual(p, `granted);
     let opts = Notification.Options.make(~body="hello", ());
     let n = Notification.make2("hi", opts);
     n->Notification.setOnclick(_ => Js.log("clicked"));

     expectToEqual(n->Notification.icon, Some(""));
     expectToEqual(n->Notification.title, Some("hi"));
     expectToEqual(n->Notification.body, Some("hello"));
     // undefined in FF
     //  expectToEqual(n->Notification.actions, Some([||]));
     resolve();
   })
|> ignore;

let onUpdateFound = () => Js.log("updatefound event");

switch (window()->navigator->serviceWorker) {
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
         ServiceWorkerRegistration.updatefound,
         onUpdateFound,
       );
       resolve();
     })
  |> catch(e => {
       Js.log2("err", e);
       failwith("fail");
     })
| None => resolve()
};

switch (window()->navigator->serviceWorker->Option.flatMap(controller)) {
| Some(sw) =>
  Js.Global.setTimeout(() => sw->postMessage("hello"), 3000) |> ignore;
  Js.log("posted");
| None => Js.log("no sw")
};

type img;
[@bs.set] external setSrc: (img, string) => unit = "src";

let image = [%bs.raw {|
(document.getElementById("image"))
|}];

let video =
  window()
  ->document
  ->Document.getElementById("video")
  ->Option.flatMap(HTMLVideoElement.asVideoElement)
  ->Option.getExn;

let canvas = window()->document->HTMLCanvasElement.createElement;

expectToEqual(
  canvas
  ->HTMLCanvasElement.asDomElement
  ->HTMLCanvasElement.asCanvasElement
  ->Option.isSome,
  true,
);

/*let canvasStream = canvas->HTMLCanvasElement.captureStream(~frameRate=60.0, ());*/

let take =
  window()
  ->Window.document
  ->Document.getElementById("take")
  ->Option.flatMap(HTMLButtonElement.asButtonElement)
  ->Option.getExn;

let tracks =
  window()
  ->Window.document
  ->Document.getElementById("tracks")
  ->Option.flatMap(HTMLButtonElement.asButtonElement)
  ->Option.getExn;

let stop =
  window()
  ->Window.document
  ->Document.getElementById("stop")
  ->Option.flatMap(HTMLButtonElement.asButtonElement)
  ->Option.getExn;

let stream = ref(None);

take->HTMLButtonElement.addEventListener_("click", _ => {
  open HTMLCanvasElement;
  canvas->setWidth(video->HTMLVideoElement.videoWidth);
  canvas->setHeight(video->HTMLVideoElement.videoHeight);
  let ctx = canvas->getContext2d;
  ctx->PWA_CanvasRenderingContext2D.drawImage(
    `Video(video),
    ~dx=0.0,
    ~dy=0.0,
  );
  //  image->setSrc(canvas->toDataURL2(~type_="image/jpeg", ~quality=0.1));
  canvas->toBlob2(~type_="image/jpeg", ~quality=0.1)
  |> then_(blob => blob->FileReader.toDataURL)
  |> then_(dataUrl => {
       image->setSrc(dataUrl);
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
};

window()
->navigator
->Navigator.mediaDevices
->Option.getExn
->MediaDevices.getUserMedia({
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

     //  stopCamera();

     /* do not remove */
     fetchBlob("/1.mp4")
     |> then_(blob => blob->FileReader.toDataURL)
     /*let dataUrl = URL.createObjectURL(`Blob(blob));
       expectToEqual(dataUrl->Js.typeof, "string");
       resolve(dataUrl)*/
     |> then_(dataUrl => {
          video->HTMLVideoElement.setSrc(dataUrl);
          resolve();
        })
     |> ignore;

     resolve();
   });

stop->HTMLButtonElement.addEventListener_("click", _ => stopCamera());

tracks->HTMLButtonElement.addEventListener_("click", _ => {
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

let file =
  window()
  ->document
  ->Document.getElementById("file")
  ->Option.flatMap(HTMLInputElement.asInputElement)
  ->Option.getExn;

expectToEqual(file->HTMLInputElement.value, "");

file->HTMLInputElement.addEventListener_("change", _ => {
  expectToEqual(
    file->HTMLInputElement.files->Option.getExn->Array.length->Js.typeof,
    "number",
  );
  Js.log(file->HTMLInputElement.files);

  switch (file->HTMLInputElement.files->Option.getExn->Array.get(0)) {
  | Some(file) =>
    file->FileReader.File.asBlob->FileReader.toDataURL
    |> then_(dataUrl => {
         image->setSrc(dataUrl);
         resolve();
       })
    |> ignore
  | None => Js.log("no files")
  };
});

expectToEqual(file->HTMLInputElement.files, Some([||]));

let date =
  window()
  ->document
  ->Document.getElementById("date")
  ->Option.flatMap(HTMLInputElement.asInputElement)
  ->Option.getExn;

expectToEqual(date->HTMLInputElement.files, None);
expectToEqual(date->HTMLInputElement.value, "");

date->HTMLInputElement.addEventListener_("change", _ => {
  expectToEqual(date->HTMLInputElement.value->Js.String.length, 10);
  expectToEqual(date->HTMLInputElement.files, None);
});

Js.Global.setTimeout(
  () => {
    open RTCPeerConnection;
    let config = Configuration.make(~iceCandidatePoolSize=2, ());
    let peer = RTCPeerConnection.make1(config);

    expectToEqual(peer->canTrickleIceCandidates, None);

    expectToEqual(peer->connectionState, Some("new"));
    expectToEqual(peer->currentLocalDescription, None);
    expectToEqual(peer->currentRemoteDescription, None);
    expectToEqual(peer->iceConnectionState->Js.typeof, "string");
    expectToEqual(peer->iceGatheringState->Js.typeof, "string");
    expectToEqual(peer->localDescription, None);
    expectToEqual(peer->pendingLocalDescription, None);
    expectToEqual(peer->remoteDescription, None);
    expectToEqual(peer->pendingRemoteDescription, None);

    // expectToEqual(peer->canTrickleIceCandidates->Js.typeof, "boolean");
    expectToEqual(peer->iceConnectionState->Js.typeof, "string");
    expectToEqual(peer->iceGatheringState->Js.typeof, "string");
    expectToEqual(peer->signalingState->Js.typeof, "string");

    peer->getStats
    |> then_(stats => {
         Js.log2("stats", stats);
         resolve();
       })
    |> ignore;

    if (!isEdge) {
      // TODO remove, test better
      // peer->RTCPeerConnection.addEventListener(datachannel, e => {
      //   Js.log(e##channel);
      //   expectToEqual(e##channel->Js.typeof, "object1");
      // });

      let dc = peer->createDataChannel("dc1");

      expectToEqual(dc->RTCDataChannel.binaryType->Js.typeof, "string");
      expectToEqual(dc->RTCDataChannel.bufferedAmount->Js.typeof, "number");
      expectToEqual(
        dc->RTCDataChannel.bufferedAmountLowThreshold->Js.typeof,
        "number",
      );
      // expectToEqual(dc->RTCDataChannel.id->Js.typeof, "number");
      expectToEqual(dc->RTCDataChannel.label->Js.typeof, "string");
      // expectToEqual(dc->RTCDataChannel.maxPacketLifeTime->Js.typeof, "number");
      // expectToEqual(dc->RTCDataChannel.maxRetransmits->Js.typeof, "number");
      // expectToEqual(dc->RTCDataChannel.negotiated->Js.typeof, "boolean");
      expectToEqual(dc->RTCDataChannel.ordered->Js.typeof, "boolean");
      expectToEqual(dc->RTCDataChannel.protocol->Js.typeof, "string");
    };

    if (!isEdge && !isMacOs) {
      let _ =
        generateCertificate(
          `Object({
            "name": "RSASSA-PKCS1-v1_5",
            "hash": "SHA-256",
            "modulusLength": 2048,
            "publicExponent": Js.Typed_array.Uint8Array.make([|1, 0, 1|]),
          }),
        )
        |> then_(cert => {
             expectToEqual(
               cert->PWA_RTCCertificate.expires->Js.typeof,
               "number",
             );

             resolve();
           })
        |> catch(err => {
             Js.log(err);
             resolve();
           })
        |> ignore;

      ();
    };
  },
  0,
);

// does not work in FF
// expectToEqual(
//   peer->getConfiguration->Configuration.iceCandidatePoolSize,
//   Some(2),
// );

// does not work in FF
// peer->setConfiguration(Configuration.make(~iceCandidatePoolSize=3, ()));

// does not work in FF
// expectToEqual(
//   peer->getConfiguration->Configuration.iceCandidatePoolSize,
//   Some(3),
// );

// expectToEqual(peer->getReceivers, [||]);
// expectToEqual(peer->getSenders, [||]);

let audio =
  window()
  ->document
  ->Document.querySelector("audio")
  ->Option.getExn
  ->HTMLAudioElement.asAudioElement
  ->Option.getExn;

/*audio->HTMLAudioElement.setPlaybackRate(5.0);*/
expectToEqual(audio->HTMLAudioElement.playbackRate, 1.0);

expectToEqual(audio->HTMLAudioElement.loop, false);
expectToEqual(audio->HTMLAudioElement.autoplay, false);
let canPlayMp3 = audio->HTMLAudioElement.canPlayType("audio/mp3");
expectToEqual(canPlayMp3 == "probably" || canPlayMp3 == "maybe", true);

expectToEqual(
  audio
  ->HTMLAudioElement.asDomElement
  ->HTMLAudioElement.asAudioElement
  ->Option.isSome,
  true,
);
expectToEqual(
  audio
  ->HTMLAudioElement.asDomElement
  ->HTMLVideoElement.asVideoElement
  ->Option.isSome,
  false,
);

/* do not remove */
/*let audioStream = audio->HTMLAudioElement.captureStream;*/

expectToEqual(window()->document->Document.querySelectorAll("smth"), [||]);
expectToEqual(
  window()->document->Document.querySelectorAll("video")->Js.Array.length,
  1,
);
expectToEqual(
  window()->document->Document.getElementById("take")->Option.isSome,
  true,
);
expectToEqual(
  window()->document->Document.getElementById("take1")->Option.isSome,
  false,
);
expectToEqual(
  window()->document->Document.querySelector("#take")->Option.isSome,
  true,
);
expectToEqual(
  window()->document->Document.querySelector("#take1")->Option.isSome,
  false,
);

let input =
  window()
  ->document
  ->HTMLInputElement.createElement
  ->HTMLInputElement.asDomElement
  ->HTMLInputElement.asInputElement
  ->Option.getExn;

let elem =
  window()
  ->document
  ->Document.createElement("input")
  ->HTMLInputElement.asInputElement
  ->Option.getExn;

Js.log("sync OK, wait for async");
/* window->Window.alertAny(true); */

let window = "";
Js.log(window);

WindowPrelude.window()->Window.alert("test");

let window = 1;

let blob = FileReader.Blob.make([||]);
let objectUrl = URL.createObjectURL(`Blob(blob));
Js.log(objectUrl);