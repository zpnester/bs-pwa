type t;

[@bs.get] [@bs.return nullable]
external serviceWorker: t => option(PWA_ServiceWorkerContainer.t) =
  "serviceWorker";

[@bs.get] [@bs.return nullable]
external mediaDevices: t => option(PWA_MediaDevices.t) = "mediaDevices";
