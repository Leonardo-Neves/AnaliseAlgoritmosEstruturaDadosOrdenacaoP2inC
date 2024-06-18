#include <variant>

#ifndef AVLTREE_H
#define AVLTREE_H

#include "searchAlgorithm.h"

class AVLTree : public SearchAlgorithm  {
public:
    AVLTree();

    int Altura(TArvBin No, int *counter_comparisons);
    int FB(TArvBin No, int *counter_comparisons);
    int ArvoreAVL(TArvBin No, int *counter_comparisons);
    void LL(TArvBin *pA, int *counter_comparisons);
    void RR(TArvBin *pA, int *counter_comparisons);
    void LR(TArvBin *pA, int *counter_comparisons);
    void RL(TArvBin *pA, int *counter_comparisons);
    int BalancaEsquerda(TArvBin *pNo, int *counter_comparisons);
    int BalancaDireita(TArvBin *pNo, int *counter_comparisons);
    int BalancaNo(TArvBin *pNo, int *counter_comparisons);
    int Insere(TArvBin *pNo, TItem x, int *counter_comparisons);
    int Sucessor(TArvBin *q, TArvBin *r, int *counter_comparisons);
    int Retira(TArvBin *p, TChave c, int *counter_comparisons);
    
    std::variant<TDicionario*, TArvBin*> testInsere(std::vector<int> dataset, int *counter_comparisons) override;
    std::variant<TDicionario*, TArvBin*> testPesquisa(std::variant<TDicionario*, TArvBin*> dicionario, std::vector<int> dataset, int *counter_comparisons) override;
    std::variant<TDicionario*, TArvBin*> testRetira(std::variant<TDicionario*, TArvBin*> dicionario, std::vector<int> dataset, int *counter_comparisons) override;
};

#endif // AVLTREE_H