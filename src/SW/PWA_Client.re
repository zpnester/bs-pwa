type t;

[@bs.get] external id: t => string = "id";
[@bs.get] external type_: t => PWA_ClientType.t = "type";
[@bs.get] external url: t => string = "url";

/* TODO transferable */
[@bs.send] external postMessage: (t, 'a) => unit = "postMessage";
