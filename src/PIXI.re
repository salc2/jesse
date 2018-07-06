type containerType;
type sprite;
type graphics;
type appType = {
    view: Dom.canvas,
    stage: containerType
};
type appConf = {
    backgroundColor: int
};

module Application = {
    [@bs.new] [@bs.module "pixi.js"] external create : (int,int,appConf) => appType = "Application";
};
module Container = {
    [@bs.new] [@bs.module "pixi.js"] external create : containerType = "Container";
    [@bs.send] external addChild : (containerType, 'a) => unit = "";
};

module Graphics = {
    [@bs.new] [@bs.module "pixi.js"] external create : graphics = "Graphics";
    [@bs.send] external beginFill : (graphics, int) => unit = "";
    [@bs.send] external lineStyle : (graphics, int, int) => unit = "";
    [@bs.send] external drawRect : (graphics, int, int, int, int) => unit = "";
};

module Sprite = {
    [@bs.val][@bs.module "pixi.js"][@bs.scope ("Sprite")] external fromImage : string => sprite = "";
};

type renderConfig = {
    view: Dom.canvas,
    antialias: bool,
    transparent: bool,
    resolution: int
};

type loader;
type renderer;
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

