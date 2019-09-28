module type S = {
  type t;
  let compare: (t, t) => int;
  let id: t => string;
};

module String = {
  type t = string;

  let compare = compare;
  let id = s => s;
};

module Int = {
  type t = int;

  let compare = compare;
  let id = s => string_of_int(s);
};
