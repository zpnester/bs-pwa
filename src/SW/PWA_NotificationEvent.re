type t;

include PWA_ExtendableEvent.Make({ type nonrec t = t; });

[@bs.get] external notification: t => PWA_Notification.t = "notification";
[@bs.get] external action_: t => Js.Nullable.t(string) = "action";
let action = self => action_(self)->Js.Nullable.toOption;