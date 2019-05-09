type t = Dom.event;

module Make = (M: {type t;}) => {
  [@bs.get] external type_: M.t => string = "type";
};

include Make({
  type nonrec t = t;
});