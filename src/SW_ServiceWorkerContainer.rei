type t;

let controller: t => option(SW_ServiceWorker.t);

let getRegistration:
  t => Js.Promise.t(option(SW_ServiceWorkerRegistration.t));

let register: (t, string) => Js.Promise.t(SW_ServiceWorkerRegistration.t);