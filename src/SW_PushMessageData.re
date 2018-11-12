open SW_Types;

type t;

[@bs.send] external arrayBuffer: t => arraybuffer = "arrayBuffer";
[@bs.send] external blob: t => blob = "blob";
[@bs.send] external json: t => any = "json";
[@bs.send] external text: t => string = "text";