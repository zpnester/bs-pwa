type t;

let controller: t => option(PWA_ServiceWorker.t);

let getRegistration:
  t => Js.Promise.t(option(PWA_ServiceWorkerRegistration.t));

let register: (t, string) => Js.Promise.t(PWA_ServiceWorkerRegistration.t);
