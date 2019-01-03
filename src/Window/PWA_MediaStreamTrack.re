type t;

[@bs.get] external enabled: t => bool = "enabled";
[@bs.get] external id: t => string = "id";
[@bs.get] external kind: t => string = "kind";
[@bs.get] external label: t => string = "label";
[@bs.get] external muted: t => bool = "muted";
[@bs.get] external readyState: t => string = "readyState";

[@bs.send] external stop: t => unit = "stop";