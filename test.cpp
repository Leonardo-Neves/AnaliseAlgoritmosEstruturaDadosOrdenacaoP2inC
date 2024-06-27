#include <stdio.h>
#include <stdlib.h> 
#include <iostream>
#include <cstddef>

#include "redBlackTree.h"
#include "datasetGenerator.h"

int main() {

    auto arvore = (TArvBin) malloc(sizeof(TNo));

    // TArvBin arvore;
    DatasetGenerator datasetGenerator;

    std::vector<int> dataset = datasetGenerator.generateRandom(1000000);

    RedBlackTree redblacktree;

    int counter = 0;

    auto result = redblacktree.testInsere(dataset, &counter);

    auto result2 = redblacktree.testPesquisa(result, dataset, &counter);

    auto result3 = redblacktree.testRetira(result, dataset, &counter);

    // auto result = redblacktree.test(dataset);



    return 0;
}