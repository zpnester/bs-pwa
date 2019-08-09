type t;

include PWA_Client.Make({
  type nonrec t = t;
});

[@bs.send] external focus: t => Js.Promise.t(t) = "focus";

[@bs.send] external navigate: (t, string) => Js.Promise.t(t) = "navigate";

let asWindowClient: PWA_Client.t => option(t) = [%raw
  {|
function(client) {
  if ((typeof client.focus === "function") && (typeof client.navigate == "function")) {
    return client
  }
}
|}
];

external asClient: t => PWA_Client.t = "%identity";