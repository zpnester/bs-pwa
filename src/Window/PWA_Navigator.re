type t;

[@bs.get]
external serviceWorker_: t => Js.Nullable.t(PWA_ServiceWorkerContainer.t) =
  "serviceWorker";

let serviceWorker = self => serviceWorker_(self)->Js.Nullable.toOption;

let serviceWorkerExn = self => serviceWorker(self)->Belt.Option.getExn;


[@bs.get] [@bs.return nullable] external mediaDevices: t => option(PWA_MediaDevices.t) = "mediaDevices";
let mediaDevicesExn = self => mediaDevices(self)->Belt.Option.getExn;