open Dom;
type action = float;
type model = float;

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

let initState = (0., Cmd.Empty);
let update = (e, m) => (m +. e, Cmd.Empty);
let subscriptions = _ => clockFrames;

let render = m => Js.log("Hola " ++ string_of_float(m));
GameRunner.run(update, render, subscriptions, initState);
