include SW_Worker;

module State = {
  type t = string;

  let installing = "installing";
  let installed = "installed";
  let activating = "activating";
  let activated = "activated";
  let redundant = "redundant";
};

[@bs.get] external scriptURL: t => string = "scriptURL";
[@bs.get] external state: t => State.t = "state";

/* The ServiceWorker interface inherits methods from its parent, Worker,
   with the exception of Worker.terminate — this should not be accessible from service workers. */

let statechange: SW_EventType.t(SW_Event.t) =
  SW_EventType.unsafe("statechange");

/* other events? */
/* only 1 event on main page, but more on the left */
/* https://developer.mozilla.org/en-US/docs/Web/API/ServiceWorker */

/* The ServiceWorker interface inherits methods from its parent, Worker,
   with the exception of Worker.terminate — this should NOT be accessible from service workers. */