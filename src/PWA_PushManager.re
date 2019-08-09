type t;

module ApplicationServerKey = {
  type t;

  external string: string => t = "%identity";
  external arrayBuffer: Js.Typed_array.ArrayBuffer.t => t = "%identity";
};

module SubscribeOptions = {
  type t;

  [@bs.obj]
  external make:
    (
      ~userVisibleOnly: bool=?,
      ~applicationServerKey: ApplicationServerKey.t=?,
      unit
    ) =>
    t =
    "";
};

[@bs.send]
external subscribe1:
  (t, SubscribeOptions.t) => Js.Promise.t(PWA_PushSubscription.t) =
  "subscribe";

[@bs.send]
external subscribe: t => Js.Promise.t(PWA_PushSubscription.t) = "subscribe";

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

// MDN: A Promise that resolves to a PushSubscription object or null.

[@bs.send]
external getSubscription_:
  t => Js.Promise.t(Js.Nullable.t(PWA_PushSubscription.t)) =
  "getSubscription";

let getSubscription = self =>
  getSubscription_(self)
  |> Js.Promise.then_(maybeSub =>
       Js.Promise.resolve(maybeSub->Js.Nullable.toOption)
     );