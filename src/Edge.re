module type S =
  (Vertex: Vertex.S) =>
   {
    type t;

    let head: t => Vertex.t;
    let tail: t => Vertex.t;

    let makeId: t => string;
  };

module Labelled = (Vertex: Vertex.S) => {
  type label = string;

  type t = {
    tail: Vertex.t,
    label,
    head: Vertex.t,
  };

  let make = (tail: Vertex.t, label: label, head: Vertex.t): t => {
    tail,
    label,
    head,
  };

  let tail = (edge: t): Vertex.t => edge.tail;
  let head = (edge: t): Vertex.t => edge.head;
  let label = (edge: t): label => edge.label;

  let makeId = (edge: t): string => {
    String.concat(
      "",
      [
        Tag.tagString(Vertex.id(edge.tail), Tag.Edge),
        Tag.tagString(edge.label, Tag.Label),
        Tag.tagString(Vertex.id(edge.head), Tag.Edge),
      ],
    );
  };
};

module Unlabelled = (Vertex: Vertex.S) => {
  type t = {
    tail: Vertex.t,
    head: Vertex.t,
  };

  let make = (tail: Vertex.t, head: Vertex.t): t => {tail, head};

  let tail = (edge: t): Vertex.t => edge.tail;
  let head = (edge: t): Vertex.t => edge.head;

  let makeId = (edge: t): string => {
    String.concat(
      "",
      [
        Tag.tagString(Vertex.id(edge.tail), Tag.Edge),
        Tag.tagString(Vertex.id(edge.head), Tag.Edge),
      ],
    );
  };
};
