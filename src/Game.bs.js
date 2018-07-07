// Generated by BUCKLESCRIPT VERSION 3.1.5, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var Subs$Jesse = require("./Subs.bs.js");
var FPSMeter$Jesse = require("./FPSMeter.bs.js");
var GameRunner$Jesse = require("./GameRunner.bs.js");

var clockFrames = Subs$Jesse.create("clock", (function (consumer) {
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

var initState = /* tuple */[
  0,
  /* Empty */0
];

function update(e, m) {
  return /* tuple */[
          m + e,
          /* Empty */0
        ];
}

function subscriptions() {
  return clockFrames;
}

var fps = Curry._1(FPSMeter$Jesse.getInstance, /* () */0);

function render() {
  fps.tick();
  return /* () */0;
}

GameRunner$Jesse.run(update, render, subscriptions, initState);

exports.update = update;
exports.render = render;
exports.subscriptions = subscriptions;
exports.initState = initState;
/* clockFrames Not a pure module */
