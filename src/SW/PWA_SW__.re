type swGlobalScope;

// separate module - hack to avoid name clashes
let selfSw: swGlobalScope = [%raw {| (self) |}];
