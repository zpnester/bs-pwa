type t;

[@bs.get]
external controller_: t => Js.Nullable.t(PWA_ServiceWorker.t) = "controller";

let controller = self => controller_(self)->Js.Nullable.toOption;

/* scope omitted */
[@bs.send]
external getRegistration_:
  t => Js.Promise.t(Js.Nullable.t(PWA_ServiceWorkerRegistration.t)) =
  "getRegistration";

let getRegistration = self =>
  getRegistration_(self)
  |> Js.Promise.then_(maybeReg =>
       Js.Promise.resolve(maybeReg->Js.Nullable.toOption)
     );

/* scope omitted */
[@bs.send]
external register:
  (t, string) => Js.Promise.t(PWA_ServiceWorkerRegistration.t) =
  "register";