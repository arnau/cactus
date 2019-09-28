open Mask;

type error =
  | UnknownVertex
  | UnknownEdge;

module Make = (Vertex: Vertex.S, EdgeS: Edge.S) => {
  module Edge = EdgeS(Vertex);
  module Set = Set.Make(Vertex);
  module Map = Map.Make(String);

  type vertex = Vertex.t;
  type t = {
    vertices: Set.t,
    edges: Map.t(Edge.t),
  };

  let empty = (): t => {
    {vertices: Set.empty, edges: Map.empty};
  };

  let order = (graph: t): int => Set.cardinal(graph.vertices);

  let size = (graph: t): int => Map.cardinal(graph.edges);

  let maxsize = (graph: t): int => {
    let order' = order(graph);
    order' * (order' - 1);
  };

  let isComplete = (graph: t): bool => maxsize(graph) == size(graph);

  let degree = (graph: t, vertex: Vertex.t): Result.t(int, error) =>
    if (Set.mem(vertex, graph.vertices)) {
      Map.fold(
        (_, edge, acc) =>
          Edge.tail(edge) == vertex || Edge.head(edge) == vertex
            ? acc + 1 : acc,
        graph.edges,
        0,
      )
      ->Ok;
    } else {
      Result.Err(UnknownVertex);
    };

  let vertices = (graph: t): list(Vertex.t) => Set.elements(graph.vertices);

  let edges = (graph: t): list(Edge.t) =>
    Map.fold((_, edge, acc) => [edge, ...acc], graph.edges, []);

  let addVertex = (graph: t, vertex: Vertex.t): t => {
    ...graph,
    vertices: Set.add(vertex, graph.vertices),
  };

  let addEdge = (graph: t, edge: Edge.t): t => {
    let vertices =
      graph.vertices
      |> Set.add(Edge.tail(edge))
      |> Set.add(Edge.head(edge));
    let edges = Map.add(Edge.makeId(edge), edge, graph.edges);
    {vertices, edges};
  };
};
