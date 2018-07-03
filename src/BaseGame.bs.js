// Generated by BUCKLESCRIPT VERSION 3.1.5, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Cmd$Jesse = require("./Cmd.bs.js");
var Pervasives = require("bs-platform/lib/js/pervasives.js");
var Subs$Jesse = require("./Subs.bs.js");

function runGame(update, render, subscriptions, initState) {
  var currentSubscribedTo = [/* [] */0];
  var m = initState[0];
  var currentModel = [m];
  var onEvent = function ($$event, runEffect) {
    var match = Curry._2(update, $$event, currentModel[0]);
    Curry._2(runEffect, match[1], Curry._1(subscriptions, currentModel[0]));
    return Curry._1(render, match[0]);
  };
  var runEffect = function (cmd, subs) {
    return window.setTimeout((function () {
                  Cmd$Jesse.run(cmd, (function (__x) {
                          return onEvent(__x, runEffect);
                        }));
                  var loop = function (s) {
                    if (typeof s === "number") {
                      return /* [] */0;
                    } else if (s.tag) {
                      return Pervasives.$at(loop(s[0]), loop(s[1]));
                    } else {
                      return /* :: */[
                              /* tuple */[
                                s[0],
                                s
                              ],
                              /* [] */0
                            ];
                    }
                  };
                  var incomingSub = loop(subs);
                  var currIds = List.map((function (el) {
                          return el[0];
                        }), currentSubscribedTo[0]);
                  var match = List.partition((function (el) {
                          var id = el[0];
                          return List.exists((function (cid) {
                                        return cid === id;
                                      }), currIds);
                        }), incomingSub);
                  var currSubs = match[0];
                  var match$1 = List.partition((function (id) {
                          return List.exists((function (el) {
                                        return el[0] === id;
                                      }), currSubs);
                        }), currIds);
                  var toRemove = match$1[1];
                  console.log(toRemove);
                  List.iter((function (s) {
                          currentSubscribedTo[0] = /* :: */[
                            /* tuple */[
                              s[0],
                              Subs$Jesse.run(s[1], (function (__x) {
                                      return onEvent(__x, runEffect);
                                    }))
                            ],
                            currentSubscribedTo[0]
                          ];
                          return /* () */0;
                        }), match[1]);
                  return List.iter((function (id) {
                                var match = List.find((function (e) {
                                        return e[0] === id;
                                      }), currentSubscribedTo[0]);
                                Curry._1(match[1], /* () */0);
                                currentSubscribedTo[0] = List.filter((function (o) {
                                          return o[0] !== id;
                                        }))(currentSubscribedTo[0]);
                                return /* () */0;
                              }), toRemove);
                }), 0);
  };
  return runEffect(initState[1], Curry._1(subscriptions, m));
}

var hola = "hola";

exports.hola = hola;
exports.runGame = runGame;
/* No side effect */
