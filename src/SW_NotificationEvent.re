include SW_ExtendableEvent;

[@bs.get] external notification: t => SW_Notification.t = "notification";
[@bs.get] external action: t => string = "action";