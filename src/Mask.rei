module List: {
  let fold: (Belt.List.t('a), 'b, ('b, 'a) => 'b) => 'b;
  let map: (Belt.List.t('a), 'a => 'b) => Belt.List.t('b);
  let each: (Belt.List.t('a), 'a => 'b) => unit;
  let filter: (Belt.List.t('a), 'a => bool) => Belt.List.t('a);
  let length: Belt.List.t('a) => int;
  let sort: (Belt.List.t('a), ('a, 'a) => int) => Belt.List.t('a);
  let sum: list(int) => int;
  let take: (Belt.List.t('a), int) => option(Belt.List.t('a));
  let drop: (Belt.List.t('a), int) => option(Belt.List.t('a));
  let every: (Belt.List.t('a), 'a => bool) => bool;
  let some: (Belt.List.t('a), 'a => bool) => bool;
  let concat: (Belt.List.t('a), Belt.List.t('a)) => Belt.List.t('a);

  let pairs: list('a) => list(('a, 'a));

  let min: (list('a), 'a => int) => option(int);
  let max: (list('a), 'a => int) => option(int);
};

module Option: {
  let unwrap: option('a) => 'a;
  let withDefault: (option('a), 'a) => 'a;
  let map: (option('a), 'a => 'b) => option('b);
};

module Result: {
  type t('a, 'e) =
    | Ok('a)
    | Err('e);

  let unwrap: t('a, 'e) => 'a;
  let withDefault: (t('a, 'e), 'a) => 'a;
  let map: (t('a, 'e), 'a => 'b) => t('b, 'e);
};
