type t;

/* Cache.match() is basically identical to Cache.matchAll(),
   except it resolves with response[0] (i.e. the first matching response)
   instead of response (all matching response in an array). */
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

let matchAll:
  (
    t,
    [ | `Request(SW_Request.t) | `String(string)],
    ~ignoreSearch: bool=?,
    ~ignoreMethod: bool=?,
    ~ignoreVary: bool=?,
    ~cacheName: string=?,
    unit
  ) =>
  Js.Promise.t(array(SW_Response.t));

let add:
  (t, [ | `Request(SW_Request.t) | `String(string)]) => Js.Promise.t(unit);

let addAll: (t, array(string)) => Js.Promise.t(unit);

let put: (t, SW_Request.t, SW_Response.t) => Js.Promise.t(unit);

let delete:
  (
    t,
    [ | `Request(SW_Request.t) | `String(string)],
    ~ignoreSearch: bool=?,
    ~ignoreMethod: bool=?,
    ~ignoreVary: bool=?,
    ~cacheName: string=?,
    unit
  ) =>
  Js.Promise.t(bool);

let keys:
  (
    t,
    ~request: SW_Request.t=?,
    ~ignoreSearch: bool=?,
    ~ignoreMethod: bool=?,
    ~ignoreVary: bool=?,
    ~cacheName: string=?,
    unit
  ) =>
  Js.Promise.t(array(SW_Request.t));