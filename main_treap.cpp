// #include <iostream>
// #include <vector>
// #include <cstdlib>
// #include <ctime>
// #include "treapTree.h"

// int main() {
//     Treap treap;
//     TArvBin arvore = NULL;
//     int counter_comparisons = 0;

//     std::srand(std::time(0)); // Inicializa o gerador de números aleatórios

//     // Inserir alguns nós
//     std::vector<int> keys = {5, 2, 8, 6, 3, 7, 1, 4};
//     for (int key : keys) {
//         TItem item;
//         item.Chave = key;
//         item.Priority = rand() % 100; // Prioridade aleatória
//         treap.Insere(&arvore, item, &counter_comparisons);
//         std::cout << "Elemento " << key << " inserido com " << counter_comparisons << " comparações." << std::endl;
//         treap.printTree(arvore);
//     }

//     // Imprimir a Treap após inserção
//     std::cout << "Treap após inserções:" << std::endl;
//     treap.printTree(arvore);
//     std::cout << "REMOÇÃO:" << std::endl;
//     // Remover alguns nós
//     keys = {4, 10, 5};
//     for (int key : keys) {
//         if (treap.Retira(&arvore, key, &counter_comparisons)) {
//             std::cout << "Elemento " << key << " removido com " << counter_comparisons << " comparações." << std::endl;
//         } else {
//             std::cout << "Elemento " << key << " não encontrado." << std::endl;
//         }
//     }

//     // Imprimir a Treap após remoções
//     std::cout << "Treap após remoções:" << std::endl;
//     treap.printTree(arvore);

//     return 0;
// }


#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "treapTree.h" 

int main() {
    Treap treap; // Instância da classe Treap
    TArvBin arvore = NULL; // Árvore inicialmente vazia
    int counter_comparisons = 0; // Contador de comparações

    std::srand(std::time(0)); // Inicializa o gerador de números aleatórios

    // Inserir alguns nós
    std::vector<int> keys = {5, 2, 8, 6, 3, 7, 1, 4};
    for (int key : keys) {
        TItem item;
        item.Chave = key;
        item.Priority = rand() % 100; // Prioridade aleatória
        treap.Insere(&arvore, item, &counter_comparisons); // Inserção na Treap
        std::cout << "Elemento " << key << " inserido com " << counter_comparisons << " comparações." << std::endl;
        treap.printTree(arvore); // Imprime a árvore após cada inserção
    }

    // Imprimir a Treap após inserção
    std::cout << "Treap após inserções:" << std::endl;
    treap.printTree(arvore);

    // Testar operação de remoção
    std::cout << "REMOÇÃO:" << std::endl;
    keys = {4, 10, 5};
    for (int key : keys) {
        if (treap.Retira(&arvore, key, &counter_comparisons)) {
            std::cout << "Elemento " << key << " removido com " << counter_comparisons << " comparações." << std::endl;
        } else {
            std::cout << "Elemento " << key << " não encontrado." << std::endl;
        }
    }

    // Imprimir a Treap após remoções
    std::cout << "Treap após remoções:" << std::endl;
    treap.printTree(arvore);

    // Testar operação de pesquisa
    std::cout << "PESQUISA:" << std::endl;
    keys = {2, 7, 10};
    for (int key : keys) {
        counter_comparisons = 0;
        if (treap.Pesquisa(&arvore, key, &counter_comparisons)) {
            std::cout << "Elemento " << key << " encontrado com " << counter_comparisons << " comparações." << std::endl;
        } else {
            std::cout << "Elemento " << key << " não encontrado." << std::endl;
        }
    }

    return 0;
}
