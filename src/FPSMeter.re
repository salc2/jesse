type fpsmeter;

let fpsMeter: fpsmeter = [%bs.raw {| new FPSMeter() |}];
[@bs.send] external tick : (fpsmeter) => unit = "tick";
