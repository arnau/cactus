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

/**
  Generates the list of neighbour pairs in a given list. E.g.

  {[
    # pairs([1, 2, 3, 4])
    - : list((int, int)) = [(3, 4), (2, 3), (1, 2)]
  ]}
 */
let pairs: list('a) => list(('a, 'a));

/**
  Takes the minimum value from the given list or [None] if the list is
  empty.
 */
let min: (list('a), 'a => int) => option(int);

/**
  Takes the maximum value from the given list or [None] if the list is
  empty.
 */
let max: (list('a), 'a => int) => option(int);

/**
  A degree sequence is graphic if there is a graph that has such degree
  sequence.

  Havel-Hakimi Algorithm:

  1. Let k be the highest degree.
  2. Take the next highest k degrees and decrease them by 1.
  3. Repeat steps 1 and 2 until you exhaust the sequence.

  If the resulting sequence is all zeroes, the sequence is graphic.

  See also [Directed.degreeSequence].
 */
let isGraphic: list(int) => bool;
