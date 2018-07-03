module Main = {
  open Dom;

let clockFrames: Subs.subscription(float) =
  Subs.create("clock", consumer => {
    let id = ref(0);
    let rec keepAnimation = time => {
      consumer(time);
      id := requestAnimationFrame(keepAnimation);
    };
    id := requestAnimationFrame(keepAnimation);
    () => cancelAnimationFrame(id^);
  });

let initM = (0., Cmd.Empty);
type msg = float;
let u = (e, m) => (m +. e, Cmd.Empty);
let sub = m => clockFrames;

let render = m => Js.log("Hola " ++ string_of_float(m));
open BaseGame;
runGame(u, render, sub, initM);
};
