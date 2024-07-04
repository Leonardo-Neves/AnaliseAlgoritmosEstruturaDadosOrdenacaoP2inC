#include "treapTree.h"
#include <iostream>
#include <cstdlib>
#include <climits>

// Construtor da classe Treap
Treap::Treap() {}

// Função para rotação à direita
void Treap::RotacaoDireita(TArvBin *pA) {
    TArvBin aux = (*pA)->Esq;
    (*pA)->Esq = aux->Dir;
    aux->Dir = *pA;
    *pA = aux;
}

// Função para rotação à esquerda
void Treap::RotacaoEsquerda(TArvBin *pA) {
    TArvBin aux = (*pA)->Dir;
    (*pA)->Dir = aux->Esq;
    aux->Esq = *pA;
    *pA = aux;
}

// Função para inserir um novo nó na Treap
int Treap::Insere(TArvBin *pNo, TItem x, int *counter_comparisons) {
    if (*pNo == NULL) {
        (*counter_comparisons)++;

        *pNo = new SNo();
        (*pNo)->Item = x;
        (*pNo)->Esq = NULL;
        (*pNo)->Dir = NULL;
        return 1;
    } else {
        (*counter_comparisons)++;


        if (x.Chave < (*pNo)->Item.Chave) {
            (*counter_comparisons)++;

            Insere(&(*pNo)->Esq, x, counter_comparisons);

            (*counter_comparisons)++;
            if ((*pNo)->Esq->Item.Priority > (*pNo)->Item.Priority) {
                RotacaoDireita(pNo);
            }
        } else {
            (*counter_comparisons)++;

            Insere(&(*pNo)->Dir, x, counter_comparisons);

            (*counter_comparisons)++;
            if ((*pNo)->Dir->Item.Priority > (*pNo)->Item.Priority) {
                RotacaoEsquerda(pNo);
            }
        }
    }
    return 1;
}

// Função para pesquisar um nó na Treap
TArvBin* Treap::Pesquisa(TArvBin *pNo, TChave c, int *counter_comparisons) {
    (*counter_comparisons)++;
    if (*pNo == NULL) {
        return NULL;
    }

    if (c < (*pNo)->Item.Chave) {
        (*counter_comparisons)++;
        return Pesquisa(&(*pNo)->Esq, c, counter_comparisons);
    } else if (c > (*pNo)->Item.Chave) {
        (*counter_comparisons)+=2;
        return Pesquisa(&(*pNo)->Dir, c, counter_comparisons);
    } else {
        (*counter_comparisons)+=2;
        return pNo;
    }
}

// // Função para remover um nó da Treap
// int Treap::Retira(TArvBin *pNo, TChave c, int *counter_comparisons) {
//     if (*pNo == NULL) {
//         return 0;
//     }

//     (*counter_comparisons)++;
//     if (c < (*pNo)->Item.Chave) {
//         return Retira(&(*pNo)->Esq, c, counter_comparisons);
//     } else if (c > (*pNo)->Item.Chave) {
//         return Retira(&(*pNo)->Dir, c, counter_comparisons);
//     } else {
//         // Se encontrou o nó a ser removido
//         (*pNo)->Item.Priority = INT_MIN; // Definir a prioridade como -inf (ou valor mínimo de int)
//         // Rotacionar para mover o nó para uma folha
//         while ((*pNo)->Esq != NULL || (*pNo)->Dir != NULL) {
//             if ((*pNo)->Esq == NULL) {
//                 RotacaoEsquerda(pNo);
//             } else if ((*pNo)->Dir == NULL) {
//                 RotacaoDireita(pNo);
//             } else if ((*pNo)->Esq->Item.Priority > (*pNo)->Dir->Item.Priority) {
//                 RotacaoDireita(pNo);
//             } else {
//                 RotacaoEsquerda(pNo);
//             }

//             if ((*pNo)->Esq != NULL) {
//                 RotacaoDireita(pNo);
//             } else if ((*pNo)->Dir == NULL) {
//                 RotacaoDireita(pNo);
//             } else if ((*pNo)->Esq->Item.Priority > (*pNo)->Dir->Item.Priority) {
//                 RotacaoDireita(pNo);
//             } else {
//                 RotacaoEsquerda(pNo);
//             }
//         }
//         // Remover o nó folha
//         TArvBin temp = *pNo;
//         *pNo = NULL;
//         delete temp;
//         return 1;
//     }
// }
// Função para remover um nó da Treap
int Treap::Retira(TArvBin *pNo, TChave c, int *counter_comparisons) {

    (*counter_comparisons)++;
    if (*pNo == NULL) {
        return 0; // Nó não encontrado
    }

    
    if (c < (*pNo)->Item.Chave) {
        (*counter_comparisons)++;
        return Retira(&(*pNo)->Esq, c, counter_comparisons);
    } else if (c > (*pNo)->Item.Chave) {
        (*counter_comparisons)+= 2;
        return Retira(&(*pNo)->Dir, c, counter_comparisons);
    } else {
        (*counter_comparisons)+= 2;

        // Nó encontrado para remoção

        // Caso 1: Nó é uma folha (sem filhos)
        if ((*pNo)->Esq == NULL && (*pNo)->Dir == NULL) {
            (*counter_comparisons)++;

            TArvBin temp = *pNo;
            *pNo = NULL;
            delete temp;
            return 1;
        }
        // Caso 2: Nó tem apenas um filho
        else if ((*pNo)->Esq == NULL) {
            (*counter_comparisons) += 2;

            TArvBin temp = *pNo;
            *pNo = (*pNo)->Dir;
            delete temp;
            return 1;
        } else if ((*pNo)->Dir == NULL) {
            (*counter_comparisons) += 3;

            TArvBin temp = *pNo;
            *pNo = (*pNo)->Esq;
            delete temp;
            return 1;
        }
        // Caso 3: Nó tem dois filhos
        else {
            (*counter_comparisons) += 3;

            // // Encontrar o nó com a maior prioridade na subárvore esquerda
            // TArvBin maxLeft = (*pNo)->Esq;
            // while (maxLeft->Dir != NULL) {
            //     maxLeft = maxLeft->Dir;
            // }

            // // Trocar os valores chave e prioridade com o nó com maior prioridade na subárvore esquerda
            // std::swap((*pNo)->Item.Chave, maxLeft->Item.Chave);
            // std::swap((*pNo)->Item.Priority, maxLeft->Item.Priority);

            // // Chamar recursivamente Retira para remover o nó com a chave originalmente procurada
            // return Retira(&(*pNo)->Esq, c, counter_comparisons);

            
            // If key is at root and both left and right are not NULL
            if ((*pNo)->Esq->Item.Priority < (*pNo)->Dir->Item.Priority ){
                (*counter_comparisons)++;

                RotacaoEsquerda(pNo);
                return Retira(&(*pNo)->Esq, c, counter_comparisons);
            }
            else {
                (*counter_comparisons)++;
                
                RotacaoDireita(pNo);
                return Retira(&(*pNo)->Dir, c, counter_comparisons);
            }
    // else if (root->left->priority < root->right->priority)
    // {
    //     root = leftRotate(root);
    //     root->left = deleteNode(root->left, key);
    // }
    // else
    // {
    //     root = rightRotate(root);
    //     root->right = deleteNode(root->right, key);
    // }
 
    // return root;
        }
    }
}

