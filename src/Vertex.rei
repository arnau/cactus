module type S = {
  type t;
  let compare: (t, t) => int;
  let id: t => string;
};

module String: {
  type t = string;

  let compare: (t, t) => int;
  let id: t => string;
};

module Int: {
  type t = int;

  let compare: (t, t) => int;
  let id: t => string;
};
