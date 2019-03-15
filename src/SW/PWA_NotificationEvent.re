type t;

include PWA_ExtendableEvent.Make({ type nonrec t = t; });

[@bs.get] external notification: t => PWA_Notification.t = "notification";
[@bs.get] [@bs.return nullable] external action: t => option(string) = "action";