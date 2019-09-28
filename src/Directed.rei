/**
  A directed graph implementation.

  Using {Edge.Labelled} makes it a directed labelled graph:

  {[
    open Cactus;

    module Digraph = Directed.Make(Vertex.String, Edge.Labelled);
    module Edge = Edge.Labelled(Vertex.String);

    let g: t = Digraph.empty()
    -> Digraph.addVertex("a")
    -> Digraph.addVertex("b")
    -> Digraph.addVertex("c")
    -> Digraph.addEdge(Edge.make("dragon", "belongTo", "fantasyland"))
    -> Digraph.addEdge(Edge.make("fantasyland", "has", "magic"));
  ]}

  As opposed to a directed graph:

  {[
    open Cactus;

    module Graph = Directed.Make(Vertex.Int, Edge.Unlabelled);
    module Edge = Edge.Unlabelled(Vertex.Int);

    let g: t = Graph.empty()
    -> Graph.addEdge(Edge.make(42, 24))
    -> Graph.addEdge(Edge.make(24, 18));
  ]}

  See: https://en.wikipedia.org/wiki/Directed_graph
  */;

type error =
  | UnknownVertex
  | UnknownEdge;

module Make:
  (Vertex: Vertex.S, EdgeS: Edge.S) =>
   {
    module Edge: {
      type t = EdgeS(Vertex).t;
      let head: t => Vertex.t;
      let tail: t => Vertex.t;
      let makeId: t => string;
    };

    module Set: {type t;};
    module Map: {type t('a);};

    type vertex = Vertex.t;
    type t = {
      vertices: Set.t,
      edges: Map.t(Edge.t),
    };

    /** Creates an empty graph */
    let empty: unit => t;

    /** Returns the amount of vertices found in the graph */
    let order: t => int;

    /** Returns the amount of edges found in the graph */
    let size: t => int;

    /**
      Returns the maximum amount of edges possible.

      Note that if the edges are labelled the graph is a multigraph hence
      there is no limit in the amount of edges.

      This implementation treats this case as if edges were unlabelled.
      */
    let maxsize: t => int;

    /**
      Checks whether all possible edges are present.

      Note that if the edges are labelled the graph is a multigraph hence
      there is no limit in the amount of edges.

      This implementation treats this case as if edges were unlabelled.
     */
    let isComplete: t => bool;

    /**
      Returns the amount of edges connected to the given vertex.

      Fails with [Directed.Error.UnknownVertex] if the given vertex is not
      part of the graph.
     */
    let degree: (t, Vertex.t) => Mask.Result.t(int, error);

    /** Returns the list of vertices */
    let vertices: t => list(Vertex.t);

    /** Returns the list of edges */
    let edges: t => list(Edge.t);

    /** Adds the given vertex to the graph */
    let addVertex: (t, Vertex.t) => t;

    /** Adds the given edge and its vertices to the graph */
    let addEdge: (t, Edge.t) => t;
  };
