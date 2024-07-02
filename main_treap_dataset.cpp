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
#include <sstream>

#include "searchAlgorithm.h"
#include "linearSearch.h"
#include "binarySearch.h"
#include "binarySearchTree.h"
#include "AVLTree.h"
#include "redBlackTree.h"
#include "datasetGenerator.h"
#include "treapTree.h"
#include "tqdm.hpp"

using namespace std;

// Function to get current date and time as a string in dd_mm_yyyy_hh_mm_ss format
std::string getCurrentDateTime() {
    std::time_t now = std::time(nullptr);
    std::tm *ltm = std::localtime(&now);

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << ltm->tm_mday << "_"
        << std::setw(2) << std::setfill('0') << 1 + ltm->tm_mon << "_"
        << 1900 + ltm->tm_year << "_"
        << std::setw(2) << std::setfill('0') << ltm->tm_hour << "_"
        << std::setw(2) << std::setfill('0') << ltm->tm_min << "_"
        << std::setw(2) << std::setfill('0') << ltm->tm_sec;

    return oss.str();
}

int main() {
    DatasetGenerator datasetGenerator;

    std::vector<int> tamanhos = {10,100,1000, 10000, 100000, 1000000};
    int NUMBER_ITERATIONS = 1;
    std::vector<std::string> datasets_name = {"Ordered", "OrderedInverse", "AlmostOrdered", "Random"};
    std::vector<std::string> algorithms = {
        "TreapTree", 
        "AVLTree", 
        "RedBlackTree", 
        "BinarySearchTree", 
        "BinarySearch", 
        "LinearSearch"
    };
    std::vector<std::vector<int>> datasets;

    // Generate the filename with current date and time
    std::string filename = "output_" + getCurrentDateTime() + ".csv";
    
    // Open the file in append mode
    std::ofstream file(filename, std::ofstream::app);

    // Write header if file is empty
    if (file.tellp() == 0) {
        file << "Iteration;Algorithm;DatasetName;DatasetSize;Time Insere;Counter Comparisons Insere;Time Pesquisa;Counter Comparisons Pesquisa;Time Retira;Counter Comparisons Retira\n";
    }
    
    for (int j = 0; j < NUMBER_ITERATIONS; ++j) {
        for (int tam : tq::tqdm(tamanhos)) {
            datasets.clear(); // Clear the datasets vector for the next size
            datasets.push_back(datasetGenerator.generateOrdered(tam));
            datasets.push_back(datasetGenerator.generateOrderedInverse(tam));
            datasets.push_back(datasetGenerator.generateAlmostOrdered(tam));
            datasets.push_back(datasetGenerator.generateRandom(tam));

            for (int i = 0; i < datasets.size(); i++) {
                // Test each algorithm
                {
                    int counter_comparisons_insere = 0; 
                    Treap treap;
                    std::clock_t start = std::clock();
                    auto result = treap.testInsere(datasets[i], &counter_comparisons_insere);
                    std::clock_t end = std::clock();

                    long double diff_insertion = 1000.0 * (end - start) / CLOCKS_PER_SEC;

                    int counter_comparisons_pesquisa = 0;
                    start = std::clock();
                    treap.testPesquisa(result, datasets[i], &counter_comparisons_pesquisa);
                    end = std::clock();

                    long double diff_pesquisa = 1000.0 * (end - start) / CLOCKS_PER_SEC;

                    int counter_comparisons_retira = 0;
                    start = std::clock();
                    treap.testRetira(result, datasets[i], &counter_comparisons_retira);
                    end = std::clock();

                    long double diff_retira = 1000.0 * (end - start) / CLOCKS_PER_SEC;

                    file << to_string(j+1) << ";" << algorithms[0] << ";" << datasets_name[i] << ";" 
                         << tam << ";" << diff_insertion << ";" << counter_comparisons_insere << ";" 
                         << diff_pesquisa << ";" << counter_comparisons_pesquisa << ";" 
                         << diff_retira << ";" << counter_comparisons_retira << "\n";
                    file.flush();
                }

                // Repeat the same block for AVLTree, RedBlackTree, LinearSearch, BinarySearch, BinarySearchTree
                {
                    int counter_comparisons_insere = 0; 
                    AVLTree avlTree;
                    std::clock_t start = std::clock();
                    auto result = avlTree.testInsere(datasets[i], &counter_comparisons_insere);
                    std::clock_t end = std::clock();

                    long double diff_insertion = 1000.0 * (end - start) / CLOCKS_PER_SEC;

                    int counter_comparisons_pesquisa = 0;
                    start = std::clock();
                    avlTree.testPesquisa(result, datasets[i], &counter_comparisons_pesquisa);
                    end = std::clock();

                    long double diff_pesquisa = 1000.0 * (end - start) / CLOCKS_PER_SEC;

                    int counter_comparisons_retira = 0;
                    start = std::clock();
                    avlTree.testRetira(result, datasets[i], &counter_comparisons_retira);
                    end = std::clock();

                    long double diff_retira = 1000.0 * (end - start) / CLOCKS_PER_SEC;

                    file << to_string(j+1) << ";" << algorithms[1] << ";" << datasets_name[i] << ";" 
                         << tam << ";" << diff_insertion << ";" << counter_comparisons_insere << ";" 
                         << diff_pesquisa << ";" << counter_comparisons_pesquisa << ";" 
                         << diff_retira << ";" << counter_comparisons_retira << "\n";
                    file.flush();
                }

                {
                    int counter_comparisons_insere = 0; 
                    RedBlackTree redBlackTree;
                    std::clock_t start = std::clock();
                    auto result = redBlackTree.testInsere(datasets[i], &counter_comparisons_insere);
                    std::clock_t end = std::clock();

                    long double diff_insertion = 1000.0 * (end - start) / CLOCKS_PER_SEC;

                    int counter_comparisons_pesquisa = 0;
                    start = std::clock();
                    redBlackTree.testPesquisa(result, datasets[i], &counter_comparisons_pesquisa);
                    end = std::clock();

                    long double diff_pesquisa = 1000.0 * (end - start) / CLOCKS_PER_SEC;

                    int counter_comparisons_retira = 0;
                    start = std::clock();
                    redBlackTree.testRetira(result, datasets[i], &counter_comparisons_retira);
                    end = std::clock();

                    long double diff_retira = 1000.0 * (end - start) / CLOCKS_PER_SEC;

                    file << to_string(j+1) << ";" << algorithms[2] << ";" << datasets_name[i] << ";" 
                         << tam << ";" << diff_insertion << ";" << counter_comparisons_insere << ";" 
                         << diff_pesquisa << ";" << counter_comparisons_pesquisa << ";" 
                         << diff_retira << ";" << counter_comparisons_retira << "\n";
                    file.flush();
                }

                {
                    int counter_comparisons_insere = 0; 
                    LinearSearch linearSearch;
                    std::clock_t start = std::clock();
                    auto result = linearSearch.testInsere(datasets[i], &counter_comparisons_insere);
                    std::clock_t end = std::clock();

                    long double diff_insertion = 1000.0 * (end - start) / CLOCKS_PER_SEC;

                    int counter_comparisons_pesquisa = 0;
                    start = std::clock();
                    linearSearch.testPesquisa(result, datasets[i], &counter_comparisons_pesquisa);
                    end = std::clock();

                    long double diff_pesquisa = 1000.0 * (end - start) / CLOCKS_PER_SEC;

                    int counter_comparisons_retira = 0;
                    start = std::clock();
                    linearSearch.testRetira(result, datasets[i], &counter_comparisons_retira);
                    end = std::clock();

                    long double diff_retira = 1000.0 * (end - start) / CLOCKS_PER_SEC;

                    file << to_string(j+1) << ";" << algorithms[3] << ";" << datasets_name[i] << ";" 
                         << tam << ";" << diff_insertion << ";" << counter_comparisons_insere << ";" 
                         << diff_pesquisa << ";" << counter_comparisons_pesquisa << ";" 
                         << diff_retira << ";" << counter_comparisons_retira << "\n";
                    file.flush();
                }

                {
                    int counter_comparisons_insere = 0; 
                    BinarySearch binarySearch;
                    std::clock_t start = std::clock();
                    auto result = binarySearch.testInsere(datasets[i], &counter_comparisons_insere);
                    std::clock_t end = std::clock();

                    long double diff_insertion = 1000.0 * (end - start) / CLOCKS_PER_SEC;

                    int counter_comparisons_pesquisa = 0;
                    start = std::clock();
                    binarySearch.testPesquisa(result, datasets[i], &counter_comparisons_pesquisa);
                    end = std::clock();

                    long double diff_pesquisa = 1000.0 * (end - start) / CLOCKS_PER_SEC;

                    int counter_comparisons_retira = 0;
                    start = std::clock();
                    binarySearch.testRetira(result, datasets[i], &counter_comparisons_retira);
                    end = std::clock();

                    long double diff_retira = 1000.0 * (end - start) / CLOCKS_PER_SEC;

                    file << to_string(j+1) << ";" << algorithms[4] << ";" << datasets_name[i] << ";" 
                         << tam << ";" << diff_insertion << ";" << counter_comparisons_insere << ";" 
                         << diff_pesquisa << ";" << counter_comparisons_pesquisa << ";" 
                         << diff_retira << ";" << counter_comparisons_retira << "\n";
                    file.flush();
                }

                {
                    int counter_comparisons_insere = 0; 
                    BinarySearchTree binarySearchTree;
                    std::clock_t start = std::clock();
                    auto result = binarySearchTree.testInsere(datasets[i], &counter_comparisons_insere);
                    std::clock_t end = std::clock();

                    long double diff_insertion = 1000.0 * (end - start) / CLOCKS_PER_SEC;

                    int counter_comparisons_pesquisa = 0;
                    start = std::clock();
                    binarySearchTree.testPesquisa(result, datasets[i], &counter_comparisons_pesquisa);
                    end = std::clock();

                    long double diff_pesquisa = 1000.0 * (end - start) / CLOCKS_PER_SEC;

                    int counter_comparisons_retira = 0;
                    start = std::clock();
                    binarySearchTree.testRetira(result, datasets[i], &counter_comparisons_retira);
                    end = std::clock();

                    long double diff_retira = 1000.0 * (end - start) / CLOCKS_PER_SEC;

                    file << to_string(j+1) << ";" << algorithms[5] << ";" << datasets_name[i] << ";" 
                         << tam << ";" << diff_insertion << ";" << counter_comparisons_insere << ";" 
                         << diff_pesquisa << ";" << counter_comparisons_pesquisa << ";" 
                         << diff_retira << ";" << counter_comparisons_retira << "\n";
                    file.flush();
                }
            }
        }
    }
    file.close();
    return 0;
}
