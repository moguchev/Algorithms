#include "CSetGraph.hpp"


CSetGraph::CSetGraph(size_t verticesNumber) :
    verticesNumber_(verticesNumber),
    out_(verticesNumber_),
    in_(verticesNumber_)
{}

CSetGraph::CSetGraph(const IGraph& graph) :
    verticesNumber_(graph.VerticesCount()),
    out_(verticesNumber_),
    in_(verticesNumber_)
{
    for (size_t i = 0; i < verticesNumber_; i++) {
        auto vertices = graph.GetNextVertices(i);
        for (int j : vertices)
            AddEdge(i, j);
    }
}

// Добавление ребра от from к to.
void CSetGraph::AddEdge(int from, int to) {
    out_[from].insert(to);
    in_[to].insert(from);
}

int CSetGraph::VerticesCount() const {
    return verticesNumber_;
}

std::vector<int> CSetGraph::GetNextVertices(int vertex) const {
    std::vector<int> vertices;
    for (int i : out_[vertex])
        vertices.push_back(i);
    return vertices;
}

std::vector<int> CSetGraph::GetPrevVertices(int vertex) const {
    std::vector<int> vertices;
    for (int i : in_[vertex])
        vertices.push_back(i);
    return vertices;
}