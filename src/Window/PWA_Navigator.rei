type t;

let serviceWorker: t => option(PWA_ServiceWorkerContainer.t);

let serviceWorkerExn: t => PWA_ServiceWorkerContainer.t;

let mediaDevices: t => option(PWA_MediaDevices.t);
let mediaDevicesExn: t => PWA_MediaDevices.t;