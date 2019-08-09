[%%debugger.chrome];

open PWA;
open WindowPrelude;
open Belt;
open Js.Promise;
open Expect;

let document = window_->Window.document;

let p = RTCPeerConnection.make();

let getMedia = () =>
  window_
  ->Window.navigator
  ->Navigator.mediaDevices
  ->Option.getExn
  ->MediaDevices.getUserMedia({"video": true});

let alice1 =
  document
  ->Document.querySelector("#alice1")
  ->Option.getExn
  ->HTMLVideoElement.asVideoElement
  ->Option.getExn;
let alice2 =
  document
  ->Document.querySelector("#alice2")
  ->Option.getExn
  ->HTMLVideoElement.asVideoElement
  ->Option.getExn;
let bob1 =
  document
  ->Document.querySelector("#bob1")
  ->Option.getExn
  ->HTMLVideoElement.asVideoElement
  ->Option.getExn;
let bob2 =
  document
  ->Document.querySelector("#bob2")
  ->Option.getExn
  ->HTMLVideoElement.asVideoElement
  ->Option.getExn;

let signalChannel = () => {
  let handler = ref(None);

  {
    as _;
    pub on = h => {
      handler := Some(h);
    };
    pub send = msg => {
      Js.Global.setTimeout(() => (handler^)->Option.getExn(msg), 0) |> ignore;
    }
  };
};

let make = (name, localVideo, remoteVideo, myChannel, otherChannel) => {
  open RTCPeerConnection;
  let iceServers = [|
    RTCIceServer.make(~urls=[|"stun://stun3.l.google.com:19302"|], ()),
  |];
  let config = Configuration.make(~iceServers, ());
  // let pc = RTCPeerConnection.make(~config, ());
  let pc = RTCPeerConnection.make();

  pc->RTCPeerConnection.addEventListener(connectionstatechange, e =>
    Js.log2("connectionstatechange", e)
  );

  pc->addEventListener(
    icecandidate,
    e => {
      Js.log(name ++ " icecandidate");

      switch (e->RTCPeerConnectionIceEvent.candidate) {
      | None => Js.log(name ++ " icecandidate none")
      | Some(c) =>
        Js.log2(name ++ " icecandidate", c->PWA_RTCIceCandidate.toJSON);
        otherChannel#send(`candidate(c->PWA_RTCIceCandidate.toJSON));
      };
    },
  );

  pc->addEventListener(
    track,
    e => {
      Js.log(name ++ " ontrack");
      let stream = e##streams->Array.get(0)->Option.getExn;

      switch (remoteVideo->HTMLVideoElement.srcObject) {
      | None =>
        remoteVideo->HTMLVideoElement.setSrcObject(Some(stream));
        remoteVideo->HTMLVideoElement.play |> ignore;
      | _ => ()
      };
    },
  );

  myChannel#on(msg => {
    Js.log2(name ++ " recv msg", msg);
    switch (msg) {
    | `offer(desc) =>
      pc->setRemoteDescription(desc)
      |> then_(_ => getMedia())
      |> then_(stream => {
           stream
           ->MediaStream.getTracks
           ->Array.forEach(track =>
               pc->addTrack_(track, [|stream|]) |> ignore
             );
           pc->createAnswer;
         })
      |> then_(answer => pc->setLocalDescription(answer))
      |> then_(_ => {
           otherChannel#send(
             `answer(
               pc
               ->localDescription
               ->Option.getExn
               ->PWA_RTCSessionDescription.toJSON,
             ),
           );
           resolve();
         })
      |> ignore

    | `answer(desc) => pc->setRemoteDescription(desc) |> ignore

    | `candidate(c) => pc->addIceCandidate(c) |> ignore
    };
  });

  getMedia()
  |> then_(stream => {
       localVideo->HTMLVideoElement.setSrcObject(Some(stream));
       localVideo->HTMLVideoElement.play |> ignore;
       resolve();
     })
  |> ignore;

  let start = () => {
    getMedia()
    |> then_(stream => {
         stream
         ->MediaStream.getTracks
         ->Array.forEach(track => pc->addTrack(track, stream) |> ignore);

         pc->createOffer
         |> then_(descr => pc->setLocalDescription(descr))
         |> then_(_ => {
              otherChannel#send(
                `offer(
                  pc
                  ->localDescription
                  ->Option.getExn
                  ->PWA_RTCSessionDescription.toJSON,
                ),
              );
              resolve();
            });
       })
    |> ignore;
  };

  {as _; pub start = start};
};

let aliceChannel = signalChannel();
let bobChannel = signalChannel();

let alice = make("Alice", alice1, alice2, aliceChannel, bobChannel);
let bob = make("Bob", bob1, bob2, bobChannel, aliceChannel);

alice#start();

Js.log("end of rtc.js");