open PWA;
open WorkerPrelude;
open DedicatedWorkerGlobalScope;

self_->addEventListener(message, e =>
  PWA_MessageEvent.(self_->postMessage(e->data))
);