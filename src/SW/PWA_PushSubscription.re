type t;


[@bs.send] external unsubscribe: t => Js.Promise.t(bool) = "unsubscribe";