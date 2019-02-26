include (module type of PWA_Client);

let focus: t => Js.Promise.t(option(t));

let navigate: (t, string) => Js.Promise.t(option(t));

let asWindowClient: PWA_Client.t => option(t);

let asClient: t => PWA_Client.t;