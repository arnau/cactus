open Jest;
open Expect;

describe("Directed.Int", () => {
  module Graph = Directed.Make(Vertex.Int, Edge.Labelled);
  module Edge = Edge.Labelled(Vertex.Int);

  describe("order", () => {
    test("order 0", () => {
      let graph = Graph.empty();
      expect(Graph.order(graph)) |> toEqual(0);
    });

    test("order 1", () => {
      let graph = Graph.empty()->Graph.addVertex(3);
      expect(Graph.order(graph)) |> toEqual(1);
    });
  });

  describe("size", () => {
    test("size 0", () => {
      let graph = Graph.empty();
      expect(Graph.size(graph)) |> toEqual(0);
    });

    test("size 1", () => {
      let edge = Edge.make(1, "has", 2);
      let graph = Graph.empty()->Graph.addEdge(edge);
      expect(Graph.size(graph)) |> toEqual(1);
    });
  });
});

describe("Directed.String", () => {
  module Graph = Directed.Make(Vertex.String, Edge.Unlabelled);
  module Edge = Edge.Unlabelled(Vertex.String);

  describe("order", () => {
    test("order 0", () => {
      let graph = Graph.empty();
      expect(Graph.order(graph)) |> toEqual(0);
    });

    test("order 1", () => {
      let graph = Graph.empty()->Graph.addVertex("a");
      expect(Graph.order(graph)) |> toEqual(1);
    });
  });

  describe("size", () => {
    test("size 0", () => {
      let graph = Graph.empty();
      expect(Graph.size(graph)) |> toEqual(0);
    });

    test("size 1", () => {
      let edge = Edge.make("a", "b");
      let graph = Graph.empty()->Graph.addEdge(edge);
      expect(Graph.size(graph)) |> toEqual(1);
    });
  });

  describe("vertices", () => {
    test("empty", () => {
      let graph = Graph.empty();
      expect(Graph.vertices(graph)) |> toEqual([]);
    });

    test("some", () => {
      let edge = Edge.make("a", "b");
      let graph = Graph.empty()->Graph.addEdge(edge);
      expect(Graph.vertices(graph)) |> toEqual(["a", "b"]);
    });
  });

  describe("edges", () => {
    test("empty", () => {
      let graph = Graph.empty();
      expect(Graph.edges(graph)) |> toEqual([]);
    });

    test("some", () => {
      let edge = Edge.make("a", "b");
      let graph = Graph.empty()->Graph.addEdge(edge);
      expect(Graph.edges(graph)) |> toEqual([edge]);
    });
  });
});
