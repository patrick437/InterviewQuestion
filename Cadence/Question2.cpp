#include <algorithm>
#include <queue>
#include <set>
#include <limits>
#include <vector>
#include <unordered_map>
#include <stdio.h>
#include <functional>
#include <iostream>


// The Node structure represents an directed acyclic graph

// A B C

// \ | /

//   D

// / | \

// E F G

// D.in_edges == {A,B,C}

// D.out_edges == {E,F,G}

struct Node {

    unsigned int cost;

    std::vector<Node*> in_edges;

    std::vector<Node*> out_edges;

    std::string name;

};



std::vector<Node*> shortest_path(

    const std::set<Node*>& begin_nodes, //!< the starting points of the graph 

    const std::set<Node*>& end_nodes //!< the end points of the graph

)

{

    // Please fill in code to return the shortest path computed

    // by summing the 'cost' of each node in a path from any Node

    // in begin_nodes to any Node in end_nodes



    // If A.cost == 1, B.cost == 2, C.cost == 3, D.cost==4, E.cost == 5, F.cost == 6, G.cost == 7

    // Then the shortest path would be {A,D,E} with a length of 10

    // Custom priority queue comparator
    // Distance map to store the shortest distance from any start node
    std::unordered_map<Node*, unsigned int> dist;
    // Previous node map to reconstruct the path
    std::unordered_map<Node*, Node*> prev;

    auto cmp = [&dist](Node* a, Node* b) { return dist[a] > dist[b]; };
    std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> pq(cmp);

    // Initialize distances to infinity
    unsigned int infinity = std::numeric_limits<unsigned int>::max();

    // Initialize all nodes with distance infinity
    for (Node* start : begin_nodes) {
        for (Node* next : start->out_edges) {
            dist[next] = infinity;
        }
    }

    // Set distances for start nodes
    for (Node* start : begin_nodes) {
        dist[start] = start->cost;
        prev[start] = nullptr;
        pq.push(start);
    }

    // Process nodes in order of increasing distance
    while (!pq.empty()) {
        Node* current = pq.top();
        pq.pop();

        // Process outgoing edges
        for (Node* neighbor : current->out_edges) {
            unsigned int new_dist = dist[current] + neighbor->cost;

            // If we found a shorter path
            if (!dist.count(neighbor) || new_dist < dist[neighbor]) {
                dist[neighbor] = new_dist;
                prev[neighbor] = current;
                pq.push(neighbor);
            }
        }
    }

    // Find the end node with the shortest distance
    Node* end = nullptr;
    unsigned int min_dist = infinity;

    for (Node* node : end_nodes) {
        if (dist.count(node) && dist[node] < min_dist) {
            min_dist = dist[node];
            end = node;
        }
    }

    // No path found
    if (end == nullptr) {
        return {};
    }

    // Reconstruct the path
    std::vector<Node*> path;
    for (Node* at = end; at != nullptr; at = prev[at]) {
        path.push_back(at);
    }

    // Reverse to get start-to-end path
    std::reverse(path.begin(), path.end());
    return path;
}



std::vector<Node*> longest_path(

    const std::set<Node*>& begin_nodes, //!< the starting points of the graph 

    const std::set<Node*>& end_nodes //!< the end points of the graph

)

{

    // Please fill in code to return the longest path computed

    // by summing the 'cost' of each node in a path from any Node

    // in begin_nodes to any Node in end_nodes



    // If A.cost == 1, B.cost == 2, C.cost == 3, D.cost==4, E.cost == 5, F.cost == 6, G.cost == 7

    // Then the longest path would be {C,D,G} with a length of 14

     // First, create a topological ordering of the nodes
    std::vector<Node*> topo_order;
    std::set<Node*> visited;

    // Helper function for topological sort using DFS
    std::function<void(Node*)> topoSort = [&](Node* node) {
        if (visited.find(node) != visited.end()) {
            return;
        }

        visited.insert(node);

        for (Node* neighbor : node->out_edges) {
            topoSort(neighbor);
        }

        topo_order.push_back(node);
        };

    // Perform topological sort starting from each begin node
    for (Node* start : begin_nodes) {
        topoSort(start);
    }

    //Reverse to get correct ordering
    std::reverse(topo_order.begin(), topo_order.end());

    //Maps to store longest distance and predecessor
    std::unordered_map<Node*, unsigned int> dist;
    std::unordered_map<Node*, Node*> prev;

    // Initialize distances for start nodes
    for (Node* node : topo_order) {
        dist[node] = 0;
        prev[node] = nullptr;
    }

    for (Node* start : begin_nodes) {
        dist[start] = start->cost;
    }

    // Process nodes in topological order
    for (Node* node : topo_order) {
        // Update distances of all outgoing edges
        for (Node* neighbor : node->out_edges) {
            unsigned int new_dist = dist[node] + neighbor->cost;

            if (new_dist > dist[neighbor]) {
                dist[neighbor] = new_dist;
                prev[neighbor] = node;
            }
        }
    }

    Node* end = nullptr;
    unsigned int max_dist = 0;

    for (Node* node : end_nodes) {
        if (dist.count(node) && dist[node] > max_dist) {
            max_dist = dist[node];
            end = node;
        }
    }

    // No path found
    if (end == nullptr) {
        return {};
    }

    std::vector<Node*> path;
    for (Node* at = end; at != nullptr; at = prev[at]) {
        path.push_back(at);
    }

    std::reverse(path.begin(), path.end());
    return path;

}

// Helper function to calculate total path cost
unsigned int calculate_path_cost(const std::vector<Node*>& path) {
    unsigned int total = 0;
    for (Node* node : path) {
        total += node->cost;
    }
    return total;
}

void print_path(const std::vector<Node*>& path) {
    if (path.empty()) {
        std::cout << "No path found!" << std::endl;
        return;
    }

    std::cout << "Path: ";
    for (size_t i = 0; i < path.size(); ++i) {
        std::cout << path[i]->name;
        if (i < path.size() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;

    std::cout << "Total cost: " << calculate_path_cost(path) << std::endl;
}

// This is the test function that can be called from main.cpp
void test_graph_paths() {
    // Create nodes A, B, C, D, E, F, G as per the example
    Node* A = new Node{ 1, {}, {}, "A" };
    Node* B = new Node{ 2, {}, {}, "B" };
    Node* C = new Node{ 3, {}, {}, "C" };
    Node* D = new Node{ 4, {}, {}, "D" };
    Node* E = new Node{ 5, {}, {}, "E" };
    Node* F = new Node{ 6, {}, {}, "F" };
    Node* G = new Node{ 7, {}, {}, "G" };

    A->out_edges.push_back(D);
    B->out_edges.push_back(D);
    C->out_edges.push_back(D);

    D->out_edges.push_back(E);
    D->out_edges.push_back(F);
    D->out_edges.push_back(G);

    D->in_edges = { A, B, C };
    E->in_edges = { D };
    F->in_edges = { D };
    G->in_edges = { D };

    std::set<Node*> begin_nodes = { A, B, C };
    std::set<Node*> end_nodes = { E, F, G };

    std::cout << "Finding shortest path..." << std::endl;
    std::vector<Node*> shortest = shortest_path(begin_nodes, end_nodes);
    print_path(shortest);

    std::cout << "\nFinding longest path..." << std::endl;
    std::vector<Node*> longest = longest_path(begin_nodes, end_nodes);
    print_path(longest);

    // Clean up memory
    delete A;
    delete B;
    delete C;
    delete D;
    delete E;
    delete F;
    delete G;
}