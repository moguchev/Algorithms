#pragma once
#include "IGraph.hpp"
#include <vector>
#include <cassert>

class CMatrixGraph : public IGraph
{
public:
    CMatrixGraph(size_t n);

    CMatrixGraph(const IGraph& graph);

    virtual ~CMatrixGraph() = default;

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) override;

    virtual int VerticesCount() const override;

    virtual std::vector<int> GetNextVertices(int vertex) const override;

    virtual std::vector<int> GetPrevVertices(int vertex) const override;
private:
    size_t verticesNumber_;
    std::vector<std::vector<bool>> edges_;
};

