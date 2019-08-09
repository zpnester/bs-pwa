[@bs.val] external windowUnsafe: PWA_Window.t = "window";

let windowOption: option(PWA_Window.t) = [%external window];
let window = () => windowUnsafe;