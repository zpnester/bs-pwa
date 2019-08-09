type t;

include PWA_AbstractWorker.Make({
  type nonrec t = t;
});

include PWA_EventTarget.Make({
  type nonrec t = t;
});

module Options = {
  type t;

  [@bs.obj]
  external make:
    (
      ~_type: [@bs.string] [ | `classic | [@bs.as "module"] `module_]=?,
      ~credentials: [@bs.string] [
                      | `omit
                      | [@bs.as "same-origin"] `sameOrigin
                      | [@bs.as "include"] `include_
                    ]
                      =?,
      ~name: string=?,
      unit
    ) =>
    t =
    "";
};

[@bs.new] external make: string => t = "Worker";
[@bs.new] external make2: (string, Options.t) => t = "Worker";

include PWA_WithPostMessage.Make2({
  type nonrec t = t;
});
// rejectionhandled
// unhandledrejection

[@bs.send] external terminate: t => unit = "terminate";