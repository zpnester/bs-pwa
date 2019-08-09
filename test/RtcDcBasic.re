open Belt;
open Js.Promise;
open PWA;

let window = Window.window;
let document = window->Window.document;

let dataChannelSend =
  document
  ->Document.querySelector("textarea#dataChannelSend")
  ->Option.getExn
  ->HTMLTextAreaElement.asTextAreaElement
  ->Option.getExn;

let dataChannelReceive =
  document
  ->Document.querySelector("textarea#dataChannelReceive")
  ->Option.getExn
  ->HTMLTextAreaElement.asTextAreaElement
  ->Option.getExn;

let startButton =
  document
  ->Document.querySelector("button#startButton")
  ->Option.getExn
  ->HTMLButtonElement.asButtonElement
  ->Option.getExn;
let sendButton =
  document
  ->Document.querySelector("button#sendButton")
  ->Option.getExn
  ->HTMLButtonElement.asButtonElement
  ->Option.getExn;
let closeButton =
  document
  ->Document.querySelector("button#closeButton")
  ->Option.getExn
  ->HTMLButtonElement.asButtonElement
  ->Option.getExn;

let localConnection = ref(None);
let remoteConnection = ref(None);
let sendChannel = ref(None);
let receiveChannel = ref(None);

let getLocalConnection = () => (localConnection^)->Option.getExn;
let getRemoteConnection = () => (remoteConnection^)->Option.getExn;

let getOtherPc = pc => {
  let pc1 = (localConnection^)->Option.getExn;
  let pc2 = (remoteConnection^)->Option.getExn;
  if (pc === pc1) {
    pc2;
  } else if (pc === pc2) {
    pc1;
  } else {
    failwith("invalid pc");
  };
};

let onIceCandidate = (pc, event) => {
  switch (event->RTCPeerConnectionIceEvent.candidate) {
  | None => ()
  | Some(candidate) =>
    getOtherPc(pc)
    ->RTCPeerConnection.addIceCandidate(candidate->RTCIceCandidate.toJSON)
    |> then_(() => {
         Js.log("AddIceCandidate success.");
         resolve();
       })
    |> catch(err => {
         Js.log2("Failed to add Ice Candidate: ", err);
         resolve();
       })
    |> ignore
  };
};

module PC = RTCPeerConnection;
module DC = RTCDataChannel;
module B = HTMLButtonElement;
module A = HTMLTextAreaElement;

let getSendChannel = () => (sendChannel^)->Option.getExn;
let getReceiveChannel = () => (receiveChannel^)->Option.getExn;

let onSendChannelStateChange = _ => {
  let readyState = getSendChannel()->DC.readyState;
  Js.log("Send channel state is: " ++ readyState);

  if (readyState == "open") {
    dataChannelSend->A.setDisabled(false);
    dataChannelSend->A.focus();
    sendButton->B.setDisabled(false);
    closeButton->B.setDisabled(false);
  } else {
    dataChannelSend->A.setDisabled(true);
    sendButton->B.setDisabled(true);
    closeButton->B.setDisabled(true);
  };
};

let onReceiveMessageCallback = event => {
  Js.log("Received Message");

  dataChannelReceive->A.setValue(
    event->MessageEvent.data->Js.Json.decodeString->Option.getExn,
  );
};

let onReceiveChannelStateChange = _ => {
  let readyState = getReceiveChannel()->DC.readyState;
  Js.log("Receive channel state is: " ++ readyState);
};

let gotDescription2 = desc => {
  getRemoteConnection()->PC.setLocalDescription(desc)
  |> then_(() => {
       Js.log2("Answer from remoteConnection", desc##sdp);
       getLocalConnection()->PC.setRemoteDescription(desc);
     })
  |> catch(err => {
       Js.log2("err", err);
       resolve();
     });
};

let receiveChannelCallback = event => {
  Js.log("Receive Channel Callback");
  let c = event##channel;
  receiveChannel := Some(c);

  c->DC.addEventListener(DC.message, onReceiveMessageCallback);
  c->DC.addEventListener(DC.open_, onReceiveChannelStateChange);
  c->DC.addEventListener_("close", onReceiveChannelStateChange);
};

let gotDescription1 = desc => {
  getLocalConnection()->PC.setLocalDescription(desc)
  |> then_(() => {
       Js.log2("Offer from localConnection", desc##sdp);
       getRemoteConnection()->PC.setRemoteDescription(desc);
     })
  |> then_(() => getRemoteConnection()->PC.createAnswer())
  |> then_(gotDescription2)
  |> catch(err => {
       Js.log2("Failed to create session description: ", err);
       resolve();
     });
};

let createConnection = () => {
  dataChannelSend->HTMLTextAreaElement.setPlaceholder("");

  let lc = RTCPeerConnection.make();
  localConnection := Some(lc);
  Js.log("Created local peer connection object localConnection");

  let sc =
    lc->RTCPeerConnection.createDataChannel(~label="sendDataChannel", ());
  sendChannel := Some(sc);
  Js.log("Created send data channel");

  lc->RTCPeerConnection.addEventListener(RTCPeerConnection.icecandidate, e =>
    onIceCandidate(lc, e)
  );
  sc->DC.addEventListener(DC.open_, onSendChannelStateChange);
  sc->DC.addEventListener_("close", onSendChannelStateChange);

  let rc = PC.make();
  remoteConnection := Some(rc);
  Js.log("Created remote peer connection object remoteConnection");

  rc->PC.addEventListener(PC.icecandidate, e => onIceCandidate(rc, e));
  rc->PC.addEventListener(PC.datachannel, receiveChannelCallback);

  lc->PC.createOffer()
  |> then_(desc => gotDescription1(desc))
  |> catch(err => {
       Js.log2("Failed to create session description: ", err);
       resolve();
     })
  |> then_(_ => {
       startButton->B.setDisabled(true);
       closeButton->B.setDisabled(false);
       resolve();
     })
  |> ignore;
};

let sendData = () => {
  let data = dataChannelSend->A.value;
  getSendChannel()->DC.send(DC.Data.string(data));
  Js.log("Sent Data: " ++ data);
};

let disableSendButton = () => {
  sendButton->B.setDisabled(true);
};

let enableStartButton = () => {
  startButton->B.setDisabled(false);
};

let closeDataChannels = () => {
  Js.log("Closing data channels");

  getSendChannel()->DC.close;
  Js.log("Closed data channel with label: " ++ getSendChannel()->DC.label);

  getReceiveChannel()->DC.close;
  Js.log("Closed data channel with label: " ++ getReceiveChannel()->DC.label);

  getLocalConnection()->PC.close;
  getRemoteConnection()->PC.close;

  localConnection := None;
  remoteConnection := None;

  Js.log("Closed peer connections");

  startButton->B.setDisabled(false);
  sendButton->B.setDisabled(true);
  closeButton->B.setDisabled(true);
  dataChannelSend->A.setValue("");
  dataChannelReceive->A.setValue("");
  dataChannelSend->A.setDisabled(true);

  disableSendButton();
  enableStartButton();
};

startButton->B.addEventListener_("click", _ => createConnection());
sendButton->B.addEventListener_("click", _ => sendData());
closeButton->B.addEventListener_("click", _ => closeDataChannels());