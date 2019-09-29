let fold = Belt.List.reduce;

let map = Belt.List.map;

let each = Belt.List.forEach;

let filter = Belt.List.keep;

let length = Belt.List.length;

let sort = Belt.List.sort;

let sum = xs => fold(xs, 0, (acc, x) => acc + x);

let take = Belt.List.take;

let drop = Belt.List.drop;

let every = Belt.List.every;

let some = Belt.List.some;

let concat = Belt.List.concat;

let pairs = (xs: list('a)): list(('a, 'a)) => {
  let (_, res) =
    fold(xs, (None, []), (acc, z) =>
      switch (acc) {
      | (None, xs) => (Some(z), xs)
      | (Some(v), xs) => (Some(z), [(v, z), ...xs])
      }
    );

  res;
};

let min = (xs: list('a), f: 'a => int): option(int) => {
  fold(
    xs,
    None,
    (acc, value) => {
      let curr = f(value);
      switch (acc) {
      | None => Some(curr)
      | Some(prev) => curr < prev ? Some(curr) : acc
      };
    },
  );
};

let max = (xs: list('a), f: 'a => int): option(int) => {
  fold(
    xs,
    None,
    (acc, value) => {
      let curr = f(value);
      switch (acc) {
      | None => Some(curr)
      | Some(prev) => curr > prev ? Some(curr) : acc
      };
    },
  );
};

let rec isGraphic = (xs: list(int)): bool => {
  switch (sort(xs, (a, b) => b - a)) {
  | [] => false
  | [k, ...ks] =>
    switch (take(ks, k)) {
    // If there are less than k items in the sequence, it is not
    // graphic.
    | None => false
    | Some(ys) =>
      switch (map(ys, y => y - 1)) {
      | ys' when some(ys', y => y < 0) => false
      | ys' when every(ys', y => y == 0) => true
      | ys' =>
        let next = concat(ys', drop(ks, k)->Mask_Option.unwrap);
        isGraphic([0, ...next]);
      }
    }
  };
};
