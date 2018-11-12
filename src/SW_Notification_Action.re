/* type t;

   let t: (~action: string=?, ~title: string=?, ~icon: string=?, unit) => t;
   let action: t => option(string);
   let title: t => option(string);
   let icon: t => option(string); */

[@bs.deriving abstract]
type t = {
  action: option(string),
  title: option(string),
  icon: option(string),
};