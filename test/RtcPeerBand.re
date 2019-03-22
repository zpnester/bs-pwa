open Belt;
open PWA;
open Js.Promise;

let window = Window.window;
let document = window->Window.document;
let navigator = window->Window.navigator;

let remoteVideo =
  document
  ->Document.querySelector("video#remoteVideo")
  ->Option.getExn
  ->HTMLVideoElement.asVideoElement
  ->Option.getExn;

let localVideo =
  document
  ->Document.querySelector("video#localVideo")
  ->Option.getExn
  ->HTMLVideoElement.asVideoElement
  ->Option.getExn;

let callButton =
  document
  ->Document.querySelector("button#callButton")
  ->Option.getExn
  ->HTMLButtonElement.asButtonElement
  ->Option.getExn;

let hangupButton =
  document
  ->Document.querySelector("button#hangupButton")
  ->Option.getExn
  ->HTMLButtonElement.asButtonElement
  ->Option.getExn;

let bandwidthSelector =
  document
  ->Document.querySelector("select#bandwidth")
  ->Option.getExn
  ->HTMLSelectElement.asSelectElement
  ->Option.getExn;

let pc1 = ref(None);
let pc2 = ref(None);

let localStream = ref(None);

let getOtherPc = pc => {
  let pc1 = (pc1^)->Option.getExn;
  let pc2 = (pc2^)->Option.getExn;
  if (pc === pc1) {
    pc2;
  } else if (pc === pc2) {
    pc1;
  } else {
    failwith("invalid pc");
  };
};

let onIceCandidate = (pc, e) => {
  let other = getOtherPc(pc);
  switch (e->RTCPeerConnectionIceEvent.candidate) {
  | Some(candidate) =>
    other->RTCPeerConnection.addIceCandidate(
      candidate->RTCIceCandidate.toJSON,
    )
    |> then_(_ => {
         Js.log("AddIceCandidate success.");
         resolve();
       })
    |> catch(err => {
         Js.log2("Failed to add ICE Candidate: ", err);
         resolve();
       })
    |> ignore
  | None => ()
  };
};

let getPc1 = () => (pc1^)->Option.getExn;
let getPc2 = () => (pc2^)->Option.getExn;

let gotRemoteStream = e => {
  /* TODO compare OK? */
  let s1 = e##streams->Array.get(0)->Option.getExn;
  if (remoteVideo->HTMLVideoElement.srcObject != Some(s1)) {
    remoteVideo->HTMLVideoElement.setSrcObject(Some(s1));
  };
};

let maxBandwidth = ref(0);

let onError = err => {
  Js.log2("error", err);
};

let updateBandwidthRestriction: (string, int) => string = [%raw
  {|
function(sdp, bandwidth) {
  let modifier = 'AS';
  if (adapter.browserDetails.browser === 'firefox') {
    bandwidth = (bandwidth >>> 0) * 1000;
    modifier = 'TIAS';
  }
  if (sdp.indexOf('b=' + modifier + ':') === -1) {
    // insert b= after c= line.
    sdp = sdp.replace(/c=IN (.*)\r\n/, 'c=IN $1\r\nb=' + modifier + ':' + bandwidth + '\r\n');
  } else {
    sdp = sdp.replace(new RegExp('b=' + modifier + ':.*\r\n'), 'b=' + modifier + ':' + bandwidth + '\r\n');
  }
  return sdp;
}
|}
];

let updateDesc = desc => {
  let type_ = desc##_type->Js.Nullable.toOption->Option.getExn;
  let sdp =
    desc##sdp
    ->Js.Nullable.toOption
    ->Option.getExn
    ->updateBandwidthRestriction(maxBandwidth^);
  {"_type": Js.Nullable.return(type_), "sdp": Js.Nullable.return(sdp)};
};

