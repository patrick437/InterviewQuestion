#include <iostream>
using namespace std;

// The aim is to not modify the Node struct

// This would represent an old legacy datastructure and we want to use it in new c++11 code

struct Node {

    int data;

    Node* next;

};

// container can contain anything that you want, ideally it should not need to take a copy of the original data

struct container {

    // Fill in code here such that the ranged based for loop in func() works
    Node* node;


    explicit container(Node* node) : node(node) {} 

    class iterator {  
    private:
        Node* current;   

    public:
        explicit iterator(Node* node) : current(node) {}

		iterator& operator++() {
			current = current->next;
			return *this;
		}

		bool operator!=(const iterator& other) const {
			return current != other.current;
		}

        // Dereference operator - retrieves the current node's data
		int operator*() const {
			return current->data;
		}
	};


    // Member functions that return iterators
    iterator begin() const {
        return iterator(node);
    }

    iterator end() const {
        return iterator(nullptr);
    }


};



void func(Node* node) {

    for (auto data : container(node)) {

        cout << data << " ";

    }

}


// This is the test function that can be called from main.cpp
void test_node_container() {
    Node* mylist = new Node{ 1, new Node{2, new Node{3, new Node{4, nullptr}}} };

    cout << "Testing container with range-based for loop:" << endl;
    cout << "Expected output: 1 2 3 4" << endl;
    cout << "Actual output:   ";
    func(mylist); // should print "1 2 3 4";
    cout << endl;

    // Clean up memory
    Node* current = mylist;
    while (current) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}



