type cancelable = unit => unit;
type subscriber('a) = 'a => unit;
type subscription('a) = Empty 
| NonEmpty(string, subscriber('a) => cancelable) 
| Combine(subscription('a),subscription('a));

let single = (id,x) => NonEmpty(id, sub => {
    sub(x);
    () => ();
} );

let create = (id, body) => NonEmpty(id, body);
let (|+|) = (s1,s2) => Combine(s1,s2);
let rec run = (subtion,subber) =>
switch (subtion) {
    | Empty => () => ()
    | NonEmpty(id, exec) => exec(subber)
    | Combine(s1,s2) => {
        run(s1,subber);
        run(s2,subber);
    }
};