let gotDescription2 = desc => {
  RTCPeerConnection.(
    getPc2()->setLocalDescription(desc)
    |> then_(() => {
         Js.log2("Answer from pc2", desc##sdp);

         (
           if (maxBandwidth^ > 0) {
             getPc1()->setRemoteDescription(updateDesc(desc));
           } else {
             getPc1()->setRemoteDescription(desc);
           }
         )
         |> catch(err => {
              onError(err);
              resolve();
            });
       })
  );
};

let gotDescription1 = desc => {
  Js.log2("Offer from pc1", desc##sdp);

  getPc1()->RTCPeerConnection.setLocalDescription(desc)
  |> then_(() => getPc2()->RTCPeerConnection.setRemoteDescription(desc))
  |> then_(() => getPc2()->RTCPeerConnection.createAnswer())
  |> then_(a => gotDescription2(a))
  |> catch(e => {
       onError(e);
       resolve();
     });
};

let gotStream = s => {
  let pc1 = getPc1();

  hangupButton->HTMLButtonElement.setDisabled(false);
  Js.log("Received local stream");
  localStream := Some(s);
  localVideo->HTMLVideoElement.setSrcObject(Some(s));
  s
  ->MediaStream.getTracks
  ->Array.forEach(t => pc1->RTCPeerConnection.addTrack(t, s) |> ignore);

  Js.log("Adding Local Stream to peer connection");

  pc1->RTCPeerConnection.createOffer()
  |> then_(desc => gotDescription1(desc))
  |> catch(err => {
       onError(err);
       resolve();
     });
};

hangupButton->HTMLButtonElement.setDisabled(true);

callButton->HTMLButtonElement.addEventListener_("click", _ => {
  open RTCPeerConnection;

  callButton->HTMLButtonElement.setDisabled(true);
  bandwidthSelector->HTMLSelectElement.setDisabled(false);

  Js.log("Starting call");
  // servers
  let pc1_ = RTCPeerConnection.make();
  pc1 := Some(pc1_);
  Js.log("Created local peer connection object pc1");
  pc1_->addEventListener(icecandidate, onIceCandidate(pc1_));

  let pc2_ = RTCPeerConnection.make();
  pc2 := Some(pc2_);
  Js.log("Created remote peer connection object pc2");

  pc2_->addEventListener(icecandidate, onIceCandidate(pc2_));
  pc2_->addEventListener(track, gotRemoteStream);

  Js.log("Requesting local stream");
  navigator
  ->Navigator.mediaDevices
  ->Option.getExn
  ->MediaDevices.getUserMedia({"video": true})
  |> then_(s => gotStream(s))
  |> catch(e => {
       Js.log(e);
       window->Window.alert("getUserMedia() error");
       resolve();
     })
  |> ignore;
});

hangupButton->HTMLButtonElement.addEventListener_("click", _ => {
  Js.log("Ending call");

  (localStream^)
  ->Option.getExn
  ->MediaStream.getTracks
  ->Array.forEach(t => t->MediaStreamTrack.stop);

  getPc1()->RTCPeerConnection.close;
  getPc2()->RTCPeerConnection.close;
  pc1 := None;
  pc2 := None;
  hangupButton->HTMLButtonElement.setDisabled(true);
  callButton->HTMLButtonElement.setDisabled(false);
  bandwidthSelector->HTMLSelectElement.setDisabled(true);
});

let setParameters: PWA_RTCRtpSender.t => Js.Promise.t(unit) = [%raw
  {|
function(sender) {
  if ((adapter.browserDetails.browser === 'chrome' ||
       (adapter.browserDetails.browser === 'firefox' &&
        adapter.browserDetails.version >= 64)) &&
      'RTCRtpSender' in window &&
      'setParameters' in window.RTCRtpSender.prototype) {
    const parameters = sender.getParameters();
    if (!parameters.encodings) {
      parameters.encodings = [{}];
    }
    if (bandwidth === 'unlimited') {
      delete parameters.encodings[0].maxBitrate;
    } else {
      parameters.encodings[0].maxBitrate = bandwidth * 1000;
    }
    return sender.setParameters(parameters);
  }
}
|}
];

let fallbackDescr:
  (RTCPeerConnection.t, string) => RTCSessionDescription.Init.t = [%raw
  {|
function(pc1, bandwidth) {

  function updateBandwidthRestriction(sdp, bandwidth) {
    let modifier = 'AS';
    if (adapter.browserDetails.browser === 'firefox') {
      bandwidth = (bandwidth >>> 0) * 1000;
      modifier = 'TIAS';
    }
    if (sdp.indexOf('b=' + modifier + ':') === -1) {
      // insert b= after c= line.
      sdp = sdp.replace(/c=IN (.*)\r\n/, 'c=IN $1\r\nb=' + modifier + ':' + bandwidth + '\r\n');
    } else {
      sdp = sdp.replace(new RegExp('b=' + modifier + ':.*\r\n'), 'b=' + modifier + ':' + bandwidth + '\r\n');
    }
    return sdp;
  }

  function removeBandwidthRestriction(sdp) {
    return sdp.replace(/b=AS:.*\r\n/, '').replace(/b=TIAS:.*\r\n/, '');
  }

  const desc = {
    type: pc1.remoteDescription.type,
    sdp: bandwidth === 'unlimited'
      ? removeBandwidthRestriction(pc1.remoteDescription.sdp)
      : updateBandwidthRestriction(pc1.remoteDescription.sdp, bandwidth)
  };
  console.log('Applying bandwidth restriction to setRemoteDescription:\n' +
    desc.sdp);
  return desc;
}
|}
];

bandwidthSelector->HTMLSelectElement.addEventListener_("change", _ => {
  open HTMLSelectElement;

  bandwidthSelector->setDisabled(true);
  let options = bandwidthSelector->options;
  let bandwidth =
    options
    ->Array.get(bandwidthSelector->selectedIndex)
    ->Option.getExn
    ->HTMLOptionElement.value;

  let sender =
    getPc1()->RTCPeerConnection.getSenders->Array.get(0)->Option.getExn;

  setParameters(sender)
  |> catch(err => {
       Js.log(err);
       resolve();
     })
  |> then_(() => {
       bandwidthSelector->setDisabled(false);
       resolve();
     })
  |> ignore;

  /* Fallback to the SDP munging with local renegotiation way of limiting the bandwidth. */
  getPc1()->RTCPeerConnection.createOffer()
  |> then_(offer => getPc1()->RTCPeerConnection.setLocalDescription(offer))
  |> then_(() => {
       let desc = fallbackDescr(getPc1(), bandwidth);
       getPc1()->RTCPeerConnection.setRemoteDescription(desc);
     })
  |> catch(err => {
       onError(err);
       resolve();
     })
  |> ignore;
});
