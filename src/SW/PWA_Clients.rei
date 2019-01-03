type t;

let get: (t, string) => Js.Promise.t(option(PWA_Client.t));


/* type defaults to 'all' */
let matchAll:
  (t, ~includeUncontrolled: bool=?, ~type_: PWA_ClientType.t=?, unit) =>
  Js.Promise.t(array(PWA_Client.t));

let openWindow: (t, string) => Js.Promise.t(option(PWA_WindowClient.t));

let claim: t => Js.Promise.t(unit);