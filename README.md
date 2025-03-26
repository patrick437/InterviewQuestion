1. Creating wrappers to use old datastructures in modern code:

 

#include <iostream>

// The aim is to not modify the Node struct

// This would represent an old legacy datastructure and we want to use it in new c++11 code

struct Node {

    int data;

    Node *next;

};

 

// container can contain anything that you want, ideally it should not need to take a copy of the original data

struct container {

    // Fill in code here such that the ranged based for loop in func() works

};

 

void func(Node * node) {

    for ( auto data : container(node) ) {

        cout << data << " "; 

    }

}

 

void test() {

    Node* mylist = new Node{1, new Node{2, new Node{3, new Node{4, nullptr}}}};

    func(mylist); // should print "1 2 3 4";

}

 

2. longest/shortest paths through a graph

#include <algorithm>

#include <set>

#include <vector>

 

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

 

}

 

3.  Review this string class.

What is wrong with the code?

What would you change?

Write comments inline in a separate colour.

 

#ifndef STRING_H

#define STRING_H

 

#include <cstring>

 

class string

{

public:

 

    string();

    ~string();

 

    string(char* letters);

    string(string const& rhs);

 

    string& operator=(char* letters);

    string& operator=(string rhs);

 

    void append( char* letters);

    size_t length();

 

    bool is_empty();

    void empty();

 

    char* c_str()

    {

        return m_szchars;

    }

 

    char* m_szchars;

    int f_count_;

 

};

 

string::string()

    : f_count_ {0}

{

    m_szchars = 0;

}

 

string::~string()

{

    free(m_szchars);

}

 

string::string( char* letters )

{

    f_count_ = strlen(letters);

    m_szchars = new char[f_count_];

    for( int i = 0; i < f_count_; ++i)

    {

        m_szchars[i] = letters[i];

    }

}

 

string::string( string const& rhs)

{

    f_count_ = strlen(rhs.m_szchars);

    m_szchars = new char[f_count_];

    for( int i = 0; i < f_count_; ++i)

    {

        m_szchars[i] = rhs.m_szchars[i];

    }

}

