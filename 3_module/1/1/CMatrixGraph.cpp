#include "CMatrixGraph.hpp"


CMatrixGraph::CMatrixGraph(size_t n) :
    verticesNumber_(n),
    edges_(verticesNumber_)
{
    for (auto& i : edges_)
        i.assign(verticesNumber_, false);
}

CMatrixGraph::CMatrixGraph(const IGraph& graph) :
    verticesNumber_(graph.VerticesCount()),
    edges_(verticesNumber_)
{
    for (auto& i : edges_)
        i.assign(verticesNumber_, false);

    for (size_t i = 0; i < verticesNumber_; i++) {
        auto vertices = graph.GetNextVertices(i);
        for (int j : vertices)
            AddEdge(i, j);
    }
}

// Добавление ребра от from к to.
void CMatrixGraph::AddEdge(int from, int to) {
    assert(0 <= from && static_cast<size_t>(from) < edges_.size());
    assert(0 <= to && static_cast<size_t>(to) < edges_.size());
    edges_[from][to] = true;
};

int CMatrixGraph::VerticesCount() const {
    return verticesNumber_;
};

std::vector<int> CMatrixGraph::GetNextVertices(int vertex) const {
    assert(0 <= vertex && static_cast<size_t>(vertex) < edges_.size());
    std::vector<int> vertices;
    for (size_t i = 0; i < verticesNumber_; i++)
        if (edges_[vertex][i])
            vertices.push_back(i);
    return vertices;
}

std::vector<int> CMatrixGraph::GetPrevVertices(int vertex) const {
    assert(0 <= vertex && static_cast<size_t>(vertex) < edges_.size());
    std::vector<int> vertices;
    for (size_t i = 0; i < verticesNumber_; i++)
        if (edges_[i][vertex])
            vertices.push_back(i);
    return vertices;
};