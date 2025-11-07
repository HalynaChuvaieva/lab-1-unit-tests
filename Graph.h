#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <limits>
#include <unordered_map>
#include <map>
using namespace std;

/**
 * @brief Template class implementing an undirected graph using adjacency lists.
 * 
 * @tparam T The data type used for vertices (e.g., int, string).
 * @example
 * Graph<int> g;
 * g.addEdge(1, 2);
 * g.addEdge(1, 3);
 * g.bfs(1);
 * // Output: BFS traversal starting from 1: 1 2 3
 */
template <class T>
class Graph
{
private:
    /**
     * @brief Recursive DFS helper used for spanning tree construction.
     * 
     * @param u Current vertex.
     * @param visited Map tracking visited vertices.
     * @param edges Vector to store edges of the spanning tree.
     */
    void dfsBuild(T u, std::map<T, bool> &visited, std::vector<std::pair<T, T>> &edges)
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

public:
    std::unordered_map<T, std::vector<T>> adj; ///< Adjacency list representation of the graph.
    std::unordered_map<T, bool> visited;       ///< Tracks visited vertices for traversal algorithms.
    std::vector<std::pair<T, T>> spanningTree; ///< Stores edges of the spanning tree.

    /// @brief Default constructor.
    Graph() = default;

    /**
     * @brief Adds an undirected edge between vertices u and v.
     * @param u First vertex.
     * @param v Second vertex.
     * @throws std::invalid_argument if u or v are invalid.
     */
    virtual void addEdge(T u, T v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    /**
     * @brief Builds a spanning tree starting from the specified vertex using DFS.
     * 
     * The function prints the edges of the resulting spanning tree.
     * 
     * @param start The starting vertex.
     * @example
     * Graph<int> g;
     * g.addEdge(1, 2);
     * g.addEdge(1, 3);
     * g.addEdge(2, 4);
     * g.buildSpanningTree(1);
     * // Output:
     * // Spanning tree consists of edges:
     * // 1 - 2
     * // 2 - 4
     * // 1 - 3
     */
    void buildSpanningTree(T start)
    {
        spanningTree.clear();

        // Reset visited status
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

    /**
     * @brief Internal DFS method used for spanning tree generation.
     * @param v The starting vertex.
     */
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

    /**
     * @brief Performs a Breadth-First Search (BFS) traversal starting from a given vertex.
     * 
     * @param start The starting vertex.
     * @example
     * Graph<int> g;
     * g.addEdge(1, 2);
     * g.addEdge(1, 3);
     * g.bfs(1);
     * // Output: BFS traversal starting from 1: 1 2 3
     */
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

    /**
     * @brief Constructs and returns the list of edges forming a spanning tree using DFS.
     * @param startVertex The vertex from which to start.
     * @return A vector of edges representing the spanning tree.
     */
    std::vector<std::pair<T, T>> buildSpanningTreeEdges(T startVertex)
    {
        std::map<T, bool> visited;
        std::vector<std::pair<T, T>> spanningEdges;

        for (const auto &pair : adj)
            visited[pair.first] = false;

        if (adj.count(startVertex))
            dfsBuild(startVertex, visited, spanningEdges);

        return spanningEdges;
    }
};
