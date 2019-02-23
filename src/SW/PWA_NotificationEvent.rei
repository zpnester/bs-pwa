type t;

include (module type of  PWA_ExtendableEvent.Make({ type nonrec t = t; }));


let notification: t => PWA_Notification.t;
let action: t => option(string);