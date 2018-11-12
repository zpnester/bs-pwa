include (module type of SW_Event);

let message: t => option(string);
let filename: t => option(string);
let lineno: t => option(int);
let colno: t => option(int);
let error: t => option(SW_Types.any);