type containerType;
type sprite;
type graphics;
type renderer;

[@bs.deriving abstract]
type appType = {
    stage: containerType
};

[@bs.deriving abstract]
type appConf = {
    width: int,
    height: int
};

module Application = {
    [@bs.new] [@bs.module "pixi.js"] external create : appConf => appType = "Application";
    let getView: appType => Dom.canvas = [%bs.raw {| (app) => app.view |}];
};
module Container = {
    [@bs.new] [@bs.module "pixi.js"] external create : containerType = "Container";
    [@bs.send] external addChild : (containerType, 'a) => unit = "";
};

module Graphics = {
    [@bs.new] [@bs.module "pixi.js"] external create : graphics = "Graphics";
    [@bs.send] external beginFill : (graphics, int) => unit = "";
    [@bs.send] external lineStyle : (graphics, int, int) => unit = "";
    [@bs.send] external drawRect : (graphics, float, float, float, float) => unit = "";
};

module Sprite = {
    [@bs.val][@bs.module "pixi.js"][@bs.scope ("Sprite")] external fromImage : string => sprite = "";
};

module Utils = {
    [@bs.val][@bs.module "pixi.js"][@bs.scope ("utils")] external sayHello : string => unit = "";
};

[@bs.deriving abstract]
type renderConfig = {
    view: Dom.canvas,
    antialias: bool,
    transparent: bool,
    resolution: int
};

type loader;

[@bs.val] [@bs.module "pixi.js"] external autoDetectRenderer : (int,int,renderConfig) => renderer = "";
[@bs.send] external render : (renderer, containerType) => unit = "";

[@bs.val] [@bs.module "pixi.js"] external loader : loader = "";
[@bs.send] external add : (loader, string) => loader = "";
[@bs.send] external load : (loader, unit => unit) => loader = "";


/*
var graphics = new PIXI.Graphics();

graphics.beginFill(0xFFFF00);

// set the line style to have a width of 5 and set the color to red
graphics.lineStyle(5, 0xFF0000);

// draw a rectangle
graphics.drawRect(0, 0, 300, 200);*/

