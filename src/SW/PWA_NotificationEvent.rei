include (module type of PWA_ExtendableEvent);

let notification: t => PWA_Notification.t;
let action: t => option(string);