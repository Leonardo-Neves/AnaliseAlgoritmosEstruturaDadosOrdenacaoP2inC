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
#include <queue>
#include <condition_variable>

#include "searchAlgorithm.h"
#include "linearSearch.h"
#include "binarySearch.h"
#include "binarySearchTree.h"
#include "AVLTree.h"
#include "redBlackTree.h"
#include "datasetGenerator.h"
#include "treapTree.h"

using namespace std;

// Function to get current date and time as a string in dd/mm/yyyy_hh:mm:ss format
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

// Mutex for file operations
std::mutex file_mutex;

struct Task {
    std::string algorithm_name;
    int iteration;
    std::string dataset_name;
    int tam;
    std::vector<int> dataset;
};

std::queue<Task> task_queue;
std::mutex queue_mutex;
std::condition_variable queue_cv;

void runAlgorithm(const std::string& filename) {
    while (true) {
        Task task;
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            queue_cv.wait(lock, []{ return !task_queue.empty(); });
            task = task_queue.front();
            task_queue.pop();
        }

        std::clock_t start, end;
        long double diff_insertion, diff_pesquisa, diff_retira;
        int counter_comparisons_insere = 0, counter_comparisons_pesquisa = 0, counter_comparisons_retira = 0;
        std::vector<int> result;

        if (task.algorithm_name == "TreapTree") {
            Treap treap;
            start = std::clock();
            result = treap.testInsere(task.dataset, &counter_comparisons_insere);
            end = std::clock();
            diff_insertion = 1000.0 * (end - start) / CLOCKS_PER_SEC;

            start = std::clock();
            treap.testPesquisa(result, task.dataset, &counter_comparisons_pesquisa);
            end = std::clock();
            diff_pesquisa = 1000.0 * (end - start) / CLOCKS_PER_SEC;

            start = std::clock();
            treap.testRetira(result, task.dataset, &counter_comparisons_retira);
            end = std::clock();
            diff_retira = 1000.0 * (end - start) / CLOCKS_PER_SEC;
        } else if (task.algorithm_name == "AVLTree") {
            AVLTree avlTree;
            start = std::clock();
            result = avlTree.testInsere(task.dataset, &counter_comparisons_insere);
            end = std::clock();
            diff_insertion = 1000.0 * (end - start) / CLOCKS_PER_SEC;

            start = std::clock();
            avlTree.testPesquisa(result, task.dataset, &counter_comparisons_pesquisa);
            end = std::clock();
            diff_pesquisa = 1000.0 * (end - start) / CLOCKS_PER_SEC;

            start = std::clock();
            avlTree.testRetira(result, task.dataset, &counter_comparisons_retira);
            end = std::clock();
            diff_retira = 1000.0 * (end - start) / CLOCKS_PER_SEC;
        } else if (task.algorithm_name == "RedBlackTree") {
            RedBlackTree redBlackTree;
            start = std::clock();
            result = redBlackTree.testInsere(task.dataset, &counter_comparisons_insere);
            end = std::clock();
            diff_insertion = 1000.0 * (end - start) / CLOCKS_PER_SEC;

            start = std::clock();
            redBlackTree.testPesquisa(result, task.dataset, &counter_comparisons_pesquisa);
            end = std::clock();
            diff_pesquisa = 1000.0 * (end - start) / CLOCKS_PER_SEC;

            start = std::clock();
            redBlackTree.testRetira(result, task.dataset, &counter_comparisons_retira);
            end = std::clock();
            diff_retira = 1000.0 * (end - start) / CLOCKS_PER_SEC;
        } else if (task.algorithm_name == "LinearSearch") {
            LinearSearch linearSearch;
            start = std::clock();
            result = linearSearch.testInsere(task.dataset, &counter_comparisons_insere);
            end = std::clock();
            diff_insertion = 1000.0 * (end - start) / CLOCKS_PER_SEC;

            start = std::clock();
            linearSearch.testPesquisa(result, task.dataset, &counter_comparisons_pesquisa);
            end = std::clock();
            diff_pesquisa = 1000.0 * (end - start) / CLOCKS_PER_SEC;

            start = std::clock();
            linearSearch.testRetira(result, task.dataset, &counter_comparisons_retira);
            end = std::clock();
            diff_retira = 1000.0 * (end - start) / CLOCKS_PER_SEC;
        } else if (task.algorithm_name == "BinarySearch") {
            BinarySearch binarySearch;
            start = std::clock();
            result = binarySearch.testInsere(task.dataset, &counter_comparisons_insere);
            end = std::clock();
            diff_insertion = 1000.0 * (end - start) / CLOCKS_PER_SEC;

            start = std::clock();
            binarySearch.testPesquisa(result, task.dataset, &counter_comparisons_pesquisa);
            end = std::clock();
            diff_pesquisa = 1000.0 * (end - start) / CLOCKS_PER_SEC;

            start = std::clock();
            binarySearch.testRetira(result, task.dataset, &counter_comparisons_retira);
            end = std::clock();
            diff_retira = 1000.0 * (end - start) / CLOCKS_PER_SEC;
        } else if (task.algorithm_name == "BinarySearchTree") {
            BinarySearchTree binarySearchTree;
            start = std::clock();
            result = binarySearchTree.testInsere(task.dataset, &counter_comparisons_insere);
            end = std::clock();
            diff_insertion = 1000.0 * (end - start) / CLOCKS_PER_SEC;

            start = std::clock();
            binarySearchTree.testPesquisa(result, task.dataset, &counter_comparisons_pesquisa);
            end = std::clock();
            diff_pesquisa = 1000.0 * (end - start) / CLOCKS_PER_SEC;

            start = std::clock();
            binarySearchTree.testRetira(result, task.dataset, &counter_comparisons_retira);
            end = std::clock();
            diff_retira = 1000.0 * (end - start) / CLOCKS_PER_SEC;
        }

        // Lock the mutex for file operations
        {
            std::lock_guard<std::mutex> lock(file_mutex);
            std::ofstream file(filename, std::ofstream::app);
            file << to_string(task.iteration + 1) << ";" << task.algorithm_name << ";" << task.dataset_name << ";" << task.tam << ";" << diff_insertion << ";" << counter_comparisons_insere << ";" << diff_pesquisa << ";" << counter_comparisons_pesquisa << ";" << diff_retira << ";" << counter_comparisons_retira << "\n";
            file.close();
        }
    }
}

