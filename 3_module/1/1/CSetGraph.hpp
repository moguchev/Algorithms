#pragma once
#include <cassert>
#include <unordered_set>
#include <vector>
#include "IGraph.hpp"

class CSetGraph : public IGraph {
public:
    CSetGraph(size_t verticesNumber);

    CSetGraph(const IGraph& graph);

    virtual ~CSetGraph() = default;

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) override;

    virtual int VerticesCount() const override;

    virtual std::vector<int> GetNextVertices(int vertex) const override;

    virtual std::vector<int> GetPrevVertices(int vertex) const override;
private:
    size_t verticesNumber_;
    std::vector<std::unordered_set<int>> out_;
    std::vector<std::unordered_set<int>> in_;
};
