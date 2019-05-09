[@bs.val] [@bs.module "./expect"]
external expectToEqual: ('a, 'a) => unit = "expectToEqual";
[@bs.val] [@bs.module "./expect"]
external expectToEqualAny: ('a, 'b) => unit = "expectToEqual";

[@bs.val] [@bs.module "./expect"] external isArray: 'a => bool = "isArray";

open Belt;

let expectString = (s: string) => {
  expectToEqual(s->Js.typeof, "string");
};

let expectArray = (arr: array('a)) => {
  expectToEqual(arr->isArray, true);
};
let expectArrayOf = (f, xs) => {
  expectArray(xs);
  xs->Array.forEach(f);
};

let expectMessageEvent = (e: PWA_MessageEvent.t) => {
  open PWA_MessageEvent;
  expectString(e->lastEventId);
  expectString(e->origin);
  // todo message source
  expectArray(e->ports);
};

let expectOptionOf = (f, x) => {
  switch (x) {
  | None => ()
  | Some(x) => f(x)
  };
};
let expectStringOption = expectOptionOf(expectString);

let expectBool = (b: bool) => {
  expectToEqual(b->Js.typeof, "boolean");
};