include SW_ExtendableEvent;

[@bs.get] external clientId: t => string = "clientId";

[@bs.get]
external preloadResponse_: t => Js.Nullable.t(Js.Promise.t(SW_Response.t)) =
  "preloadResponse";

let preloadResponse = (self: t) => self->preloadResponse_->Js.Nullable.toOption;

[@bs.get] external request: t => SW_Request.t = "request";

[@bs.send]
external respondWith: (t, Js.Promise.t(SW_Response.t)) => unit =
  "respondWith";