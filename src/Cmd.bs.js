// Generated by BUCKLESCRIPT VERSION 3.1.5, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");

function run(cmd, notifyTo) {
  if (typeof cmd === "number") {
    return /* () */0;
  } else if (cmd.tag) {
    return Curry._1(cmd[0], /* () */0);
  } else {
    return Curry._1(notifyTo, Curry._1(cmd[0], /* () */0));
  }
}

exports.run = run;
/* No side effect */
