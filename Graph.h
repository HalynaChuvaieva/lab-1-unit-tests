#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <limits>
#include <unordered_map>
using namespace std;

template <class T>
class Graph
{
private:
    void dfsBuild(T u, std::map<T, bool> &visited, std::vector<std::pair<T, T>> &edges);
    template <typename T>
    void Graph<T>::dfsBuild(T u, std::map<T, bool> &visited, std::vector<std::pair<T, T>> &edges)
    {
        visited[u] = true;

        for (const T &v : adj[u])
        {
            if (!visited[v])
            {
                edges.push_back({u, v});
                dfsBuild(v, visited, edges);
            }
        }
    }

    template <typename T>
    std::vector<std::pair<T, T>> Graph<T>::buildSpanningTree(T startVertex)
    {
        std::map<T, bool> visited;
        std::vector<std::pair<T, T>> spanningEdges;

        for (const auto &pair : adj)
        {
            visited[pair.first] = false;
        }

        if (adj.count(startVertex))
        {
            dfsBuild(startVertex, visited, spanningEdges);
        }

        return spanningEdges;
    }

protected:
    unordered_map<T, vector<T>> adj;
    unordered_map<T, bool> visited;
    vector<pair<T, T>> spanningTree;

    void dfs(T v)
    {
        visited[v] = true;
        for (T u : adj[v])
        {
            if (!visited[u])
            {
                spanningTree.push_back({v, u});
                dfs(u);
            }
        }
    }

public:
    Graph() {}
    std::map<T, std::vector<T>> adj;
    std::vector<std::pair<T, T>> buildSpanningTree(T startVertex);
    virtual void addEdge(T u, T v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void buildSpanningTree(T start)
    {
        spanningTree.clear();
        for (auto &p : visited)
            p.second = false;

        for (auto &p : adj)
            visited[p.first] = false;

        dfs(start);

        cout << "Spanning tree consists of edges:\n";
        for (auto &e : spanningTree)
        {
            cout << e.first << " - " << e.second << endl;
        }
    }

    void bfs(T start)
    {
        for (auto &p : adj)
            visited[p.first] = false;

        queue<T> q;
        visited[start] = true;
        q.push(start);

        cout << "BFS traversal starting from " << start << ": ";

        while (!q.empty())
        {
            T v = q.front();
            q.pop();

            cout << v << " ";

            for (T u : adj[v])
            {
                if (!visited[u])
                {
                    visited[u] = true;
                    q.push(u);
                }
            }
        }
        cout << endl;
    }
};
