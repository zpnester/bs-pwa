open PWA.Window;
open PWA.Worker;
open FileReader_Helpers;
open Expect;

Js.log("worker example html");

let decoder = PWA.TextDecoder.makeWithUtfLabel("utf8");
expectBool(decoder->PWA.TextDecoder.fatal);
expectBool(decoder->PWA.TextDecoder.ignoreBOM);
expectString(decoder->PWA.TextDecoder.encoding);

let opts = PWA.Worker.Options.make(~name="worker1", ());
let w = PWA.Worker.makeWithOptions("worker-src.js", opts);
w->addEventListener(
  message,
  e => {
    open PWA_MessageEvent;
    Js.log2("window got message", e);
    Js.log2("msg", e->data);

    switch (e->data->asArrayBuffer) {
    | None => Js.log("not a buffer")
    | Some(ab) =>
      let s = decoder->PWA.TextDecoder.decodeArrayBuffer(ab);
      Js.log("decoded " ++ s);
    };
  },
);
w->postMessage("hello");