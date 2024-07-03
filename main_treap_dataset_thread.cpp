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
#include "treapTree.h"

#include "datasetGenerator.h"

using namespace std;

std::mutex mtx;

void runExperiment(SearchAlgorithm* algorithm, std::string algorithms_name, std::vector<int> dataset, std::string dataset_name, std::ofstream& file, int interation) {

    int counter_comparisons_insere = 0;
    std::clock_t start = std::clock();
    auto result = algorithm->testInsere(dataset, &counter_comparisons_insere);
    std::clock_t end = std::clock();

    long double diff_insertion = 1000.0 * (end - start) / CLOCKS_PER_SEC;

    int counter_comparisons_pesquisa = 0;
    start = std::clock();
    algorithm->testPesquisa(result, dataset, &counter_comparisons_pesquisa);
    end = std::clock();

    long double diff_pesquisa = 1000.0 * (end - start) / CLOCKS_PER_SEC;

    int counter_comparisons_retira = 0;
    start = std::clock();
    algorithm->testRetira(result, dataset, &counter_comparisons_retira);
    end = std::clock();

    long double diff_retira = 1000.0 * (end - start) / CLOCKS_PER_SEC;

    {
        std::lock_guard<std::mutex> lock(mtx);
        file << interation << ";" << algorithms_name << ";" << dataset_name << ";" << dataset.size() << ";" << diff_insertion << ";" << counter_comparisons_insere<< ";" << diff_pesquisa << ";" << counter_comparisons_pesquisa<< ";" << diff_retira << ";" << counter_comparisons_retira << "\n";
    }
}

int main() {

    DatasetGenerator datasetGenerator;
    std::vector<int> tamanhos = {10, 100, 1000, 10000, 100000, 1000000};
    std::vector<std::vector<int>> datasets;

    int NUMBER_INTERATIONS = 10;

    std::vector<std::string> datasets_name = {
        "Ordered",
        "OrderedInverse",
        "AlmostOrdered",
        "Random"
    };

    std::vector<std::string> algorithms = {
        "TreapTree",
        "AVLTree",
        "RedBlackTree",
        "BinarySearchTree",
        "BinarySearch",
        "LinearSearch"
    };

    std::map<std::string, SearchAlgorithm*> methods;
    methods["linearSearch"] = new LinearSearch();
    methods["binarySearch"] = new BinarySearch();
    methods["binarySearchTree"] = new BinarySearchTree();
    methods["avlTree"] = new AVLTree();
    methods["redBlackTree"] = new RedBlackTree();
    methods["treapTree"] = new Treap();

    for (int j = 0; j < NUMBER_INTERATIONS; ++j) {

        std::ofstream file(std::to_string(j) + ".csv");

        file << "Interation;Algorithm;DatasetName;DatasetSize;Time Insere;Counter Comparisons Insere;Time Pesquisa;Counter Comparisons Pesquisa;Time Retira;Counter Comparisons Retira\n";

        if (file.is_open()) {

            for (int tam : tamanhos) {

                std::cout << "Tamanho: " << tam << std::endl;

                int counter = 0;
                datasets.clear();
                datasets.push_back(datasetGenerator.generateOrdered(tam));
                datasets.push_back(datasetGenerator.generateOrderedInverse(tam));
                datasets.push_back(datasetGenerator.generateAlmostOrdered(tam));
                datasets.push_back(datasetGenerator.generateRandom(tam));

                std::vector<std::thread> threads;

                for (int i = 0; i < datasets.size(); ++i) {
                    for (auto function = methods.begin(); function != methods.end(); ++function) {
                        threads.emplace_back(runExperiment, function->second, function->first, datasets[i], datasets_name[i], std::ref(file), j);
                    }
                }

                for (long long i = 0; i < threads.size(); ++i) {
                    threads[i].join();
                }
            }
        }

        file.close();
    }

    return 0;
}
