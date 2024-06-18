#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>
#include <unordered_set>

#include "datasetGenerator.h"

DatasetGenerator::DatasetGenerator() {}

// Método responsável por gerar um vetor de dados ordenados
std::vector<int> DatasetGenerator::generateOrdered(int length) {
    
    std::vector<int> orderedList(length);
    std::iota(orderedList.begin(), orderedList.end(), 1);

    return orderedList;
}

// Método responsável por gerar um vetor de dados ordenados inversamente
std::vector<int> DatasetGenerator::generateOrderedInverse(int length) {
    
    std::vector<int> orderedInverseList(length);
    std::iota(orderedInverseList.begin(), orderedInverseList.end(), 1);
    std::reverse(orderedInverseList.begin(), orderedInverseList.end());
      
    return orderedInverseList;
}

// Método responsável por gerar um vetor de dados ordenados parcialmente
std::vector<int> DatasetGenerator::generateAlmostOrdered(int length) {
    
    std::random_device rd;
    std::mt19937 g(rd());
    
    std::vector<int> half(length / 2);
    std::iota(half.begin(), half.end(), 1);
    std::vector<int> remaining(length - half.size());
    std::iota(remaining.begin(), remaining.end(), half.size() + 1);
    std::shuffle(remaining.begin(), remaining.end(), g);
    
    // Verifica números únicos
    std::unordered_set<int> uniqueNumbers(half.begin(), half.end());
    for (int num : remaining) {
        while (uniqueNumbers.count(num) > 0) {
            num = std::uniform_int_distribution<>(half.size() + 1, length)(g);
        }
        uniqueNumbers.insert(num);
        half.push_back(num);
    }
        
    return half;
}

// Método responsável por gerar um vetor de dados ordenados randômicamente
std::vector<int> DatasetGenerator::generateRandom(int length) {
    
    std::random_device rd;
    std::mt19937 g(rd());

    std::vector<int> randomList(length);
    
    std::unordered_set<int> uniqueNumbers;
    for (int i = 0; i < length; ++i) {
        int num = std::uniform_int_distribution<>(1, length * 2)(g);
        while (uniqueNumbers.count(num) > 0) {
            num = std::uniform_int_distribution<>(1, length * 2)(g);
        }
        randomList[i] = num;
        uniqueNumbers.insert(num);
    }
    
    return randomList;
}

// Método responsável por gerar um vetor de dados ordenados randômicamente com dados repetidos
std::vector<int> DatasetGenerator::generateRandomWithRepeats(int length) {
    std::vector<int> result;

    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<int> dis(0, length);

    for (size_t i = 0; i < length; ++i) {
        result.push_back(dis(gen));
    }

    return result;
}