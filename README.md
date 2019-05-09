# bs-pwa

Various browser APIs for BuckleScript

## Install

```
npm i @zpnester/bs-filereader@^0.3.0
npm i @zpnester/bs-pwa
```

bsconfig.json
```
"bs-dependencies": [
  "@zpnester/bs-pwa"
]
```

* Notification
* ServiceWorkerRegistration
* HTMLAudioElement
* HTMLVideoElement
* MediaStream
* MediaStreamTrack
* Client
* WindowClient
* ServiceWorkerGlobalScope
* DedicatedWorkerGlobalScope
* PWA_PushManager
* RTCPeerConnection
* RTCDataChannel
* TextDecoder
* Worker

## Examples

### Video element with ReasonReact 7

```reason
open React;
open PWA;
open Belt;

module App = {
  [@react.component]
  let make = () => {
    let videoRef = useRef(Js.Nullable.undefined);

    let onPlayClick = _ => {
      open HTMLVideoElement;

      let video =
        videoRef
        ->Ref.current
        ->Js.Nullable.toOption
        ->Option.flatMap(asVideoElement)
        ->Option.getExn;
      video->play |> ignore;
    };

    let onPauseClick = _ => {
      open HTMLVideoElement;

      let video =
        videoRef
        ->Ref.current
        ->Js.Nullable.toOption
        ->Option.flatMap(asVideoElement)
        ->Option.getExn;
      video->pause;
    };

    <>
      <video
        ref={videoRef->ReactDOMRe.Ref.domRef}
        src="https://www.w3schools.com/html/mov_bbb.mp4"
      />
      <br />
      <button onClick=onPlayClick> {string("Play")} </button>
      <button onClick=onPauseClick> {string("Pause")} </button>
    </>;
  };
};

ReactDOMRe.renderToElementWithId(<App />, "app");
```


### Worker

#### From Window

```reason
open PWA;
open Worker;

let worker = Worker.make("doWork.js");
worker->addEventListener(message, e =>
  MessageEvent.(
    switch (e->data->Js.Json.decodeString) {
    | None => ()
    | Some(s) => Js.log("Worker said: " ++ s)
    }
  )
);
worker->postMessage("Hello World");
```

#### From Worker

```reason
open PWA;
open DedicatedWorkerGlobalScope;

self_->addEventListener(message, e =>
  PWA_MessageEvent.(self_->postMessage(e->data))
);
```