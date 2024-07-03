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

#include "datasetGenerator.h"

int main() {

    DatasetGenerator datasetGenerator;

    BinarySearchTree redBlackTree;
    
    int counter = 0;

    int dataset_size = 1000000;

    auto dataset = datasetGenerator.generateAlmostOrdered(dataset_size);
    std::cout << "generateAlmostOrdered" << std::endl;
    
    auto result = redBlackTree.testInsere(dataset, &counter);
    // std::cout << "2" << std::endl;
    // redBlackTree.testPesquisa(result, dataset, &counter);
    // std::cout << "3" << std::endl;
    // redBlackTree.testRetira(result, dataset, &counter);

    // auto dataset2 = datasetGenerator.generateOrderedInverse(dataset_size);
    // std::cout << "generateOrderedInverse" << std::endl;
    // std::cout << "1" << std::endl;
    // auto result2 = redBlackTree.testInsere(dataset2, &counter);
    // std::cout << "2" << std::endl;
    // redBlackTree.testPesquisa(result2, dataset2, &counter);
    // std::cout << "3" << std::endl;
    // redBlackTree.testRetira(result2, dataset2, &counter);

    // auto dataset3 = datasetGenerator.generateAlmostOrdered(dataset_size);
    // std::cout << "generateAlmostOrdered" << std::endl;
    // std::cout << "1" << std::endl;
    // auto result3 = redBlackTree.testInsere(dataset3, &counter);
    // std::cout << "2" << std::endl;
    // redBlackTree.testPesquisa(result3, dataset3, &counter);
    // std::cout << "3" << std::endl;
    // redBlackTree.testRetira(result3, dataset3, &counter);

    // auto dataset4 = datasetGenerator.generateRandom(dataset_size);
    // std::cout << "generateRandom" << std::endl;
    // std::cout << "1" << std::endl;
    // auto result4 = redBlackTree.testInsere(dataset4, &counter);
    // std::cout << "2" << std::endl;
    // redBlackTree.testPesquisa(result4, dataset4, &counter);
    // std::cout << "3" << std::endl;
    // redBlackTree.testRetira(result4, dataset4, &counter);


    return 0;
}