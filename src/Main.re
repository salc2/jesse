
open Subscription;
let sub1 = from(233);
let cancel = sub1( (x) => Js.log("this is " ++ string_of_int(x)) );
Js.log("Hello, BuckleScript and Reason!");
