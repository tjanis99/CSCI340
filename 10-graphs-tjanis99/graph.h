//***************************************************************************
//
//  Trevor Janis
//  Z1839641
//  CSCI 340-1
//
//  I certify that this is my own work and where appropriate an extension 
//  of the starter code provided for the assignment.
//
//***************************************************************************
#ifndef NIU_CSCI340_GRAPH_H
#define NIU_CSCI340_GRAPH_H

// This is the file where the student should do their work.

#include "graph.decl.h"
#include <queue>
#include <stack>
#include <iostream>

/**
 * @brief Returns the number of vertices in the graph.
 * @return size_t 
 */
size_t Graph::nvertices() const {
    return vertices.size();
}

/**
 * @brief Returns the number of edges in the graph.
 * @return size_t 
 */
size_t Graph::nedges() const {
    return edges.size();
}

/**
 * @brief Assigns vertices and edges to the graph.
 * @param vertices Vector of vertex labels.
 * @param edges Vector of graph edges.
 */
void Graph::assign(const std::vector<std::string> &vertices, const std::vector<GraphEdge> &edges) {
    this->vertices = vertices;

    // Build the label to index lookup table
    v_lut.clear();
    for (size_t i = 0; i < vertices.size(); ++i) {
        v_lut[vertices[i]] = i;
    }

    this->edges = edges;
}

/**
 * @brief Checks if an edge exists between given vertices.
 * @param origin The origin vertex index.
 * @param destination The destination vertex index.
 * @return true if the edge exists, false otherwise.
 */
