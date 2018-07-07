type action = float;
type model = ((float, float,float,float),(float, float,float,float),(float, float,float,float));

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
let roof = (0.,0.,320.,5.);
let floor = (0.,175.,320.,5.);
let player = (160.,90.,28.,28.);

let initState = ( (roof,floor,player), Cmd.Empty);
let update = (e, m) => (m, Cmd.Empty);
let subscriptions = _ => clockFrames;
let fps = FPSMeter.getInstance();
let canvas = Dom.getCanvas("myCanvas");
let conf = PIXI.renderConfig(
  ~view = canvas,
    ~antialias=false,
    ~transparent=false,
    ~resolution=2);

let stage = PIXI.Container.create;
let renderer = PIXI.autoDetectRenderer(320,180,conf);
let graph = PIXI.Graphics.create;


PIXI.Graphics.beginFill(graph,0xFFFF00);
PIXI.Container.addChild(stage,graph);


let engine = Matter.Engine.create; 
let recA = Matter.Bodies.rectangle(400., 200., 80., 80.);
Matter.World.add(Matter.Engine.getWorld(engine), [recA]);


let print: 'a => unit = [%bs.raw {| function(a){console.log(a.position);} |}];


let render = m => {
  Matter.Engine.update(engine, 16.);
  print(recA);
  let (r,f,p) = m;

  let (rx,ry,rw,rh) = r;
  PIXI.Graphics.drawRect(graph,rx, ry, rw, rh);

  let (fx,fy,fw,fh) = f;
  PIXI.Graphics.drawRect(graph,fx, fy, fw, fh);

  let (px,py,pw,ph) = p;
  PIXI.Graphics.drawRect(graph,px, py, pw, ph);

  PIXI.render(renderer,stage);
  FPSMeter.tick(fps);
};
GameRunner.run(update, render, subscriptions, initState);
