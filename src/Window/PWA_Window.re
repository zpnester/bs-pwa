type t = Dom.window;

include PWA_EventTarget.Make({
  type nonrec t = t;
});

// window usually does not name clash (compiler exception?) but self does
// so keep window external
// do not include "window self" as it is not needed
// use non-external "worker self" (named self_), its usage is separate enough to not cause ssr issues

[@bs.val] external window: t = "window";

[@bs.get] external navigator: t => PWA_Navigator.t = "navigator";
[@bs.get] external document: t => PWA_Document.t = "document";

[@bs.send] external alert: (t, string) => unit = "alert";
[@bs.send] external alertAny: (t, 'a) => unit = "alert";
