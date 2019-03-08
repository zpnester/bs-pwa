module Make = (M: {type t;}) => {

  include PWA_EventTarget.Make(M);

  [@bs.send] external click: M.t => unit = "click";
  [@bs.send] external blur: M.t => unit = "blur";

  [@bs.send]
  external focus_:
    (M.t, Js.Nullable.t({. "preventScroll": Js.Nullable.t(bool)})) => unit =
    "focus";

  let focus = (self, ~preventScroll: option(bool)=?, ()) => {
    let opts =
      if (preventScroll->Belt.Option.isNone) {
        Js.Nullable.undefined;
      } else {
        Js.Nullable.return({
          "preventScroll": preventScroll->Js.Nullable.fromOption,
        });
      };
    focus_(self, opts);
  };

  /* let clickEvent: PWA_EventType.t(M.t, Dom.mouseEvent) = PWA_EventType.unsafe("click"); */
  /* forceSpellCheck */
};