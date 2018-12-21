type t;

[@bs.get]
external serviceWorker_: t => Js.Nullable.t(SW_ServiceWorkerContainer.t) =
  "serviceWorker";

let serviceWorker = self => serviceWorker_(self)->Js.Nullable.toOption;

let serviceWorkerExn = self => serviceWorker(self)->Belt.Option.getExn;