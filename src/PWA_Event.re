type t;

module Make = ({ type t; }) => {
    [@bs.get] external type_: t => string = "type";
};