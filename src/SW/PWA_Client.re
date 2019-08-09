module Make = (M: {type t;}) => {
  [@bs.get] external id: M.t => string = "id";
  [@bs.get] external type_: M.t => PWA_ClientType.t = "type";
  [@bs.get] external url: M.t => string = "url";

  include PWA_WithPostMessage.Make(M);
};

type t;

include Make({
  type nonrec t = t;
});