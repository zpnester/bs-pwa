

// separate module - hack to avoid name clashes
let window: Dom.window = [%raw {| (window) |}];
let selfWindow: Dom.window = [%raw {| (self) |}];
