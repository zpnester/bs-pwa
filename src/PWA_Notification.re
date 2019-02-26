type t;
type ctor;

module Action = PWA_Notification_Action;



let toPermission_ =
fun
| "granted" => `granted
| "denied" => `denied
| "default" => `default
| _ => failwith("unexpected permision");


[@bs.get]
external permission_: ctor => string = "permission";

let permission = ctor => permission_(ctor)->toPermission_;


[@bs.send] 
external requestPermission_: ctor => Js.Promise.t(string) =
"requestPermission";

let requestPermission = ctor =>
requestPermission_(ctor)
|> Js.Promise.then_(s => Js.Promise.resolve(s->toPermission_));



let ctor_: Js.Nullable.t(ctor) = [%raw {|
( (typeof Notification === "function") ? Notification : null)
|}];

let ctor = ctor_->Js.Nullable.toOption;


[@bs.get]
external actions_: t => Js.Nullable.t(array(PWA_Notification_Action.t)) =
  "actions";
[@bs.get] external badge_: t => Js.Nullable.t(string) = "badge";
[@bs.get] external body_: t => Js.Nullable.t(string) = "body";
[@bs.get] external data_: t => Js.Nullable.t(Js.Json.t) = "data";
[@bs.get] external dir_: t => Js.Nullable.t(string) = "dir";
[@bs.get] external tag_: t => Js.Nullable.t(string) = "tag";
[@bs.get] external icon_: t => Js.Nullable.t(string) = "icon";
[@bs.get] external image_: t => Js.Nullable.t(string) = "image";
[@bs.get] external renotify_: t => Js.Nullable.t(bool) = "renotify";
[@bs.get] external silent_: t => Js.Nullable.t(bool) = "silent";

[@bs.get] external timestamp_: t => Js.Nullable.t(float) = "timestamp";
[@bs.get] external title_: t => Js.Nullable.t(string) = "title";

[@bs.get] external vibrate_: t => Js.Nullable.t(Js.Json.t) = "vibrate";

let actions = (self: t) => self->actions_->Js.Nullable.toOption;
let badge = (self: t) => self->badge_->Js.Nullable.toOption;
let body = (self: t) => self->body_->Js.Nullable.toOption;
let data = (self: t) => self->data_->Js.Nullable.toOption;
let dir = (self: t) => self->dir_->Js.Nullable.toOption;
let tag = (self: t) => self->tag_->Js.Nullable.toOption;
let icon = (self: t) => self->icon_->Js.Nullable.toOption;
let image = (self: t) => self->image_->Js.Nullable.toOption;
let renotify = (self: t) => self->renotify_->Js.Nullable.toOption;
let silent = (self: t) => self->silent_->Js.Nullable.toOption;

let timestamp = (self: t) => self->timestamp_->Js.Nullable.toOption;
let title = (self: t) => self->title_->Js.Nullable.toOption;

let vibrate = (self: t) => self->vibrate_->Js.Nullable.toOption;

[@bs.send] external close: t => unit = "close";

[@bs.set] external onclick: (t, PWA_Event.t => unit) => unit = "onclick";

type show_notification_options = {
  .
  "actions": Js.Nullable.t(array(PWA_Notification_Action.t)),
  "badge": Js.Nullable.t(string),
  "body": Js.Nullable.t(string),
  "dir": Js.Nullable.t(string),
  "icon": Js.Nullable.t(string),
  "image": Js.Nullable.t(string),
  "lang": Js.Nullable.t(string),
  "renotify": Js.Nullable.t(bool),
  "requireInteraction": Js.Nullable.t(bool),
  "tag": Js.Nullable.t(string),
  "vibrate": Js.Nullable.t(Js.Json.t),
  "data": Js.Nullable.t(Js.Json.t),
};

let make_: (ctor, string, Js.Nullable.t(show_notification_options)) => t = [%raw {|
function(ctor, title, options) {
  return new ctor(title, options);
}
|}];


let make =
    (self: ctor,
      title: string,
      ~actions: option(array(PWA_Notification_Action.t))=?,
      ~badge: option(string)=?,
      ~body: option(string)=?,
      ~dir: option(string)=?,
      ~icon: option(string)=?,
      ~image: option(string)=?,
      ~lang: option(string)=?,
      ~renotify: option(bool)=?,
      ~requireInteraction: option(bool)=?,
      ~tag: option(string)=?,
      ~vibrate: option(Js.Json.t)=?,
      ~data: option(Js.Json.t)=?,
      (),
    ) => {
  open Belt.Option;
  let opts =
    if (isNone(actions)
        && isNone(badge)
        && isNone(body)
        && isNone(dir)
        && isNone(icon)
        && isNone(image)
        && isNone(lang)
        && isNone(renotify)
        && isNone(requireInteraction)
        && isNone(tag)
        && isNone(vibrate)
        && isNone(data)) {
      Js.Nullable.undefined;
    } else {
      Js.Nullable.return({
        "actions": Js.Nullable.fromOption(actions),
        "badge": Js.Nullable.fromOption(badge),
        "body": Js.Nullable.fromOption(body),
        "dir": Js.Nullable.fromOption(dir),
        "icon": Js.Nullable.fromOption(icon),
        "image": Js.Nullable.fromOption(image),
        "lang": Js.Nullable.fromOption(lang),
        "renotify": Js.Nullable.fromOption(renotify),
        "requireInteraction": Js.Nullable.fromOption(requireInteraction),
        "tag": Js.Nullable.fromOption(tag),
        "vibrate": Js.Nullable.fromOption(vibrate),
        "data": Js.Nullable.fromOption(data),
      });
    };
  make_(self, title, opts);
};