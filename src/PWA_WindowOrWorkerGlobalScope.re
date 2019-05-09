module Make = (M: {type t;}) => {
  [@bs.get] external isSecureContext: M.t => bool = "isSecureContext";
  [@bs.get] external origin: M.t => string = "origin";
};