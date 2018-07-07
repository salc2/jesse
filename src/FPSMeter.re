type fpsmeter;

let getInstance: unit => fpsmeter = [%bs.raw {| () => new FPSMeter() |}];
[@bs.send] external tick : (fpsmeter) => unit = "tick";
