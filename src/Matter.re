type engine;
type body;
type world;

module Engine = {
    [@bs.new] [@bs.module "matter-js"][@bs.scope ("Engine")] external create: engine = "";
    let getWorld: (engine) => world = [%bs.raw {| (engine) => engine.world |}];
    [@bs.val] [@bs.module "matter-js"][@bs.scope ("Engine")] external update: (engine, float) => unit = "";
};
module World = {
    [@bs.val][@bs.module "matter-js"][@bs.scope ("World")] external add: (world, list(body)) => unit = "";
};
module Bodies = {
    [@bs.val][@bs.module "matter-js"][@bs.scope ("Bodies")] external rectangle: (float,float,float,float) => body = "";
};
