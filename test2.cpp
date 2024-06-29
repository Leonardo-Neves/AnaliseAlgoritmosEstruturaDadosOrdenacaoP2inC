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

#include "redBlackTree.h"
#include "datasetGenerator.h"

int main() {

    DatasetGenerator datasetGenerator;

    RedBlackTree redBlackTree;

    auto dataset = datasetGenerator.generateAlmostOrdered(1000000);

    // std::ofstream file("test.txt");

    // if (file.is_open()) {
    //     for (int i = 0; i < dataset.size(); ++i) {
    //         {
    //             file << dataset[i] << "\n";
    //         }
    //     }
    // }

    // file.close();

    
    int counter = 0;

    auto result = redBlackTree.testInsere(dataset, &counter);

    auto result1 = redBlackTree.testPesquisa(result, dataset, &counter);

    auto result2 = redBlackTree.testRetira(result, dataset, &counter);


    return 0;
}