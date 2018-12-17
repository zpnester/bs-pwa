include (module type of SW_ExtendableEvent);

let notification: t => SW_Notification.t;
let action: t => option(string);