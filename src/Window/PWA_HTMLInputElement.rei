type t;

let files: t => option(array(FileReader.File.t));
let value: t => string;

let onchange: (t, Dom.event => unit) => unit;


let asInputElement: Dom.element => option(t);