// // Função para imprimir a Treap
// void Treap::printTreeRec(TArvBin node, int depth) const {
//     if (node == NULL) {
//         return;
//     }
//     printTreeRec(node->Dir, depth + 1);
//     for (int i = 0; i < depth; ++i) {
//         std::cout << "    ";
//     }
//     std::cout << "(" << node->Item.Chave << ", " << node->Item.Priority << ")" << std::endl;
//     printTreeRec(node->Esq, depth + 1);
// }

// void Treap::printTree(TArvBin arvore) const {
//     printTreeRec(arvore, 0);
// }

// Função para imprimir a Treap de forma hierárquica
void Treap::printTreeRec(TArvBin node, int depth, std::string prefix, bool isLeft) const {
    if (node == NULL) {
        return;
    }

    // Imprime o nó atual com a devida indentação
    std::cout << prefix;
    if (isLeft) {
        std::cout << "Filho à esquerda: ";
    } else {
        std::cout << "Filho à direita: ";
    }
    std::cout << "(" << node->Item.Chave << ", " << node->Item.Priority << ")" << std::endl;

    // Chamadas recursivas para os filhos à esquerda e à direita
    printTreeRec(node->Esq, depth + 1, prefix + "        ", true);
    printTreeRec(node->Dir, depth + 1, prefix + "        ", false);
}

// Função wrapper para imprimir a Treap
void Treap::printTree(TArvBin arvore) const {
    std::cout << "Nó raiz: (" << arvore->Item.Chave << ", " << arvore->Item.Priority << ")" << std::endl;
    printTreeRec(arvore->Esq, 1, "    ", true);
    printTreeRec(arvore->Dir, 1, "    ", false);
}


// Funções de teste (implementação padrão, ajuste conforme necessário)
std::variant<TDicionario*, TArvBin> Treap::testInsere(std::vector<int> dataset, int *counter_comparisons) {
    TArvBin arvore = NULL;
    long long sum = 0;

    for (int i = 0; i < dataset.size(); ++i) {
        TItem item;
        item.Chave = dataset[i];
        item.Priority = rand() % dataset.size(); // Prioridade aleatória

        int counter_comparisons_insertion = 0;
        Insere(&arvore, item, &counter_comparisons_insertion);
        sum += counter_comparisons_insertion;
    }

    (*counter_comparisons) = sum / dataset.size();
    return arvore;
}

std::variant<TDicionario*, TArvBin> Treap::testPesquisa(std::variant<TDicionario*, TArvBin> dicionario, std::vector<int> dataset, int *counter_comparisons) {
    if (std::holds_alternative<TArvBin>(dicionario)) {
        TArvBin dic_ptr = std::get<TArvBin>(dicionario);
        if (dic_ptr == NULL) {
            return dicionario;
        }

        long long sum = 0;
        for (int i = 0; i < dataset.size(); ++i) {
            int counter_comparisons_pesquisa = 0;
            TChave chave = dataset[i];
            Pesquisa(&dic_ptr, chave, &counter_comparisons_pesquisa);
            sum += counter_comparisons_pesquisa;
        }

        (*counter_comparisons) = sum / dataset.size();
    }
    return dicionario;
}

std::variant<TDicionario*, TArvBin> Treap::testRetira(std::variant<TDicionario*, TArvBin> dicionario, std::vector<int> dataset, int *counter_comparisons) {
    if (std::holds_alternative<TArvBin>(dicionario)) {
        TArvBin dic_ptr = std::get<TArvBin>(dicionario);
        long long sum = 0;

        for (int i = 0; i < dataset.size(); ++i) {
            int counter_comparisons_retira = 0;
            TChave chave = dataset[i];
            Retira(&dic_ptr, chave, &counter_comparisons_retira);
            sum += counter_comparisons_retira;
        }

        (*counter_comparisons) = sum / dataset.size();
    }
    return dicionario;
}
