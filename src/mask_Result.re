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
