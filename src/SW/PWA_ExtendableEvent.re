module Make = (M: {type t;}) => {
  include PWA_Event.Make(M);

  [@bs.send]
  external waitUntil: (M.t, Js.Promise.t('a)) => unit = "waitUntil";
};
