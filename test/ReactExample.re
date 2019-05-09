open React;
open PWA;
open Belt;

module App = {
  [@react.component]
  let make = () => {
    let videoRef = useRef(Js.Nullable.undefined);

    let onPlayClick = _ => {
      open HTMLVideoElement;

      let video =
        videoRef
        ->Ref.current
        ->Js.Nullable.toOption
        ->Option.flatMap(asVideoElement)
        ->Option.getExn;
      video->play |> ignore;
    };

    let onPauseClick = _ => {
      open HTMLVideoElement;

      let video =
        videoRef
        ->Ref.current
        ->Js.Nullable.toOption
        ->Option.flatMap(asVideoElement)
        ->Option.getExn;
      video->pause;
    };

    <>
      <video
        ref={videoRef->ReactDOMRe.Ref.domRef}
        src="https://www.w3schools.com/html/mov_bbb.mp4"
      />
      <br />
      <button onClick=onPlayClick> {string("Play")} </button>
      <button onClick=onPauseClick> {string("Pause")} </button>
    </>;
  };
};

ReactDOMRe.renderToElementWithId(<App />, "app");