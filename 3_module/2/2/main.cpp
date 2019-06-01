/*
Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей между какими-то вершинами.
Найдите количество различных кратчайших путей между заданными вершинами. Требуемая сложность O(V+E).
Формат ввода
v: кол-во вершин (макс. 50000),
n: кол-во ребер(макс. 200000),
n пар реберных вершин,
пара вершин (u, w) для запроса.

Формат вывода
Количество кратчайших путей от v к w.
*/

#include <unordered_set>
#include <vector>
#include <queue>
#include <list>
#include <iostream>

struct Vertex {
    int depth = 0;
    int paths = 0;
};


class Graph {
public:
    explicit Graph(size_t size);

    void AddEdge(int from, int to);

    size_t VerticesCount() const;

    std::vector<int> GetNextVertices(int vertex) const;

    int CountMinPaths(int from, int to);
private:
    size_t _size;
    std::vector<std::list<int>> _fromTo;
};

Graph::Graph(size_t size) :_size(size) ,
    _fromTo(size)
{}

void Graph::AddEdge(int from, int to) {
    if (from < VerticesCount() && to < VerticesCount()) {
        for (auto i : _fromTo[from])
            if (i == to)
                return;

        _fromTo[to].push_back(from);
        _fromTo[from].push_back(to);
    }
}

size_t Graph::VerticesCount() const {
    return _size;
}

std::vector<int> Graph::GetNextVertices(int vertex) const {
    std::vector<int> vertices;
    if (vertex < VerticesCount())
        for (int i : _fromTo[vertex])
            vertices.push_back(i);

    return vertices;
}

int Graph::CountMinPaths(int from, int to)
{
    if (from < VerticesCount() && to < VerticesCount()) {
        std::vector<Vertex> info(VerticesCount());

        std::queue<int> q;
        q.push(from);
        info[from].paths = 1;

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            std::vector<int> nextVertices = GetNextVertices(v);

            for (int i : nextVertices) {
                if (info[i].paths == 0) {
                    q.push(i);
                    info[i].depth = info[v].depth + 1;
                    info[i].paths = info[v].paths;
                }
                else if (info[i].depth == info[v].depth + 1) {
                    info[i].paths += info[v].paths;
                }
            }
        }
        return info[to].paths;
    }
    return 0;
}

void testGraph(Graph *graph) {
    std::cout << "Vertices count: " << graph->VerticesCount() << std::endl;

    for (int j = 0; j < graph->VerticesCount(); ++j) {
        std::cout << "from " << j << " to: ";
        for (auto i : graph->GetNextVertices(j))
            std::cout << i << ", ";

        std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
}

int main() {
    size_t v = 0, n = 0;
    std::cin >> v;
    auto graph = new Graph(v);

    std::cin >> n;
    int from = 0, to = 0;
    for (int i = n; i > 0; --i) {
        std::cin >> from >> to;
        graph->AddEdge(from, to);
    }

    testGraph(graph);

    std::cin >> from >> to;
    std::cout << graph->CountMinPaths(from, to);
    
    delete graph;
    return 0;
}