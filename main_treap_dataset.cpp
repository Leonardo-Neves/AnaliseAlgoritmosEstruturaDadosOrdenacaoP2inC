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
#include <exception>

#include "AVLTree.h"
#include "binarySearch.h"
#include "binarySearchTree.h"
#include "linearSearch.h"
#include "redBlackTree.h"
#include "treapTree.h"
#include "datasetGenerator.h"

int main() {

    DatasetGenerator datasetGenerator;

    Treap treap;
    
    int counter = 0;

    auto dataset = datasetGenerator.generateOrdered(1000000);
    std::cout << "generateOrdered" << std::endl;
    std::cout << "1" << std::endl;
    auto result = treap.testInsere(dataset, &counter);
    std::cout << "2" << std::endl;
    treap.testPesquisa(result, dataset, &counter);
    std::cout << "3" << std::endl;
    treap.testRetira(result, dataset, &counter);

    auto dataset2 = datasetGenerator.generateOrderedInverse(1000000);
    std::cout << "generateOrderedInverse" << std::endl;
    std::cout << "1" << std::endl;
    auto result2 = treap.testInsere(dataset2, &counter);
    std::cout << "2" << std::endl;
    treap.testPesquisa(result2, dataset2, &counter);
    std::cout << "3" << std::endl;
    treap.testRetira(result2, dataset2, &counter);

    auto dataset3 = datasetGenerator.generateAlmostOrdered(1000000);
    std::cout << "generateAlmostOrdered" << std::endl;
    std::cout << "1" << std::endl;
    auto result3 = treap.testInsere(dataset3, &counter);
    std::cout << "2" << std::endl;
    treap.testPesquisa(result3, dataset3, &counter);
    std::cout << "3" << std::endl;
    treap.testRetira(result3, dataset3, &counter);

    auto dataset4 = datasetGenerator.generateRandom(1000000);
    std::cout << "generateRandom" << std::endl;
    std::cout << "1" << std::endl;
    auto result4 = treap.testInsere(dataset4, &counter);
    std::cout << "2" << std::endl;
    treap.testPesquisa(result4, dataset4, &counter);
    std::cout << "3" << std::endl;
    treap.testRetira(result4, dataset4, &counter);


    return 0;
}