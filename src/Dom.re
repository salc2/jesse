[@bs.scope "window"] [@bs.val]
external requestAnimationFrame : (float => unit) => int = "";
[@bs.scope "window"] [@bs.val]
external cancelAnimationFrame : int => unit = "";
[@bs.scope "window"] [@bs.val]
external setTimeout : (unit => unit) => int => int = "";
