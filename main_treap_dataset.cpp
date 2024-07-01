#include <iostream>
#include <vector>
#include <functional>
#include <map>
#include <string>
#include <utility>
#include <chrono>
#include <fstream>
#include <random>
#include <ctime>
#include <mutex>
#include <thread>
#include <atomic>
#include <iomanip>

#include "searchAlgorithm.h"

#include "linearSearch.h"
#include "binarySearch.h"
#include "binarySearchTree.h"
#include "AVLTree.h"
#include "redBlackTree.h"

#include "datasetGenerator.h"

using namespace std;
#include "treapTree.h"

int main() {

    DatasetGenerator datasetGenerator;

    // std::vector<int> tamanhos = {10, 100, 1000};
    std::vector<int> tamanhos = {10, 100, 1000, 10000, 100000, 1000000};
    std::vector<std::vector<int>> datasets;
    for (int tam : tamanhos) {
        int counter = 0; // Reset the counter for each tree size
        datasets.clear(); // Limpa o vetor de datasets para o próximo tamanho
        datasets.push_back(datasetGenerator.generateOrdered(tam));
        datasets.push_back(datasetGenerator.generateOrderedInverse(tam));
        datasets.push_back(datasetGenerator.generateAlmostOrdered(tam));
        datasets.push_back(datasetGenerator.generateRandom(tam));

        for (auto dataset: datasets) {
        
            std::cout << "Treap" << std::endl;
            {
                counter = 0; // Reset the counter for each tree size
                Treap treap;
                // std::cout << "1" << std::endl;
                auto result = treap.testInsere(dataset, &counter);
                // std::cout << "2" << std::endl;
                treap.testPesquisa(result, dataset, &counter);
                // std::cout << "3" << std::endl;
                treap.testRetira(result, dataset, &counter);
            }

            std::cout << "AVLTree" << std::endl;
            {
                counter = 0; // Reset the counter for each tree size
                AVLTree avl;
                // std::cout << "1" << std::endl;
                auto result = avl.testInsere(dataset, &counter);
                // std::cout << "2" << std::endl;
                avl.testPesquisa(result, dataset, &counter);
                // std::cout << "3" << std::endl;
                avl.testRetira(result, dataset, &counter);
            }

            std::cout << "RedBlackTree" << std::endl;
            {
                counter = 0; // Reset the counter for each tree size
                RedBlackTree redBlack;
                std::cout << "1" << std::endl;
                auto result = redBlack.testInsere(dataset, &counter);
                std::cout << "2" << std::endl;
                redBlack.testPesquisa(result, dataset, &counter);
                std::cout << "3" << std::endl;
                redBlack.testRetira(result, dataset, &counter);
            }

            std::cout << "LinearSearch" << std::endl;
            {
                counter = 0; // Reset the counter for each tree size
                LinearSearch linear;
                // std::cout << "1" << std::endl;
                auto result = linear.testInsere(dataset, &counter);
                // std::cout << "2" << std::endl;
                linear.testPesquisa(result, dataset, &counter);
                // std::cout << "3" << std::endl;
                linear.testRetira(result, dataset, &counter);
            }

            std::cout << "BinarySearch" << std::endl;
            {
                counter = 0; // Reset the counter for each tree size
                BinarySearch binarySearch;
                // std::cout << "1" << std::endl;
                auto result = binarySearch.testInsere(dataset, &counter);
                // std::cout << "2" << std::endl;
                binarySearch.testPesquisa(result, dataset, &counter);
                // std::cout << "3" << std::endl;
                binarySearch.testRetira(result, dataset, &counter);
            }

            std::cout << "BinarySearchTree" << std::endl;
            {
                BinarySearchTree binarySearchTree;
                // std::cout << "1" << std::endl;
                auto result = binarySearchTree.testInsere(dataset, &counter);
                // std::cout << "2" << std::endl;
                binarySearchTree.testPesquisa(result, dataset, &counter);
                // std::cout << "3" << std::endl;
                binarySearchTree.testRetira(result, dataset, &counter);
            }
        }
    }

    return 0;
}
