#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <limits>
#include <unordered_map>
#include <stdexcept>   // for std::invalid_argument
using namespace std;

/**
 * @brief A generic undirected graph implementation using adjacency lists.
 * @tparam T Type of vertex identifiers.
 * 
 * @example
 * Graph<int> g;
 * g.addEdge(1, 2);
 * g.addEdge(2, 3);
 * g.bfs(1);
 */
template <class T>
class Graph
{
protected:
    unordered_map<T, vector<T>> adj;     ///< Adjacency list representation.
    unordered_map<T, bool> visited;      ///< Map to track visited vertices.
    vector<pair<T, T>> spanningTree;     ///< Edges in the generated spanning tree.

    /**
     * @brief Depth-First Search (DFS) helper function for spanning tree construction.
     * @param v Current vertex being visited.
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

public:
    /**
     * @brief Default constructor.
     */
    Graph() {}

    /**
     * @brief Adds an undirected edge between vertices u and v.
     * @param u First vertex.
     * @param v Second vertex.
     * @throws std::invalid_argument if u == v (self-loop not allowed).
     * 
     * @example
     * Graph<int> g;
     * g.addEdge(1, 2); // valid
     * g.addEdge(1, 1); // throws invalid_argument
     */
    virtual void addEdge(T u, T v)
    {
        if (u == v)
            throw std::invalid_argument("Self-loops are not allowed.");

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    /**
     * @brief Builds and prints a DFS-based spanning tree starting from the given vertex.
     * @param start The vertex from which DFS starts.
     * @throws std::invalid_argument if start vertex does not exist in the graph.
     * 
     * @example
     * Graph<int> g;
     * g.addEdge(1, 2);
     * g.addEdge(2, 3);
     * g.buildSpanningTree(1);
     */
    void buildSpanningTree(T start)
    {
        if (!adj.count(start))
            throw std::invalid_argument("Start vertex not found in the graph.");

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

    /**
     * @brief Performs a Breadth-First Search (BFS) starting from the given vertex.
     * @param start The vertex to start BFS from.
     * @throws std::invalid_argument if start vertex does not exist in the graph.
     * 
     * @example
     * Graph<int> g;
     * g.addEdge(1, 2);
     * g.addEdge(2, 3);
     * g.bfs(1); // Output: BFS traversal starting from 1: 1 2 3
     */
    void bfs(T start)
    {
        if (!adj.count(start))
            throw std::invalid_argument("Start vertex not found in the graph.");

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
