type t =
  | Edge
  | Label
  | Vertex;

let toChar = (tag: t): Char.t =>
  switch (tag) {
  | Edge => '\000'
  | Label => '\001'
  | Vertex => '\002'
  };

let toString = (tag: t): string => String.make(1, toChar(tag));

let tagString = (input: string, tag: t): string => toString(tag) ++ input;
