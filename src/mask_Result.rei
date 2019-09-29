type t('a, 'e) =
  | Ok('a)
  | Err('e);

let unwrap: t('a, 'e) => 'a;
let withDefault: (t('a, 'e), 'a) => 'a;
let map: (t('a, 'e), 'a => 'b) => t('b, 'e);
