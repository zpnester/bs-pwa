type t;

[@bs.obj]
external make:
  (
    ~actions: array(PWA_Notification_Action.t)=?,
    ~badge: string=?,
    ~body: string=?,
    ~dir: string=?,
    ~icon: string=?,
    ~image: string=?,
    ~lang: string=?,
    ~renotify: bool=?,
    ~requireInteraction: bool=?,
    ~tag: string=?,
    ~vibrate: Js.Json.t=?,
    ~data: Js.Json.t=?,
    unit
  ) =>
  t =
  "";