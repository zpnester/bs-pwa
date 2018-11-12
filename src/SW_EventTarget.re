/* not included: options, 'useCapture' optional param for addEventListener and removeEventListener  */

type t;
type event;

[@bs.send]
external addEventListener_: (t, string, event => unit) => unit =
  "addEventListener";

external pass: 'a => 'b = "%identity";

let addEventListener =
    (self: t, event: SW_EventType.t('e), listener: 'e => unit) => {
  addEventListener_(self, pass(event), pass(listener));
};

[@bs.send] external dispatchEvent: (t, event) => bool = "dispatchEvent";
[@bs.send]
external removeEventListener: (t, 'a => unit) => unit = "removeEventListener";