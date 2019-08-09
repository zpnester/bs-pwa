[@bs.val] external windowUnsafe: PWA_Window.t = "window";

let windowOption: option(PWA_Window.t);
let window: unit => PWA_Window.t;