type t;

open SW_Types;

[@bs.get] external id: t => string = "id";
[@bs.get] external type_: t => string = "type";
[@bs.get] external url: t => string = "url";


[@bs.send] external postMessage_: (t, 'a, Js.Nullable.t(array(transferable))) => unit = "postMessage";


let postMessage = (self: t, message: 'a, ~transfer: option(array(transferable))=?, ()) => {
    self->postMessage_(message, Js.Nullable.fromOption(transfer))
};