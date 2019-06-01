#pragma once
#include <vector>
#include <cassert>
#include <queue>
#include <stack>
#include <list>
#include "IGraph.hpp"


class CListGraph : public IGraph {
public:
    CListGraph(size_t n);

    CListGraph(const IGraph& graph);

    virtual ~CListGraph() = default;

    void AddEdge(int from, int to) override;

    virtual int VerticesCount() const override;

    virtual std::vector<int> GetNextVertices(int vertex) const override;
    
    virtual std::vector<int> GetPrevVertices(int vertex) const override;
private:
    std::vector<std::vector<int>> adjacency_lists;
};
