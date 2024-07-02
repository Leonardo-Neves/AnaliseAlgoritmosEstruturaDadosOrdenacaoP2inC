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

#include "ProgressBar.hpp"

std::vector<std::vector<std::vector<int>>> generateDataset(std::vector<int> lengthLists) {

    /*
        Exemplo de vetor de saída
        [
            [   Ordered
                [0 ... 10],
                [0 ... 100],
                [0 ... 1000],
                [0 ... 10000]
            ],
            [   OrderedInverse
                [0 ... 10],
                [0 ... 100],
                [0 ... 1000],
                [0 ... 10000]
            ],
            [   AlmostOrdered
                [0 ... 10],
                [0 ... 100],
                [0 ... 1000],
                [0 ... 10000]
            ],
            [   Random
                [0 ... 10],
                [0 ... 100],
                [0 ... 1000],
                [0 ... 10000]
            ],
        ]
    */

    // Criando uma instância do gerador de conjunto de dados
    DatasetGenerator datasetGenerator;

    std::vector<std::vector<std::vector<int>>> datasets;

    // Gerando parte do conjunto de dados para dados ordenados
    std::vector<std::vector<int>> datasets_temporary_ordered;
    for (int i = 0; i < lengthLists.size(); ++i) {
        datasets_temporary_ordered.push_back(datasetGenerator.generateOrdered(lengthLists[i]));
    }
    datasets.push_back(datasets_temporary_ordered);

    // Gerando parte do conjunto de dados para dados ordenados inversamente
    std::vector<std::vector<int>> datasets_temporary_ordered_inverse;
    for (int i = 0; i < lengthLists.size(); ++i) {
        datasets_temporary_ordered_inverse.push_back(datasetGenerator.generateOrderedInverse(lengthLists[i]));
    }
    datasets.push_back(datasets_temporary_ordered_inverse);

    // Gerando parte do conjunto de dados para dados ordenados parcialmente
    std::vector<std::vector<int>> datasets_temporary_almost_ordered;
    for (int i = 0; i < lengthLists.size(); ++i) {
        datasets_temporary_almost_ordered.push_back(datasetGenerator.generateAlmostOrdered(lengthLists[i]));
    }
    datasets.push_back(datasets_temporary_almost_ordered);

    // Gerando parte do conjunto de dados para dados ordenados randômicamente
    std::vector<std::vector<int>> datasets_temporary_random;
    for (int i = 0; i < lengthLists.size(); ++i) {
        datasets_temporary_random.push_back(datasetGenerator.generateRandom(lengthLists[i]));
    }
    datasets.push_back(datasets_temporary_random);

    return datasets;
}

int main() {

    std::string output_path = "/home/leo/AAED_P2/output";

    std::vector<int> lengthLists = {10, 100, 1000, 10000, 100000, 1000000};
    
    std::vector<std::string> datasets_name = {
        "Ordered",
        "OrderedInverse",
        "AlmostOrdered",
        "Random"
    };
    
    auto datasets = generateDataset(lengthLists);
    
    std::map<std::string, SearchAlgorithm*> methods;
    methods["linearSearch"] = new LinearSearch();
    methods["binarySearch"] = new BinarySearch();
    methods["binarySearchTree"] = new BinarySearchTree();
    methods["avlTree"] = new AVLTree();
    methods["redBlackTree"] = new RedBlackTree();
    methods["treapTree"] = new Treap();

    std::ofstream file("output.csv");

    file << "Algorithm;DatasetName;DatasetSize;Time Insere;Counter Comparisons Insere;Time Pesquisa;Counter Comparisons Pesquisa;Time Retira;Counter Comparisons Retira\n";

    int total_iterations = methods.size() * datasets.size() * datasets[0].size();
    ProgressBar progress(total_iterations);
    
    if (file.is_open()) {

        for (auto function = methods.begin(); function != methods.end(); ++function) {
        
            for (int i = 0; i < datasets.size(); ++i) {

                for (int j = 0; j < datasets[i].size(); ++j) {
                    
                    try {
                        std::cout << function->first << " " << datasets[i][j].size() << std::endl;
                        int counter_comparisons_insere = 0;
                        std::clock_t start = std::clock();
                        auto result_testInsere = function->second->testInsere(datasets[i][j], &counter_comparisons_insere);
                        std::clock_t end = std::clock();
                        long double diff_insertion = 1000.0 * (end - start) / CLOCKS_PER_SEC;
                        
                        int counter_comparisons_pesquisa = 0;
                        start = std::clock();
                        auto result_testPesquisa = function->second->testPesquisa(result_testInsere, datasets[i][j], &counter_comparisons_pesquisa);
                        end = std::clock();
                        long double diff_pesquisa = 1000.0 * (end - start) / CLOCKS_PER_SEC;
                        
                        int counter_comparisons_retira = 0;
                        start = std::clock();
                        auto result_testRetira = function->second->testRetira(result_testInsere, datasets[i][j], &counter_comparisons_retira);
                        end = std::clock();
                        long double diff_retira = 1000.0 * (end - start) / CLOCKS_PER_SEC;
                        
                        {
                            file << function->first << ";" << datasets_name[i] << ";" 
                                << datasets[i][j].size() << ";" << diff_insertion << ";" << counter_comparisons_insere<< ";" 
                                << diff_pesquisa << ";" << counter_comparisons_pesquisa<< ";" 
                                << diff_retira << ";" << counter_comparisons_retira<< ";" << "\n";
                        }

                        progress.update();
                    } catch (const std::exception& e) {
                        std::cerr << e.what() << std::endl;
                    }
                }
            }
        }
    }

    file.close();

    return 0;
}