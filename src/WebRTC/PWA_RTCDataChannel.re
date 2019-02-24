

type t;


module Init = {
	type t;

	[@bs.obj] external make: (
		~ordered: bool=?,
		~maxPacketLifeTime: int=?,
		~maxRetransmits: int=?,
		~protocol: string=?,
		~negotiated: bool=?,
		~id: int=?,
		unit) => t = "";
}

/* TODO test */
[@bs.get] external binaryType: t => string = "binaryType";
[@bs.set] external setBinaryType: (t, string) => unit = "binaryType";

/* TODO test */
[@bs.get] external bufferedAmount: t => int = "bufferedAmount";

/* TODO test */
[@bs.get] external bufferedAmountLowThreshold: t => int = "bufferedAmountLowThreshold";
[@bs.set] external setBufferedAmountLowThreshold: (t, int) => unit = "bufferedAmountLowThreshold";

/* TODO test */
[@bs.get] external id: t => int = "id";

/* TODO test */
[@bs.get] external label : t => string = "label";


/* TODO test */
[@bs.get] external maxPacketLifeTime_ : t => Js.Null.t(int) = "maxPacketLifeTime";
let maxPacketLifeTime = self => maxPacketLifeTime_(self)->Js.Null.toOption;

/* TODO test */
[@bs.get] external maxRetransmits_ : t => Js.Null.t(int) = "maxRetransmits";
let maxRetransmits = self => maxRetransmits_(self)->Js.Null.toOption;

/* TODO test */
[@bs.get] external negotiated : t => bool= "negotiated";

/* TODO test */
[@bs.get] external ordered : t => bool= "ordered";

/* TODO test */
[@bs.get] external protocol : t => string= "protocol";

/* TODO test */
[@bs.get] external readyState : t => string= "readyState";

/* TODO test all */
let bufferedamountlow: PWA_EventType.t(t, PWA_Event.t) = PWA_EventType.unsafe("bufferedamountlow");

/* name clash with close method */
let closeEvent: PWA_EventType.t(t, PWA_Event.t) = PWA_EventType.unsafe("close");

let error: PWA_EventType.t(t, PWA_ErrorEvent.t) = PWA_EventType.unsafe("error");

let message: PWA_EventType.t(t, PWA_MessageEvent.t) = PWA_EventType.unsafe("message");

let open_: PWA_EventType.t(t, PWA_Event.t) = PWA_EventType.unsafe("open");

/* TODO test */
[@bs.send] external close: t => unit = "close";


/* TODO test */
[@bs.send] external send: (t, [@bs.unwrap] [
	| `String(string)
	| `Blob(FileReader.Blob.t)
	| `ArrayBuffer(Js.Typed_array.ArrayBuffer.t)
	| `Int8Array(Js.Typed_array.Int8Array.t)
	| `Uint8Array(Js.Typed_array.Uint8Array.t)
	| `Uint8ClampedArray(Js.Typed_array.Uint8ClampedArray.t)
	| `Int16Array(Js.Typed_array.Int16Array.t)
	| `Uint16Array(Js.Typed_array.Uint16Array.t)
	| `Int32Array(Js.Typed_array.Int32Array.t)
	| `Uint32Array(Js.Typed_array.Uint32Array.t)
	| `Float32Array(Js.Typed_array.Float32Array.t)
	| `Float64Array(Js.Typed_array.Float64Array.t)
	| `DataView(Js.Typed_array.DataView.t)
]) => unit = "close";



     