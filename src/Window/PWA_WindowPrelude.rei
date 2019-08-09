[@bs.val] external windowUnsafe: PWA_Window.t = "window";
[@bs.val] external windowOptionUnsafe: option(PWA_Window.t) = "window";

let window: unit => PWA_Window.t;
let windowOption: unit => option(PWA_Window.t);