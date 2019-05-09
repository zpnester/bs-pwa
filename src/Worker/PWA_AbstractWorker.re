module Make = (M: {type t;}) => {
  let error: PWA_EventType.t(M.t, PWA_ErrorEvent.t) =
    PWA_EventType.unsafe("error");
};