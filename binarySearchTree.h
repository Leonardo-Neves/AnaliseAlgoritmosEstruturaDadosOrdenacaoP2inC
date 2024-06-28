#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "searchAlgorithm.h"

class BinarySearchTree : public SearchAlgorithm  {
public:
    BinarySearchTree();

    typedef TArvBin TApontador;

    TDicionario *TDicionario_Inicia(int *counter_comparisons);
    TArvBin Pesquisa(TArvBin No, TChave c, int *counter_comparisons);
    int Insere(TArvBin *pNo, TItem x, int *counter_comparisons);
    void Predecessor(TArvBin *q, TArvBin *r, int *counter_comparisons);
    void Sucessor(TArvBin *q, TArvBin *r, int *counter_comparisons);
    int Retira(TArvBin *p, TChave c, int *counter_comparisons);
    void TDicionario_Pesquisa(TDicionario *D, TChave c, int *counter_comparisons);
    int TDicionario_Insere(TDicionario *D, TItem x, int *counter_comparisons);
    int TDicionario_Retira(TDicionario *D, TChave c, int *counter_comparisons);

    std::variant<TDicionario*, TArvBin> testInsere(std::vector<int> dataset, int *counter_comparisons) override;
    std::variant<TDicionario*, TArvBin> testPesquisa(std::variant<TDicionario*, TArvBin> dicionario, std::vector<int> dataset, int *counter_comparisons) override;
    std::variant<TDicionario*, TArvBin> testRetira(std::variant<TDicionario*, TArvBin> dicionario, std::vector<int> dataset, int *counter_comparisons) override;
};

#endif // BINARYSEARCHTREE_H