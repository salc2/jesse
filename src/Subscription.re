type cancelable = unit => unit;
type subscriber('a) = 'a => unit;
type subscription('a) = {
  id: string,
  run: subscriber('a) => cancelable,
};

let create = (id: string, body: subscriber('a) => cancelable) => {
  id,
  run: (s: subscriber('a)) => body(s),
};
