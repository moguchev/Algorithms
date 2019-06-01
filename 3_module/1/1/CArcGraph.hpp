#pragma once
#include <vector>
#include <tuple>
#include "IGraph.hpp"

class CArcGraph : public IGraph {
public:
    CArcGraph(size_t n);

    CArcGraph(const IGraph& graph);

    virtual ~CArcGraph() = default;

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) override;

    virtual int VerticesCount() const override;
    
    virtual std::vector<int> GetNextVertices(int vertex) const override;

    virtual std::vector<int> GetPrevVertices(int vertex) const override;
private:
    size_t verticesNumber_;
    std::vector<std::pair<int, int>> edges_;
};
