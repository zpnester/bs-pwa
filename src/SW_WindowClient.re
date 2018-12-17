type t;

[@bs.send] external focus_: t => Js.Promise.t(Js.Nullable.t(t)) = "focus";

let focus = self =>
  focus_(self)
  |> Js.Promise.then_(maybe_window =>
       Js.Promise.resolve(maybe_window->Js.Nullable.toOption)
     );

[@bs.send]
external navigate_: (t, string) => Js.Promise.t(Js.Nullable.t(t)) =
  "navigate";
let navigate = (self, url) =>
  navigate_(self, url)
  |> Js.Promise.then_(maybe_window =>
       Js.Promise.resolve(maybe_window->Js.Nullable.toOption)
     );