module List = {
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

  /** Generates the list of neighbour pairs in a given list. E.g.

    {[
      # pairs([1, 2, 3, 4])
      - : list((int, int)) = [(3, 4), (2, 3), (1, 2)]
    ]}
  */
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

  /** Takes the minimum value from the given list or [None] if the list is
    * empty.
    */
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

  /** Takes the maximum value from the given list or [None] if the list is
    * empty.
    */
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
};

module Option = {
  /** Unwraps the optional value. Raises an exception when the optional is
      [None].

      {[
        # Mask.Option.unwrap(Some(1));
        - : int = 1
      ]}
    */
  let unwrap = Belt.Option.getExn;

  let withDefault = Belt.Option.getWithDefault;

  let map = Belt.Option.map;
};

module Result = {
  type t('a, 'e) =
    | Ok('a)
    | Err('e);

  let unwrap =
    fun
    | Ok(x) => x
    | Err(_) => [%assert "unwrap"];

  let withDefault = (result, default) =>
    switch (result) {
    | Ok(x) => x
    | Err(_) => default
    };

  let map = (result, f) =>
    switch (result) {
    | Ok(x) => Ok(f(x))
    | Err(e) => Err(e)
    };
};
