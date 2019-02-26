type t;

include (module type of PWA_DomElementLike.Make({
	type nonrec t = t;
}));

let files: t => option(array(FileReader.File.t));
let value: t => string;


let change: PWA_EventType.t(t, Dom.event);

let asInputElement: Dom.element => option(t);

let createElement: PWA_Document.t => t;