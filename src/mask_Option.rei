/**
  Checks if the given optional has no value.

  {[
    Option.isNone(None);     //=> true
    Option.isNone(Some(1));  //=> false
  ]}
 */
let isNone: option('a) => bool;

/**
  Checks if the given optional has a value.

  {[
    Option.isSome(Some(1)); //=> true
    Option.isSome(None);    //=> false
  ]}
 */
let isSome: option('a) => bool;

/**
  Unwraps the optional value. When [None] it raises an exception.

  Consider using [Option.withDefault] instead for a safer experience.
 */
let unwrap: option('a) => 'a;

/**
  Unwraps the optional value. When [None] it uses the provided default value.

  {[
    Some(1)->Option.withDefault(0); //=> 1
    None->Option.withDefault(0);    //=> 0
  ]}
 */
let withDefault: (option('a), 'a) => 'a;

/**
  Applies the given function [f] to the optional value. Does nothing when
  the optional is [None].

  {[
    Option.map(Some(2), x => x * x); //=> Some(4)
    Option.map(None, x => x * x);    //=> None
  ]}
 */
let map: (option('a), 'a => 'b) => option('b);
