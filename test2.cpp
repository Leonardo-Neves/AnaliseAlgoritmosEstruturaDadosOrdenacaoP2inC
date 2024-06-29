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
    
    int counter = 0;

    redBlackTree.testInsere(dataset, &counter);


    return 0;
}