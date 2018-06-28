open Dom;

let animationSub: Subs.subscription(float) =
  Subs.create("animationSub", consumer => {
    let id = ref(0);
    let rec keepAnimation = time => {
      consumer(time);
      id := requestAnimationFrame(keepAnimation);
    };
    id := requestAnimationFrame(keepAnimation);
    () => cancelAnimationFrame(id^);
  });

let cancel = Subs.run(animationSub, Js.log);
setTimeout(()=> {
  Js.log("Hola");
  cancel();
},5000);
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
      update: ('a, 'm) => ('m, Cmd.cmd('a)),
      render: 'm => unit,
      subscriptions: 'm => Subs.subscription('a),
      initState: ('m, Cmd.cmd('a)),
    ) =>{
      let currentSubscribedTo = ref([]);
      let (m,c) = initState;
      let currentModel = ref(m);
      
      let handleSubs = (subs) => {
        []
      };
     
      let rec onEvent = (event, runEffect) => {
        let (nModel, effect) = update(event, currentModel^);
        runEffect(effect);
        currentSubscribedTo := handleSubs(subscriptions(currentModel^));
        render(nModel);
      };

      let rec runEffect = cmd => {
        Dom.setTimeout( () => Cmd.run(cmd,onEvent(_,runEffect)) ,0);
      };

      

    };
