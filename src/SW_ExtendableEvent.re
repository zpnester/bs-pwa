
  include SW_Event;

  [@bs.send] external waitUntil: (t, Js.Promise.t('a)) => unit = "waitUntil";
 


