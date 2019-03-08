type t;

module Make = (_: {type t;}) => {
  [@bs.get] external type_: t => string = "type";
};
