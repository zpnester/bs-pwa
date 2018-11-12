type t;

let match:
  (
    t,
    [ | `Request(SW_Request.t) | `String(string)],
    ~ignoreSearch: bool=?,
    ~ignoreMethod: bool=?,
    ~ignoreVary: bool=?,
    ~cacheName: string=?,
    unit
  ) =>
  Js.Promise.t(option(SW_Response.t));
let has: (t, string) => Js.Promise.t(bool);
let open_: (t, string) => Js.Promise.t(SW_Cache.t);
let delete: (t, string) => Js.Promise.t(bool);
let keys: t => Js.Promise.t(array(string));