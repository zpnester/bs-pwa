open FileReader;

type t;

  [@bs.get] external length: t => int = "length";
  [@bs.send] [@bs.return nullable] external item: (t, int) => option(File.t) = "item";

  let toArray: t => array(File.t) =
    self => {
      let arr = [||];
      for (i in 0 to self->length - 1) {
        arr |> Js.Array.push(self->item(i) |> Js.Option.getExn) |> ignore;
      };
      arr;
    };