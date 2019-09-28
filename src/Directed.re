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

  let degree' =
    (. graph, vertex) => {
      Map.fold(
        (_, edge, acc) =>
          Edge.tail(edge) == vertex || Edge.head(edge) == vertex
            ? acc + 1 : acc,
        graph.edges,
        0,
      );
    };

  let degree = (graph: t, vertex: Vertex.t): Result.t(int, error) =>
    if (Set.mem(vertex, graph.vertices)) {
      Ok(degree'(. graph, vertex));
    } else {
      Result.Err(UnknownVertex);
    };

  let degreeSequence = (graph: t): list(int) =>
    Set.fold(
      (vertex, acc) => [degree'(. graph, vertex), ...acc],
      graph.vertices,
      [],
    )
    ->Mask.List.sort((a, b) => b - a);

  let minDegree = (graph: t): option(int) =>
    Set.elements(graph.vertices)->Mask.List.min(v => degree'(. graph, v));

  let maxDegree = (graph: t): option(int) =>
    Set.elements(graph.vertices)->Mask.List.max(v => degree'(. graph, v));

  let rec isGraphicSequence = (xs: list(int)): bool => {
    switch (List.sort(xs, (a, b) => b - a)) {
    | [] => false
    | [k, ...ks] =>
      switch (List.take(ks, k)) {
      // If there are less than k items in the sequence, it is not
      // graphic.
      | None => false
      | Some(ys) =>
        switch (List.map(ys, y => y - 1)) {
        | ys' when List.some(ys', y => y < 0) => false
        | ys' when List.every(ys', y => y == 0) => true
        | ys' =>
          let next = List.concat(ys', List.drop(ks, k)->Option.unwrap);
          isGraphicSequence([0, ...next]);
        }
      }
    };
  };

  let hasGraphicSequence = (graph: t): bool =>
    degreeSequence(graph)->isGraphicSequence;

  let isRegular = (graph: t): bool =>
    switch (degreeSequence(graph)) {
    | [] => false
    | [_] => true
    | [k, ...xs] => Mask.List.every(xs, x => x == k)
    };

  let isEulerian = (graph: t): bool =>
    switch (degreeSequence(graph)) {
    | [] => false
    | xs => Mask.List.every(xs, x => x mod 2 == 0)
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
