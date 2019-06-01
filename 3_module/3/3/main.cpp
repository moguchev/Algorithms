﻿/*Требуется отыскать самый выгодный маршрут между городами. Из города может выходить дорога, которая возвращается в этот же город.
Требуемое время работы O((N + M)log N), где N – количество городов, M – известных дорог между ними.
N ≤ 10000, M ≤ 250000.
Длина каждой дороги ≤ 10000.*/
#include <iostream>
#include <vector>
#include <limits>
#include <queue>


class IGraph {
public:
    IGraph(size_t n) {
        graph_.resize(n);
    }

    int get_dist(int x, int y) {
        return graph_[x][y].second;
    }           // получение расстояния между городами

    void add(int x, int y, int mass) {
        graph_[x].emplace_back(std::make_pair(y, mass));
    }

    std::vector<int> next_vertex(int top) {
        std::vector<int> res;
        for (int i = 0; i < graph_[top].size(); i++)
            res.push_back(graph_[top][i].first);
        return res;
    }      // получение связанных городов

    int get_number(int x, int y) {
        return graph_[x][y].first;
    }          // получение номера вершины

    int number_way(int top) {
        return graph_[top].size();
    }              // получение колличества связанных городов

private:
    std::vector<std::vector<std::pair<int, int>>> graph_;
};

struct Comp {
    bool operator()(std::pair<int, int> a, std::pair<int, int> b) {
        return a.second > b.second;
    }
};

int dijkstra(int n, int top_1, int top_2, IGraph graph) {
    std::vector<int> min_dist;
    std::vector<bool> used;
    std::priority_queue<std::pair<int, int>,
        std::vector<std::pair<int, int>>, Comp> pq;
    min_dist.resize(n, std::numeric_limits<int>::max());
    used.resize(n, false);
    min_dist[top_1] = 0;                                                  // расстояние до нее 0
    std::pair<int, int> top_pair(top_1, 0);
    pq.push(top_pair);

    while (!pq.empty()) {
        auto top = pq.top();                                              // получили вершину
        pq.pop();                                                         // убрали ее из очереди
        std::vector<int> next_top;
        next_top = graph.next_vertex(top.first);                          // получил все вершины, исходящие из top.first
        int number_way = graph.number_way(top.first);
        for (int i = 0; i < number_way; i++) {
            int new_distation = min_dist[top.first] + graph.get_dist(top.first, i);
            if (new_distation < min_dist[graph.get_number(top.first, i)]) {
                min_dist[graph.get_number(top.first, i)] = new_distation;                 // обновляем его
                pq.push(std::make_pair(graph.get_number(top.first, i),
                    min_dist[graph.get_number(top.first, i)]));
            }
        }
    }
    return min_dist[top_2];
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    IGraph graph(n);
    for (size_t i = 0; i < m; i++) {
        int x, y, z;
        std::cin >> x >> y >> z;
        graph.add(x, y, z);
        graph.add(y, x, z);
    }
    int top_1, top_2;
    std::cin >> top_1 >> top_2;
    std::cout << dijkstra(n, top_1, top_2, graph);
    return 0;
}