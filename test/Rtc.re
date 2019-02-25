
[%%debugger.chrome]

open PWA;
open Belt;
open Js.Promise;
open WindowGlobalScope;
open HTMLVideoElement;
open Expect;


let p = RTCPeerConnection.make();



let qs: string => HTMLVideoElement.t = [%bs.raw {|
function(s) {
	var el = document.querySelector(s);
	if (!el) {
		throw "el not found";
	}
	return el;
}
|}];

let getMedia = () => window->navigator
	->Navigator.mediaDevices
	->Option.getExn
	->MediaDevices.getUserMedia({"video": true});
 

let alice1 = qs("#alice1");
let alice2 = qs("#alice2");	
let bob1 = qs("#bob1");
let bob2 = qs("#bob2");



let signalChannel = () => {

	let handler = ref(None);

	{
		pub on =  h => { handler := Some(h)};
		pub send = msg => {
			Js.Global.setTimeout(() => {
				(handler^ ->Option.getExn)(msg);
			}, 0) |> ignore;
		};
	}

};



let make = (name, localVideo, remoteVideo, myChannel, otherChannel) => {
	open RTCPeerConnection;
	let iceServers =  [|RTCIceServer.make(~urls=[|"stun://stun3.l.google.com:19302"|], ())|];
	let config = Configuration.make(~iceServers, ());
	let pc = RTCPeerConnection.make(~config, ());


	pc->addEventListener(icecandidate, e => {
		Js.log2(name ++ " icecandidate");

		switch (e##candidate->Js.Nullable.toOption) {
			| None => Js.log(name ++ " icecandidate none");
			| Some(c) => 
				Js.log2(name ++ " icecandidate", c->PWA_RTCIceCandidate.toJSON)
				otherChannel#send(`candidate(c->PWA_RTCIceCandidate.toJSON))
		}
		
	});

	pc->addEventListener(track, e => {
		Js.log(name ++ " ontrack");
		let stream = e##streams->Array.get(0)->Option.getExn;

		switch (remoteVideo->srcObject) {
			| None => 
				remoteVideo->setSrcObject(Some(stream));
				remoteVideo->play |> ignore;
			| _ => ()
		}
	});

	myChannel#on(msg => {
		Js.log2(name ++ " recv msg", msg);
		switch (msg) {
			| `offer(desc) =>
				pc->setRemoteDescription(desc)
				|> then_(_ => {
					getMedia()
				})
				|> then_(stream => {
					stream->MediaStream.getTracks->Array.forEach(track => {
						pc->addTrack(track, stream) |> ignore;
					})
					pc->createAnswer()
				})
				|> then_(answer => {
					pc->setLocalDescription(answer)
				})
				|> then_(_ => {
					otherChannel#send(`answer(pc->localDescription->Option.getExn->PWA_RTCSessionDescription.toJSON));
					resolve();
				}) |> ignore;

			| `answer(desc) =>
				pc->setRemoteDescription(desc) |> ignore

			| `candidate(c) =>
				pc->addIceCandidate(c) |> ignore;
		}
	});

	getMedia()
	|> then_(stream => {
		localVideo->setSrcObject(Some(stream));
		localVideo->play |> ignore;
		resolve();
	}) |> ignore;


	let start = () => {
		getMedia()
		|> then_(stream => {
			stream->MediaStream.getTracks->Array.forEach(track => {
				pc->addTrack(track, stream) |> ignore;
			})

			pc->createOffer()
			|> then_(descr => {
				pc->setLocalDescription(descr)
			})
			|> then_(descr => {
				otherChannel#send(`offer(pc->localDescription->Option.getExn->PWA_RTCSessionDescription.toJSON));
				resolve();
			})
		}) |> ignore;
	};

	{
		pub start = start;
	}
}


let aliceChannel = signalChannel();
let bobChannel = signalChannel();

let alice = make("Alice", alice1, alice2, aliceChannel, bobChannel);
let bob = make("Bob", bob1, bob2, bobChannel, aliceChannel);


alice#start();



Js.log("end of rtc.js");