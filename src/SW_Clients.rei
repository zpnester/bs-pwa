type t;

let get: (t, string) => Js.Promise.t(option(SW_Client.t));


/* type: SW_ClientType.t plus additional value 'all' */
let matchAll:
  (t, ~includeUncontrolled: bool=?, ~type_: string=?, unit) =>
  Js.Promise.t(array(SW_Client.t));

let openWindow: (t, string) => Js.Promise.t(option(SW_WindowClient.t));

let claim: t => Js.Promise.t(unit);