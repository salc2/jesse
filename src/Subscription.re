type cancelable = unit => unit;
type subscription('a) = 'a => unit => cancelable;

let from = (x:'a) => (func: 'a => unit) => {
    func(x);
    () => Js.log("Cancelling");
}; 