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

let engine = Matter.Engine.create; 

let roofP = Matter.Bodies.rectangle(0., 0., 320., 5.);
let floorP = Matter.Bodies.rectangle(0., 175., 320., 5.);
let playerP = Matter.Bodies.rectangle(160., 90., 28., 28.);

Matter.World.add(Matter.Engine.getWorld(engine), [roofP, floorP, playerP]);


let initState = ( (roof,floor,player), Cmd.Empty);
let update = (e, m) => (m, Cmd.NotNotify( () =>{  
  Matter.Engine.update(engine, 16.); 
  Matter.Engine.onUpdate( () => {
    Js.log("updated!")
  } ); 
} ));
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





let print: 'a => unit = [%bs.raw {| function(a){console.log(a.position);} |}];


let render = m => {

 
  
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
