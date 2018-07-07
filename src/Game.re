type action = float;
type model = float;

let clockFrames: Subs.subscription(float) =
  Subs.create("clock", consumer => {
    let id = ref(0);
    let rec keepAnimation = time => {
      consumer(time);
      id := Dom.requestAnimationFrame(keepAnimation);
    };
    id := Dom.requestAnimationFrame(keepAnimation);
    () => Dom.cancelAnimationFrame(id^);
  });

let initState = (0., Cmd.Empty);
let update = (e, m) => (m +. e, Cmd.Empty);
let subscriptions = _ => clockFrames;
let fps = FPSMeter.getInstance();

let render = m => {
  FPSMeter.tick(fps);
  ()
};
GameRunner.run(update, render, subscriptions, initState);
