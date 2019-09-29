open Jest;
open Expect;
open Mask;

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

  describe("maxsize", () =>
    test("single edge", () => {
      let edge = Edge.make("a", "b");
      let graph = Graph.empty()->Graph.addEdge(edge);
      expect(Graph.maxsize(graph)) |> toEqual(2);
    })
  );

  describe("isComplete", () => {
    test("no", () => {
      let graph = Graph.empty()->Graph.addEdge(Edge.make("a", "b"));
      expect(Graph.isComplete(graph)) |> toEqual(false);
    });

    test("yes", () => {
      let graph =
        Graph.empty()
        ->Graph.addEdge(Edge.make("a", "b"))
        ->Graph.addEdge(Edge.make("b", "a"));

      expect(Graph.isComplete(graph)) |> toEqual(true);
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

  describe("degree", () => {
    test("missing", () => {
      let graph = Graph.empty();
      expect(Graph.degree(graph, "a"))
      |> toEqual(Result.Err(Directed.UnknownVertex));
    });

    test("degree 1", () => {
      let graph =
        Graph.empty()
        ->Graph.addEdge(Edge.make("a", "b"))
        ->Graph.addEdge(Edge.make("c", "d"));
      expect(Graph.degree(graph, "a")) |> toEqual(Result.Ok(1));
    });
  });

  describe("degreeSequence", () => {
    test("none", () => {
      let graph = Graph.empty();
      expect(Graph.degreeSequence(graph)) |> toEqual([]);
    });

    test("degree 0", () => {
      let graph = Graph.empty()->Graph.addVertex("a");
      expect(Graph.degreeSequence(graph)) |> toEqual([0]);
    });

    test("degree 1", () => {
      let graph = Graph.empty()->Graph.addEdge(Edge.make("a", "b"));
      expect(Graph.degreeSequence(graph)) |> toEqual([1, 1]);
    });

    test("degree many", () => {
      let graph =
        Graph.empty()
        ->Graph.addEdge(Edge.make("a", "b"))
        ->Graph.addEdge(Edge.make("a", "c"))
        ->Graph.addEdge(Edge.make("a", "d"))
        ->Graph.addEdge(Edge.make("b", "d"))
        ->Graph.addVertex("e");

      expect(Graph.degreeSequence(graph)) |> toEqual([3, 2, 2, 1, 0]);
    });
  });

  describe("minDegree", () => {
    test("none", () => {
      let graph = Graph.empty();
      expect(Graph.minDegree(graph)) |> toEqual(None);
    });

    test("one", () => {
      let graph =
        Graph.empty()
        ->Graph.addEdge(Edge.make("a", "b"))
        ->Graph.addEdge(Edge.make("c", "d"));

      expect(Graph.minDegree(graph)) |> toEqual(Some(1));
    });
  });

  describe("maxDegree", () =>
    test("one", () => {
      let graph =
        Graph.empty()
        ->Graph.addEdge(Edge.make("a", "b"))
        ->Graph.addEdge(Edge.make("c", "d"));

      expect(Graph.maxDegree(graph)) |> toEqual(Some(1));
    })
  );
});
