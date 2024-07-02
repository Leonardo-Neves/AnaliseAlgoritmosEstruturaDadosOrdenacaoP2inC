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

    for (int j = 0; j < datasets.size(); ++j) {

        std::ofstream file(std::to_string(j) + ".csv");

        file << "Algorithm;DatasetName;DatasetSize;Time Insere;Counter Comparisons Insere;Time Pesquisa;Counter Comparisons Pesquisa;Time Retira;Counter Comparisons Retira\n";

        if (file.is_open()) {

            for (int tam : tamanhos) {

                std::cout << "Tamanho: " << tam << std::endl;

                int counter = 0;
                datasets.clear();
                datasets.push_back(datasetGenerator.generateOrdered(tam));
                datasets.push_back(datasetGenerator.generateOrderedInverse(tam));
                datasets.push_back(datasetGenerator.generateAlmostOrdered(tam));
                datasets.push_back(datasetGenerator.generateRandom(tam));

                for (int i = 0; i < datasets.size(); ++i) {
                
                    std::cout << "Treap" << std::endl;
                    {
                        int counter_comparisons_insere = 0; // Reset the counter for each tree size
                        Treap treap;
                        std::cout << "1" << std::endl;
                        std::clock_t start = std::clock();
                        auto result = treap.testInsere(datasets[i], &counter_comparisons_insere);
                        std::clock_t end = std::clock();

                        long double diff_insertion = 1000.0 * (end - start) / CLOCKS_PER_SEC;

                        std::cout << "2" << std::endl;
                        int counter_comparisons_pesquisa = 0;
                        start = std::clock();
                        treap.testPesquisa(result, datasets[i], &counter_comparisons_pesquisa);
                        end = std::clock();

                        long double diff_pesquisa = 1000.0 * (end - start) / CLOCKS_PER_SEC;

                        std::cout << "3" << std::endl;
                        int counter_comparisons_retira = 0;
                        start = std::clock();
                        treap.testRetira(result, datasets[i], &counter_comparisons_retira);
                        end = std::clock();

                        long double diff_retira = 1000.0 * (end - start) / CLOCKS_PER_SEC;

                        {
                            file << algorithms[0] << ";" << datasets_name[i] << ";" 
                                << tam << ";" << diff_insertion << ";" << counter_comparisons_insere<< ";" 
                                << diff_pesquisa << ";" << counter_comparisons_pesquisa<< ";" 
                                << diff_retira << ";" << counter_comparisons_retira<< ";" << "\n";
                        }
                    }

                    std::cout << "AVLTree" << std::endl;
                    {
                        int counter_comparisons_insere = 0; // Reset the counter for each tree size
                        AVLTree avlTree;
                        std::cout << "1" << std::endl;
                        std::clock_t start = std::clock();
                        auto result = avlTree.testInsere(datasets[i], &counter_comparisons_insere);
                        std::clock_t end = std::clock();

                        long double diff_insertion = 1000.0 * (end - start) / CLOCKS_PER_SEC;

                        std::cout << "2" << std::endl;
                        int counter_comparisons_pesquisa = 0;
                        start = std::clock();
                        avlTree.testPesquisa(result, datasets[i], &counter_comparisons_pesquisa);
                        end = std::clock();

                        long double diff_pesquisa = 1000.0 * (end - start) / CLOCKS_PER_SEC;

                        std::cout << "3" << std::endl;
                        int counter_comparisons_retira = 0;
                        start = std::clock();
                        avlTree.testRetira(result, datasets[i], &counter_comparisons_retira);
                        end = std::clock();

                        long double diff_retira = 1000.0 * (end - start) / CLOCKS_PER_SEC;

                        {
                            file << algorithms[1] << ";" << datasets_name[i] << ";" 
                                << tam << ";" << diff_insertion << ";" << counter_comparisons_insere<< ";" 
                                << diff_pesquisa << ";" << counter_comparisons_pesquisa<< ";" 
                                << diff_retira << ";" << counter_comparisons_retira<< ";" << "\n";
                        }
                    }

                    std::cout << "RedBlackTree" << std::endl;
                    {
                        int counter_comparisons_insere = 0; // Reset the counter for each tree size
                        RedBlackTree redBlackTree;
                        std::cout << "1" << std::endl;
                        std::clock_t start = std::clock();
                        auto result = redBlackTree.testInsere(datasets[i], &counter_comparisons_insere);
                        std::clock_t end = std::clock();

                        long double diff_insertion = 1000.0 * (end - start) / CLOCKS_PER_SEC;

                        std::cout << "2" << std::endl;
                        int counter_comparisons_pesquisa = 0;
                        start = std::clock();
                        redBlackTree.testPesquisa(result, datasets[i], &counter_comparisons_pesquisa);
                        end = std::clock();

                        long double diff_pesquisa = 1000.0 * (end - start) / CLOCKS_PER_SEC;

                        std::cout << "3" << std::endl;
                        int counter_comparisons_retira = 0;
                        start = std::clock();
                        redBlackTree.testRetira(result, datasets[i], &counter_comparisons_retira);
                        end = std::clock();

                        long double diff_retira = 1000.0 * (end - start) / CLOCKS_PER_SEC;

                        {
                            file << algorithms[2] << ";" << datasets_name[i] << ";" 
                                << tam << ";" << diff_insertion << ";" << counter_comparisons_insere<< ";" 
                                << diff_pesquisa << ";" << counter_comparisons_pesquisa<< ";" 
                                << diff_retira << ";" << counter_comparisons_retira<< ";" << "\n";
                        }
                    }

                    std::cout << "LinearSearch" << std::endl;
                    {
                        int counter_comparisons_insere = 0; // Reset the counter for each tree size
                        LinearSearch linearSearch;
                        std::cout << "1" << std::endl;
                        std::clock_t start = std::clock();
                        auto result = linearSearch.testInsere(datasets[i], &counter_comparisons_insere);
                        std::clock_t end = std::clock();

                        long double diff_insertion = 1000.0 * (end - start) / CLOCKS_PER_SEC;

                        std::cout << "2" << std::endl;
                        int counter_comparisons_pesquisa = 0;
                        start = std::clock();
                        linearSearch.testPesquisa(result, datasets[i], &counter_comparisons_pesquisa);
                        end = std::clock();

                        long double diff_pesquisa = 1000.0 * (end - start) / CLOCKS_PER_SEC;

                        std::cout << "3" << std::endl;
                        int counter_comparisons_retira = 0;
                        start = std::clock();
                        linearSearch.testRetira(result, datasets[i], &counter_comparisons_retira);
                        end = std::clock();

                        long double diff_retira = 1000.0 * (end - start) / CLOCKS_PER_SEC;

                        {
                            file << algorithms[3] << ";" << datasets_name[i] << ";" 
                                << tam << ";" << diff_insertion << ";" << counter_comparisons_insere<< ";" 
                                << diff_pesquisa << ";" << counter_comparisons_pesquisa<< ";" 
                                << diff_retira << ";" << counter_comparisons_retira<< ";" << "\n";
                        }
                    }

                    std::cout << "BinarySearch" << std::endl;
                    {
                        int counter_comparisons_insere = 0; // Reset the counter for each tree size
                        BinarySearch binarySearch;
                        std::cout << "1" << std::endl;
                        std::clock_t start = std::clock();
                        auto result = binarySearch.testInsere(datasets[i], &counter_comparisons_insere);
                        std::clock_t end = std::clock();

                        long double diff_insertion = 1000.0 * (end - start) / CLOCKS_PER_SEC;

                        std::cout << "2" << std::endl;
                        int counter_comparisons_pesquisa = 0;
                        start = std::clock();
                        binarySearch.testPesquisa(result, datasets[i], &counter_comparisons_pesquisa);
                        end = std::clock();

                        long double diff_pesquisa = 1000.0 * (end - start) / CLOCKS_PER_SEC;

                        std::cout << "3" << std::endl;
                        int counter_comparisons_retira = 0;
                        start = std::clock();
                        binarySearch.testRetira(result, datasets[i], &counter_comparisons_retira);
                        end = std::clock();

                        long double diff_retira = 1000.0 * (end - start) / CLOCKS_PER_SEC;

                        {
                            file << algorithms[4] << ";" << datasets_name[i] << ";" 
                                << tam << ";" << diff_insertion << ";" << counter_comparisons_insere<< ";" 
                                << diff_pesquisa << ";" << counter_comparisons_pesquisa<< ";" 
                                << diff_retira << ";" << counter_comparisons_retira<< ";" << "\n";
                        }
                    }

                    std::cout << "BinarySearchTree" << std::endl;
                    {
                        int counter_comparisons_insere = 0; // Reset the counter for each tree size
                        BinarySearchTree binarySearchTree;
                        std::cout << "1" << std::endl;
                        std::clock_t start = std::clock();
                        auto result = binarySearchTree.testInsere(datasets[i], &counter_comparisons_insere);
                        std::clock_t end = std::clock();

                        long double diff_insertion = 1000.0 * (end - start) / CLOCKS_PER_SEC;

                        std::cout << "2" << std::endl;
                        int counter_comparisons_pesquisa = 0;
                        start = std::clock();
                        binarySearchTree.testPesquisa(result, datasets[i], &counter_comparisons_pesquisa);
                        end = std::clock();

                        long double diff_pesquisa = 1000.0 * (end - start) / CLOCKS_PER_SEC;

                        std::cout << "3" << std::endl;
                        int counter_comparisons_retira = 0;
                        start = std::clock();
                        binarySearchTree.testRetira(result, datasets[i], &counter_comparisons_retira);
                        end = std::clock();

                        long double diff_retira = 1000.0 * (end - start) / CLOCKS_PER_SEC;

                        {
                            file << algorithms[5] << ";" << datasets_name[i] << ";" 
                                << tam << ";" << diff_insertion << ";" << counter_comparisons_insere<< ";" 
                                << diff_pesquisa << ";" << counter_comparisons_pesquisa<< ";" 
                                << diff_retira << ";" << counter_comparisons_retira<< ";" << "\n";
                        }
                    }
                }
            }
        }

        file.close();
    }

    return 0;
}
