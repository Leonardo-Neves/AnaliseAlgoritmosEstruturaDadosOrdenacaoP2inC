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

std::mutex mtx;

// Este método é responsável em executar um algoritmo, medir o tempo de CPU time e gravar os resultados de movimentações, comparações e tempo de execução em um arquivo CSV
void runExperiment(int iteration, const std::string& functionName, SearchAlgorithm* method, const std::vector<int>& dataset, const std::string& datasetName, std::ofstream& file) {

    // Executando o método insere, mensurando o tempo de execução e contando comparações
    int counter_comparisons_insere = 0;
    std::clock_t start = std::clock();
    auto result_testInsere = method->testInsere(dataset, &counter_comparisons_insere);
    std::clock_t end = std::clock();
    long double diff_insertion = 1000.0 * (end - start) / CLOCKS_PER_SEC;

    // Executando o método pesquisa, mensurando o tempo de execução e contando comparações
    int counter_comparisons_pesquisa = 0;
    start = std::clock();
    auto result_testPesquisa = method->testPesquisa(result_testInsere, dataset, &counter_comparisons_pesquisa);
    end = std::clock();
    long double diff_pesquisa = 1000.0 * (end - start) / CLOCKS_PER_SEC;

    // Executando o método retira, mensurando o tempo de execução e contando comparações
    int counter_comparisons_retira = 0;
    start = std::clock();
    auto result_testRetira = method->testRetira(result_testInsere, dataset, &counter_comparisons_retira);
    end = std::clock();
    long double diff_retira = 1000.0 * (end - start) / CLOCKS_PER_SEC;

    // Registrando resultados no arquivo CSV
    {
        std::lock_guard<std::mutex> lock(mtx);
        file << iteration + 1 << ";" << functionName << ";" << datasetName << ";" 
             << dataset.size() << ";" << diff_insertion << ";" << counter_comparisons_insere<< ";" 
             << diff_pesquisa << ";" << counter_comparisons_pesquisa<< ";" 
             << diff_retira << ";" << counter_comparisons_retira<< ";" << "\n";
    }
}

// Este método é responsável por executar um interação do código, o que envolve executar um conjunto de dados sobre uma série de métodos utilizando computação paralela
void runInteration(std::map<std::string, SearchAlgorithm*> methods, int iteration, std::vector<std::vector<std::vector<int>>> datasets, std::vector<std::string> datasets_name, std::string output_path, std::string posfixo = "") {

    // Interando sobre cada método
    for (auto function = methods.begin(); function != methods.end(); ++function) {

        // Obtendo tempo atual
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::tm* now_tm = std::localtime(&now_time);

        // Criando arquivo CSV de saída
        char time_str[100];
        std::strftime(time_str, sizeof(time_str), "%Y-%m-%d_%H-%M-%S", now_tm);
        std::string filename = output_path + "/output_" + function->first + "_" + std::string(time_str) + "_" + std::to_string(iteration) + "_" + posfixo + ".csv";
        std::ofstream file(filename);

        // Criando threads para executar os algoritmos em paralelo
        if (file.is_open()) {
            file << "Iteration;Algorithm;DatasetName;DatasetSize;Time Insere;Counter Comparisons Insere;Time Pesquisa;Counter Comparisons Pesquisa;Time Retira;Counter Comparisons Retira\n";

            for (int i = 0; i < datasets.size(); ++i) {

                std::vector<std::thread> threads;

                


                for (int j = 0; j < datasets[i].size(); ++j) {
                    runExperiment(iteration, function->first, std::move(function->second), datasets[i][j], datasets_name[i], std::ref(file));
                    // threads.emplace_back(runExperiment, iteration, function->first, std::move(function->second), datasets[i][j], datasets_name[i], std::ref(file));
                }

                // for (int i = 0; i < threads.size(); ++i) {
                //     threads[i].join();
                // }
            }
        }

        file.close();
    }
}

// Este método é responsável por gerar um conjunto de dados baseado em um vetor de entrada, que em cada posição do vetor, um número indicando o comprimento do vetor que será gerado
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

int main()
{
    // Configurações Iniciais
    int NUMBER_INTERATIONS = 1; // Número de interações que o código vai executar
    std::string output_path = "/home/leo/AAED_P2/output"; // Caminho de saída do resultado

    // Configuração dos métodos que será utilizado em cada interação
    std::map<std::string, SearchAlgorithm*> methods;
    // methods["linearSearch"] = new LinearSearch();
    // methods["binarySearch"] = new BinarySearch();
    // methods["binarySearchTree"] = new BinarySearchTree();
    methods["avlTree"] = new AVLTree();
    // methods["redBlackTree"] = new RedBlackTree();

    // Nome dos conjuntos de dados, informação que será utilizada posteriormente como identificador no arquivo CSV de resultado
    std::vector<std::string> datasets_name = {
        "Ordered",
        "OrderedInverse",
        "AlmostOrdered",
        "Random"
    };

    // Executando as interações
    for (int i = 0; i < NUMBER_INTERATIONS; ++i) {

        // Gerando um dataset para está interação, executando primeiro para vetores do tamanho, 10, 100, 1.000 e 10.000
        std::vector<int> lengthLists1 = {10, 100, 1000, 10000};
        std::vector<std::vector<std::vector<int>>> datasets1 = generateDataset(lengthLists1);

        // Executando a primeira parte da interação
        runInteration(methods, i, datasets1, datasets_name, output_path, "1");

        // // Gerando um dataset para está interação, executando primeiro para vetores do tamanho de 100.000
        // std::vector<int> lengthLists2 = {100000};
        // std::vector<std::vector<std::vector<int>>> datasets2 = generateDataset(lengthLists2);

        // // Executando a segunda parte da interação
        // runInteration(methods, i, datasets2, datasets_name, output_path, "2");
    }

    return 0;
}