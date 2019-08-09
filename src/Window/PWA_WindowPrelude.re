[@bs.val] external windowUnsafe: PWA_Window.t = "window";
[@bs.val] external windowOptionUnsafe: option(PWA_Window.t) = "window";

let window = () => windowUnsafe;
let windowOption = () => windowOptionUnsafe;