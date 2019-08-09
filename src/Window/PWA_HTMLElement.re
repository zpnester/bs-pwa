module Make = (M: {type t;}) => {
  include PWA_EventTarget.Make(M);

  [@bs.send] external click: M.t => unit = "click";
  [@bs.send] external blur: M.t => unit = "blur";

  [@bs.send]
  external focus1:
    (M.t, Js.Nullable.t({.. "preventScroll": option(bool)})) => unit =
    "focus";

  [@bs.send] external focus: M.t => unit = "focus";
  /* let clickEvent: PWA_EventType.t(M.t, Dom.mouseEvent) = PWA_EventType.unsafe("click"); */
  /* forceSpellCheck */
};