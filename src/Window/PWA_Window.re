type t = Dom.window;

include PWA_EventTarget.Make({
  type nonrec t = t;
});

let window = PWA_Window__.window;
let self = PWA_Window__.selfWindow;

[@bs.get] external navigator: t => PWA_Navigator.t = "navigator";
[@bs.get] external document: t => PWA_Document.t = "document";

[@bs.send] external alert: (t, string) => unit = "alert";
[@bs.send] external alertAny: (t, 'a) => unit = "alert";
