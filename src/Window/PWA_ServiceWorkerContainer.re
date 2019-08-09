type t;

[@bs.get] [@bs.return nullable]
external controller: t => option(PWA_ServiceWorker.t) = "controller";

/* scope omitted */

// MDN: A Promise that resolves to a ServiceWorkerRegistration object, or undefined.
[@bs.send]
external getRegistration:
  t => Js.Promise.t(option(PWA_ServiceWorkerRegistration.t)) =
  "getRegistration";

[@bs.send]
external register:
  (t, string) => Js.Promise.t(PWA_ServiceWorkerRegistration.t) =
  "register";