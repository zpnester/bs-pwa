include (module type of SW_Client);

let focus: t => Js.Promise.t(option(t));

let navigate: (t, string) => Js.Promise.t(option(t));

let asWindowClient: SW_Client.t => option(t);