type t;


let focus: t => Js.Promise.t(option(t));


let navigate: (t, string) => Js.Promise.t(option(t)) ;