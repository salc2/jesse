[@bs.scope "window"] [@bs.val]
external requestAnimationFrame : (float => unit) => int = "";
[@bs.scope "window"] [@bs.val]
external cancelAnimationFrame : int => unit = "";
[@bs.scope "window"] [@bs.val]
external setTimeout : (unit => unit, int) => int = "";
type canvas;
let getCanvas: string => canvas = [%bs.raw {| (id) => document.getElementById(id) |}];

[@bs.scope ("window","document","body")] [@bs.val]
external appendChild : canvas => unit = "";
