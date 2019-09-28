module type S =
  (Vertex: Vertex.S) =>
   {
    type t;

    let head: t => Vertex.t;
    let tail: t => Vertex.t;

    let makeId: t => string;
  };

/**
  A labelled directed edge.

  {[
    module Edge = Edge.Labelled(Vertex.String);

    Edge.make("b", "follows", "a");
  ]}
  */
module Labelled:
  (Vertex: Vertex.S) =>
   {
    type label = string;

    type t = {
      tail: Vertex.t,
      label,
      head: Vertex.t,
    };

    /** Makes a new edge */
    let make: (Vertex.t, label, Vertex.t) => t;

    /**
      Returns the source vertex.

      {[
        module Edge = Edge.Labelled(Vertex.String);

        let edge = Edge.make("dragon", "has", "wings");

        Edge.tail(edge) == "dragon";
      ]}
      */
    let tail: t => Vertex.t;

    /**
      Returns the sink vertex.

      {[
        module Edge = Edge.Labelled(Vertex.String);

        let edge = Edge.make("dragon", "has", "wings");

        Edge.head(edge) == "wings";
      ]}
      */
    let head: t => Vertex.t;

    /**
      Returns the label.

      {[
        module Edge = Edge.Labelled(Vertex.String);

        let edge = Edge.make("dragon", "has", "wings");

        Edge.label(edge) == "has";
      ]}
      */
    let label: t => label;

    /**
      Makes a unique identifier for the given edge.

      {[
        module Edge = Edge.Labelled(Vertex.String);

        let edge = Edge.make("dragon", "has", "wings");
        let edgeId = Edge.makeId(edge);
      ]}
      */
    let makeId: t => string;
  };

/**
  An unlabelled directed edge.

  {[
    module Edge = Edge.Unlabelled(Vertex.String);

    Edge.make("a", "b");
  ]}

  */
module Unlabelled:
  (Vertex: Vertex.S) =>
   {
    type t = {
      tail: Vertex.t,
      head: Vertex.t,
    };

    let make: (Vertex.t, Vertex.t) => t;

    /**
      Returns the source vertex.

      {[
        module Edge = Edge.Unlabelled(Vertex.String);

        let edge = Edge.make("a", "b");

        Edge.tail(edge) == "a";
      ]}
      */
    let tail: t => Vertex.t;

    /**
      Returns the sink vertex.

      {[
        module Edge = Edge.Unlabelled(Vertex.String);

        let edge = Edge.make("a", "b");

        Edge.head(edge) == "b";
      ]}
      */
    let head: t => Vertex.t;

    /**
      Makes a unique identifier for the given edge.

      {[
        module Edge = Edge.Unlabelled(Vertex.String);

        let edge = Edge.make("a", "b");
        let edgeId = Edge.makeId(edge);
      ]}
      */
    let makeId: t => string;
  };