int main() {
    DatasetGenerator datasetGenerator;

    std::vector<int> tamanhos = {10, 100, 1000, 10000, 100000, 1000000};
    int NUMBER_ITERATIONS = 10;
    std::vector<std::string> datasets_name = {"Ordered", "OrderedInverse", "AlmostOrdered", "Random"};
    std::vector<std::string> algorithms = {"TreapTree", "AVLTree", "RedBlackTree", "BinarySearchTree", "BinarySearch", "LinearSearch"};
    std::vector<std::vector<int>> datasets;

    std::string filename = "output_" + getCurrentDateTime() + ".csv";
    {
        std::ofstream file(filename);
        file << "Iteration;Algorithm;DatasetName;DatasetSize;Time Insere;Counter Comparisons Insere;Time Pesquisa;Counter Comparisons Pesquisa;Time Retira;Counter Comparisons Retira\n";
        file.close();
    }

    const int num_threads = std::thread::hardware_concurrency();
    std::vector<std::thread> thread_pool;
    for (int i = 0; i < num_threads; ++i) {
        thread_pool.emplace_back(runAlgorithm, filename);
    }

    for (int j = 0; j < NUMBER_ITERATIONS; ++j) {
        for (int tam : tamanhos) {
            datasets.clear();
            datasets.push_back(datasetGenerator.generateOrdered(tam));
            datasets.push_back(datasetGenerator.generateOrderedInverse(tam));
            datasets.push_back(datasetGenerator.generateAlmostOrdered(tam));
            datasets.push_back(datasetGenerator.generateRandom(tam));

            for (int i = 0; i < datasets.size(); ++i) {
                for (const std::string& algorithm : algorithms) {
                    Task task = {algorithm, j, datasets_name[i], tam, datasets[i]};
                    {
                        std::lock_guard<std::mutex> lock(queue_mutex);
                        task_queue.push(task);
                    }
                    queue_cv.notify_one();
                }
            }
        }
    }

    // Wait for all threads to finish
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        queue_cv.wait(lock, [] { return task_queue.empty(); });
    }

    for (auto& thread : thread_pool) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    return 0;
}
