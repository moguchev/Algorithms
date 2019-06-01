#include "CArcGraph.hpp"


CArcGraph::CArcGraph(size_t n) : edges_(n) {}

CArcGraph::CArcGraph(const IGraph& graph) :
    verticesNumber_(graph.VerticesCount())
{
    for (size_t i = 0; i < verticesNumber_; i++) {
        auto vertices = graph.GetNextVertices(i);
        for (int j : vertices)
            AddEdge(i, j);
    }
}

// Добавление ребра от from к to.
void CArcGraph::AddEdge(int from, int to) {
    for (const auto& e : edges_)
        if (e.first == from && e.second == to)
            return;
    edges_.push_back(std::make_pair(from, to));
}

int CArcGraph::VerticesCount() const {
    return verticesNumber_;
}

std::vector<int> CArcGraph::GetNextVertices(int vertex) const {
    std::vector<int> vertices;
    for (const auto& e : edges_)
        if (e.first == vertex)
            vertices.push_back(e.second);
    return vertices;
}

std::vector<int> CArcGraph::GetPrevVertices(int vertex) const {
    std::vector<int> vertices;
    for (const auto& e : edges_)
        if (e.second == vertex)
            vertices.push_back(e.first);
    return vertices;
}