bool Graph::edge_exists(size_t origin, size_t destination) const {
    for (const auto &edge : edges) {
        if (edge.origin == origin && edge.destination == destination) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Returns the weight of the edge between given vertices.
 * @param origin The origin vertex index.
 * @param destination The destination vertex index.
 * @return The weight of the edge, or INFINITY if the edge doesn't exist.
 */
double Graph::edge_weight(size_t origin, size_t destination) const {
    for (const auto &edge : edges) {
        if (edge.origin == origin && edge.destination == destination) {
            return edge.weight;
        }
    }
    return INFINITY; // If edge doesn't exist, return INFINITY
}

/**
 * @brief Returns the undirected adjacency list for a given vertex.
 * @param vertex The vertex index.
 * @return Vector of AdjListEdge representing the adjacency list.
 */
std::vector<AdjListEdge> Graph::undirected_adjacency_list(size_t vertex) const {
    std::vector<AdjListEdge> adjacencyList;

    for (const auto &edge : edges) {
        if (edge.origin == vertex) {
            adjacencyList.push_back({edge.destination, edge.weight});
        } else if (edge.destination == vertex) {
            adjacencyList.push_back({edge.origin, edge.weight});
        }
    }

    return adjacencyList;
}

/**
 * @brief Returns the in adjacency list for a given vertex.
 * @param vertex The vertex index.
 * @return Vector of AdjListEdge representing the in adjacency list.
 */
std::vector<AdjListEdge> Graph::in_adjacency_list(size_t vertex) const {
    std::vector<AdjListEdge> inAdjacencyList;

    for (const auto &edge : edges) {
        if (edge.destination == vertex) {
            inAdjacencyList.push_back({edge.origin, edge.weight});
        }
    }

    return inAdjacencyList;
}

/**
 * @brief Returns the out adjacency list for a given vertex.
 * @param vertex The vertex index.
 * @return Vector of AdjListEdge representing the out adjacency list.
 */
std::vector<AdjListEdge> Graph::out_adjacency_list(size_t vertex) const {
    std::vector<AdjListEdge> outAdjacencyList;

    for (const auto &edge : edges) {
        if (edge.origin == vertex) {
            outAdjacencyList.push_back({edge.destination, edge.weight});
        }
    }

    return outAdjacencyList;
}

/**
 * @brief Returns the weighted adjacency matrix of the graph.
 * @return Vector representing the weighted adjacency matrix.
 */
std::vector<double> Graph::weighted_adjacency_matrix() const {
  // XXX You must implement this.
  size_t numVertices = nvertices();
  std::vector<double> matrix(numVertices * numVertices, INFINITY);

  for (const auto& edge : edges) {
    matrix[edge.origin * numVertices + edge.destination] = edge.weight;
  }

  return matrix;
}

/**
 * @brief Returns the unweighted adjacency matrix of the graph.
 * @return Vector representing the unweighted adjacency matrix.
 */
std::vector<bool> Graph::unweighted_adjacency_matrix() const {
  // XXX You must implement this.
  size_t numVertices = nvertices();
  std::vector<bool> matrix(numVertices * numVertices, false);

  for (const auto& edge : edges) {
    matrix[edge.origin * numVertices + edge.destination] = true;
  }

  return matrix;
}

/**
 * @brief Returns the label of the vertex with the given index.
 * @param vertex The vertex index.
 * @return The label of the vertex.
 */
std::string Graph::v_label(size_t vertex) const {
    if (vertex < vertices.size()) {
        return vertices[vertex];
    } else {
        return ""; // Or throw an exception
    }
}

/**
 * @brief Returns the index of the vertex with the given label.
 * @param label The label of the vertex.
 * @return The index of the vertex, or -1 if not found.
 */
ssize_t Graph::v_index(const std::string &label) const {
    auto it = v_lut.find(label);
    if (it != v_lut.end()) {
        return it->second;
    } else {
        return -1; // Or throw an exception
    }
}

/**
 * @brief Performs breadth-first traversal starting from a given vertex.
 * @tparam FN Type of the function to be applied to each visited vertex.
 * @param start The starting vertex index.
 * @param visitfn The function to be applied to each visited vertex.
 * @param connected_only Flag indicating whether to traverse only connected vertices.
 */
template <typename FN>
void Graph::breadth_first(size_t start, FN visitfn, bool connected_only) {
  size_t numVertices = nvertices();
  std::vector<bool> visited(numVertices, false);
  std::queue<size_t> queue;

  visited[start] = true;
  queue.push(start);

  while (!queue.empty()) {
    size_t current = queue.front();
    queue.pop();
    visitfn(current);

    const auto& adj_list = (connected_only) ? out_adjacency_list(current) : undirected_adjacency_list(current);
    for (const auto& neighbor : adj_list) {
      if (!visited[neighbor.vertex]) {
        visited[neighbor.vertex] = true;
        queue.push(neighbor.vertex);
      }
    }
  }
}

/**
 * @brief Performs depth-first traversal starting from a given vertex.
 * @tparam FN Type of the function to be applied to each visited vertex.
 * @param start The starting vertex index.
 * @param visitfn The function to be applied to each visited vertex.
 * @param connected_only Flag indicating whether to traverse only connected vertices.
 */
template <typename FN>
void Graph::depth_first(size_t start, FN visitfn, bool connected_only) {
    size_t numVertices = nvertices();

   // Ensure StudentExtra is initialized
    if (student.visited.size() != numVertices) {
        student.visited.resize(numVertices, false);
    }

    if (!connected_only) {
        // Reset visited vector for the traversal of all vertices
        std::fill(student.visited.begin(), student.visited.end(), false);
    }

    std::stack<size_t> stack;

    for (size_t i = 0; i < numVertices; ++i) {
        size_t current = (start + i) % numVertices;  // Traverse from any unvisited vertex

        if (!student.visited[current]) {
            stack.push(current);

                current = stack.top();
                stack.pop();

                if (!student.visited[current]) {
                    visitfn(current);
                    student.visited[current] = true;

                    const auto& adj_list = (connected_only) ? out_adjacency_list(current) : undirected_adjacency_list(current);

                    for (const auto& neighbor : adj_list) {
                        if (!student.visited[neighbor.vertex]) {
                            stack.push(neighbor.vertex);
                        }
                    }
                }
            }
        }
    }

/**
 * @brief Performs topological sorting of the graph.
 * @return Vector representing the topological order of vertices.
 */
std::vector<size_t> Graph::toposort() const {
  std::vector<size_t> result; // To store the topological order
  std::vector<size_t> in_degree(nvertices(), 0); // To store in-degrees of vertices

  // Calculate in-degrees
  for (const auto &edge : edges) {
    in_degree[edge.destination]++;
  }

  // Initialize a queue for vertices with in-degree 0
  std::queue<size_t> q;
  for (size_t i = 0; i < nvertices(); ++i) {
    if (in_degree[i] == 0) {
      q.push(i);
    }
  }

  while (!q.empty()) {
    size_t current = q.front();
    q.pop();
    result.push_back(current);

    // Update in-degrees of neighbors
    for (const auto &neighbor : out_adjacency_list(current)) {
      in_degree[neighbor.vertex]--;
      if (in_degree[neighbor.vertex] == 0) {
        q.push(neighbor.vertex);
      }
    }
  }

  // Check for a cycle (some vertices may not have been visited)
  if (result.size() != nvertices()) {
    std::cerr << "Warning: Graph contains a cycle. Topological sort is incomplete." << std::endl;
  }

  return result;
}
    
/**
 * @brief Performs Dijkstra's algorithm starting from a given vertex.
 * @param start The starting vertex index.
 * @return Vector of dijkstra_row representing the result of Dijkstra's algorithm.
 */
std::vector<dijkstra_row> Graph::dijkstra(size_t start) const {
  // Check for negative edge weights
  for (const auto &edge : edges) {
    if (edge.weight < 0) {
      std::cerr << "Error: Dijkstra's algorithm does not support graphs with negative edge weights." << std::endl;
      return {};
    }
  }

  std::vector<dijkstra_row> result(nvertices());
  std::vector<bool> visited(nvertices(), false);

  // Initialize the result table
  for (size_t i = 0; i < nvertices(); ++i) {
    result[i].vertex = i;
    result[i].visited = false;
    result[i].shortest_known = INFINITY;
    result[i].came_from = -1;
  }

  // Set the distance to the start vertex to 0
  result[start].shortest_known = 0;

  auto compare = [&](size_t a, size_t b) {
    return result[a].shortest_known > result[b].shortest_known;
  };

  // Use a priority queue to always choose the unvisited vertex with the shortest known distance
  /**
   * @brief Priority queue for Dijkstra's algorithm.
   * 
   * @return std::priority_queue<size_t, std::vector<size_t>, decltype(compare)> 
   */
  std::priority_queue<size_t, std::vector<size_t>, decltype(compare)> pq(compare);
  pq.push(start);

  while (!pq.empty()) {
    size_t current = pq.top();
    pq.pop();

    if (visited[current]) {
      continue; // Skip if already visited
    }

    visited[current] = true;

    // Update distances of neighbors change
    for (const auto &neighbor : out_adjacency_list(current)) {
      size_t v = neighbor.vertex;
      double new_distance = result[current].shortest_known + neighbor.weight;

      if (!visited[v] && new_distance < result[v].shortest_known) {
        result[v].shortest_known = new_distance;
        result[v].came_from = current;
        pq.push(v);
      }
    }
  }

  return result;
}


#endif /* NIU_CSCI340_GRAPH_H */
