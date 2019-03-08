module Make = (M: {type t;}) => {
  external asDomElement: M.t => Dom.element = "%identity";
};
