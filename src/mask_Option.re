let isNone =
  fun
  | None => true
  | _ => false;

let isSome =
  fun
  | Some(_) => true
  | _ => false;

let unwrap =
  fun
  | Some(x) => x
  | None => [%assert "unwrap"];

let withDefault = (opt: option('a), default: 'a): 'a =>
  switch (opt) {
  | Some(x) => x
  | None => default
  };

let map = (opt: option('a), f: 'a => 'b): option('b) =>
  switch (opt) {
  | Some(x) => Some(f(x))
  | None => None
  };
