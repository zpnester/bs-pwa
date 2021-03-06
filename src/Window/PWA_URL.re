type t;

[@bs.new] external make: string => t = "URL";

[@bs.new] external make2: (string, ~base: string) => t = "URL";

[@bs.get] external hash: t => string = "hash";
[@bs.set] external setHash: (t, string) => unit = "hash";

[@bs.get] external host: t => string = "host";
[@bs.set] external setHost: (t, string) => unit = "host";

[@bs.get] external hostname: t => string = "hostname";
[@bs.set] external setHostname: (t, string) => unit = "hostname";

[@bs.get] external href: t => string = "href";
[@bs.set] external setHref: (t, string) => unit = "href";

[@bs.get] external origin: t => string = "origin";

[@bs.get] external password: t => string = "password";
[@bs.set] external setPassword: (t, string) => unit = "password";

[@bs.get] external pathname: t => string = "pathname";
[@bs.set] external setPathname: (t, string) => unit = "pathname";

[@bs.get] external port: t => string = "port";
[@bs.set] external setPort: (t, string) => unit = "port";

[@bs.get] external protocol: t => string = "protocol";
[@bs.set] external setProtocol: (t, string) => unit = "protocol";

[@bs.get] external search: t => string = "search";
[@bs.set] external setSearch: (t, string) => unit = "search";

[@bs.get] external username: t => string = "username";
[@bs.set] external setUsername: (t, string) => unit = "username";

[@bs.get] external toJSON: t => string = "toJSON";

[@bs.get] external toString: t => string = "toString";

/* searchParams */

[@bs.val] [@bs.scope "URL"]
external createObjectURL:
  (
  [@bs.unwrap]
  [
    | `File(FileReader.File.t)
    | `Blob(FileReader.Blob.t)
    | `MediaSource(PWA_MediaSource.t)
  ]
  ) =>
  string =
  "createObjectURL";

[@bs.val] [@bs.scope "URL"]
external revokeObjectURL: string => unit = "revokeObjectURL";