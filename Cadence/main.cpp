#include <iostream>

// Forward declarations of test functions from different files
// You'll need to declare all your test functions here

// From graph_paths.cpp
void test_graph_paths();

// From node_container.cpp
void test_node_container();

// From string_class.cpp
void test_string_class();

// Add more test function declarations as needed for your other problems

int main() {
    int choice;

    std::cout << "Select which test to run:" << std::endl;
    std::cout << "1. Graph Paths" << std::endl;
    std::cout << "2. Node Container" << std::endl;
    std::cout << "3. String Class" << std::endl;
    // Add more options as needed
    std::cout << "Enter choice (1-3): ";
    std::cin >> choice;

    switch (choice) {
    case 1:
        std::cout << "\nRunning Graph Paths test:\n" << std::endl;
        test_graph_paths();
        break;
    case 2:
        std::cout << "\nRunning Node Container test:\n" << std::endl;
        test_node_container();
        break;
    default:
        std::cout << "Invalid choice!" << std::endl;
        break;
    }

    std::cout << "\nTest completed. Press Enter to exit..." << std::endl;
    std::cin.ignore();
    std::cin.get();

    return 0;
}