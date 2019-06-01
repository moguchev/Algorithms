#include "CListGraph.hpp"

CListGraph::CListGraph(size_t n) : adjacency_lists(n) {}

CListGraph::CListGraph(const IGraph& graph) {
    adjacency_lists.resize(graph.VerticesCount());
    for (size_t i = 0; i < adjacency_lists.size(); i++) {
        adjacency_lists[i] = graph.GetNextVertices(i);
    }
}


void CListGraph::AddEdge(int from, int to) {
    assert(0 <= from && static_cast<size_t>(from) < adjacency_lists.size());
    assert(0 <= to && static_cast<size_t>(to) < adjacency_lists.size());
    adjacency_lists[from].push_back(to);
}

int CListGraph::VerticesCount() const {
    return static_cast<int>(adjacency_lists.size());
}

std::vector<int> CListGraph::GetNextVertices(int vertex) const {
    assert(0 <= vertex && static_cast<size_t>(vertex) < adjacency_lists.size());
    return adjacency_lists[vertex];
}

std::vector<int> CListGraph::GetPrevVertices(int vertex) const {
    assert(0 <= vertex && static_cast<size_t>(vertex) < adjacency_lists.size());
    std::vector<int> prev_vertices;

    for (size_t from = 0; from < adjacency_lists.size(); from++) {
        for (int to : adjacency_lists[from]) {
            if (to == vertex) {
                prev_vertices.push_back(from);
            }
        }
    }
    return prev_vertices;
}