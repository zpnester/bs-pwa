type window;

// separate module - hack to avoid name clashes
let window: window = [%raw {| (window) |}];
let selfWindow: window = [%raw {| (self) |}];
