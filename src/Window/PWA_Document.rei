type t = Dom.document;


let querySelectorAll: (self, selectors) => array(Dom.element) ;

let querySelector: (t, string) => option(Dom.element);

let getElementById: (t, string) => option(Dom.element);

