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

#include "treapTree.h" 
#include "datasetGenerator.h"

int main() {

    DatasetGenerator datasetGenerator;

    Treap treap;

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

    auto result = treap.testInsere(dataset, &counter);

    auto result1 = treap.testPesquisa(result, dataset, &counter);

    auto result2 = treap.testRetira(result, dataset, &counter);


    return 0;
}