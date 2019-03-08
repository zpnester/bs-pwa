type t;

type subscribe_opts;

let setUserVisibleOnly: (subscribe_opts, Js.Nullable.t(bool)) => unit = [%raw
  {|
function(opts, userVisibleOnly) {
    opts.userVisibleOnly = userVisibleOnly;
}
|}
];

let setApplicationServerKeyString: (subscribe_opts, string) => unit = [%raw
  {|
function(opts, applicationServerKey) {
    opts.applicationServerKey = applicationServerKey;
}
|}
];

let setApplicationServerKeyArrayBuffer:
  (subscribe_opts, Js.Typed_array.ArrayBuffer.t) => unit = [%raw
  {|
function(opts, applicationServerKey) {
    opts.applicationServerKey = applicationServerKey;
}
|}
];

[@bs.send]
external subscribe_:
  (t, Js.Nullable.t(subscribe_opts)) => Js.Promise.t(PWA_PushSubscription.t) =
  "subscribe";

let subscribe =
    (
      self,
      ~userVisibleOnly: option(bool)=?,
      ~applicationServerKey:
         option(
           [ | `String(string) | `ArrayBuffer(Js.Typed_array.ArrayBuffer.t)],
         )=?,
      (),
    ) => {
  let opts =
    if (userVisibleOnly->Belt.Option.isNone
        && applicationServerKey->Belt.Option.isNone) {
      Js.Nullable.undefined;
    } else {
      let opts: subscribe_opts = [%raw "{}"];
      setUserVisibleOnly(opts, Js.Nullable.fromOption(userVisibleOnly));
      switch (applicationServerKey) {
      | Some(`String(str)) => setApplicationServerKeyString(opts, str)
      | Some(`ArrayBuffer(ab)) =>
        setApplicationServerKeyArrayBuffer(opts, ab)
      | None => ()
      };
      Js.Nullable.return(opts);
    };
  subscribe_(self, opts);
};

let urlB64ToUint8Array: string => Js.Typed_array.Uint8Array.t = [%raw
  {|
function(base64String) {
    const padding = '='.repeat((4 - base64String.length % 4) % 4);
    const base64 = (base64String + padding)
      .replace(/\-/g, '+')
      .replace(/_/g, '/');

    const rawData = atob(base64);
    const outputArray = new Uint8Array(rawData.length);

    for (let i = 0; i < rawData.length; ++i) {
      outputArray[i] = rawData.charCodeAt(i);
    }
    return outputArray;
}
|}
];

[@bs.send]
external getSubscription_:
  t => Js.Promise.t(Js.Nullable.t(PWA_PushSubscription.t)) =
  "getSubscription";

let getSubscription = self =>
  getSubscription_(self)
  |> Js.Promise.then_(maybeSub =>
       Js.Promise.resolve(maybeSub->Js.Nullable.toOption)
     );
