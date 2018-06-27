open Subscription;
open Dom;

let animationSub: subscription(float) =
  create("animationSub", consumer => {
    let id = ref(0);
    let rec keepAnimation = time => {
      consumer(time);
      id := requestAnimationFrame(keepAnimation);
    };
    id := requestAnimationFrame(keepAnimation);
    () => cancelAnimationFrame(id^);
  });

Js.log("Hello, BuckleScript and Reason!");

type action =
  | PassageOfTime
  | ArrowLeftPressed
  | ArrowRightPressed
  | ArrowLeftReleased
  | ArrowRightReleased
  | ArrowUpPressed;

let runGame =
    (
      update: ('a, 'm) => 'm,
      render: 'm => unit,
      subs: subscription('a),
      model: 'm,
    ) => 1 /*   let currentSubs: list( subscription('a))) */;
