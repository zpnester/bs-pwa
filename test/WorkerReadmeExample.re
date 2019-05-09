open PWA;
open Worker;

let worker = Worker.make("doWork.js");
worker->addEventListener(message, e =>
  MessageEvent.(
    switch (e->data->Js.Json.decodeString) {
    | None => ()
    | Some(s) => Js.log("Worker said: " ++ s)
    }
  )
);
worker->postMessage("Hello World");