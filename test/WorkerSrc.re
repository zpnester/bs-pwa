open PWA;
open WorkerPrelude;
open DedicatedWorkerGlobalScope;
open Expect;

Js.log2("hello worker", self_->name);

expectString(self_->name);
expectString(self_->origin);
expectBool(self_->isSecureContext);

self_->addEventListener(
  message,
  e => {
    open PWA_MessageEvent;
    Js.log2("worker got message", e);
    Js.log2("msg", e->data);
    expectMessageEvent(e);

    switch (e->data->Js.Json.decodeString) {
    | None => ()
    | Some(s) => self_->postMessage(s ++ " world")
    };
  },
);

let b =
  Js.Typed_array.Int8Array.make([|65, 66, 67|])
  ->Js.Typed_array.Int8Array.buffer;

self_->postMessageWithTransferList(b, [|Transferable.arrayBuffer(b)|]);

Js.log(b);