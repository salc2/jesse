// Generated by BUCKLESCRIPT VERSION 3.1.5, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var Cmd$Jesse = require("./Cmd.bs.js");
var Subs$Jesse = require("./Subs.bs.js");

var animationSub = Subs$Jesse.create("animationSub", (function (consumer) {
        var id = [0];
        var keepAnimation = function (time) {
          Curry._1(consumer, time);
          id[0] = window.requestAnimationFrame(keepAnimation);
          return /* () */0;
        };
        id[0] = window.requestAnimationFrame(keepAnimation);
        return (function () {
            window.cancelAnimationFrame(id[0]);
            return /* () */0;
          });
      }));

var cancel = Subs$Jesse.run(animationSub, (function (prim) {
        console.log(prim);
        return /* () */0;
      }));

window.setTimeout((function () {
        console.log("Hola");
        return Curry._1(cancel, /* () */0);
      }), 5000);

console.log("Hello, BuckleScript and Reason!");

function runGame(update, render, subscriptions, initState) {
  var currentSubscribedTo = [/* [] */0];
  var currentModel = [initState[0]];
  var runEffect = function (cmd) {
    return window.setTimeout((function () {
                  return Cmd$Jesse.run(cmd, (function (__x) {
                                var $$event = __x;
                                var runEffect$1 = runEffect;
                                var match = Curry._2(update, $$event, currentModel[0]);
                                Curry._1(runEffect$1, match[1]);
                                Curry._1(subscriptions, currentModel[0]);
                                currentSubscribedTo[0] = /* [] */0;
                                return Curry._1(render, match[0]);
                              }));
                }), 0);
  };
  return /* () */0;
}

exports.animationSub = animationSub;
exports.cancel = cancel;
exports.runGame = runGame;
/* animationSub Not a pure module */
