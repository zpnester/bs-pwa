module Make = (M: {type t;}) => {
  [@bs.get] external id: M.t => string = "id";
  [@bs.get] external type_: M.t => PWA_ClientType.t = "type";
  [@bs.get] external url: M.t => string = "url";

  /* transferable omitted */
  [@bs.send] external postMessage: (M.t, 'a) => unit = "postMessage";
};

type t;

include Make({
  type nonrec t = t;
});