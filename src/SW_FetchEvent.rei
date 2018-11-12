include (module type of SW_ExtendableEvent);

let clientId: t => string;
let preloadResponse: t => option(Js.Promise.t(SW_Response.t));
let request: t => SW_Request.t;
let respondWith: (t, Js.Promise.t(SW_Response.t)) => unit;