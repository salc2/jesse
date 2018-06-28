type cmd('a) = Empty | Notify( unit => 'a ) | NotNotify(unit => unit);

let rec run = (cmd,notifyTo) =>
switch (cmd) {
    | Empty => ()
    | Notify(effect) => notifyTo(effect())
    | NotNotify(effect) => effect()
};  