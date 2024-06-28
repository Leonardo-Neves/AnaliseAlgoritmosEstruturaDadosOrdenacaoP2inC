#ifndef BINARYSEARCH_H
#define BINARYSEARCH_H

#include "searchAlgorithm.h"

class BinarySearch : public SearchAlgorithm  {
public:
    BinarySearch();

    TDicionario *TDicionario_Inicia(int n, int *counter_comparisons);
    TApontador TDicionario_Binaria(TDicionario *D, TApontador esq, TApontador dir, TChave c, int *counter_comparisons);
    TApontador TDicionario_Pesquisa(TDicionario *D, TChave c, int *counter_comparisons);
    int TDicionario_Insere(TDicionario *D, TItem x, int *counter_comparisons);
    int TDicionario_Retira(TDicionario *D, TChave c, int *counter_comparisons);
    
    std::variant<TDicionario*, TArvBin> testInsere(std::vector<int> dataset, int *counter_comparisons) override;
    std::variant<TDicionario*, TArvBin> testPesquisa(std::variant<TDicionario*, TArvBin> dicionario, std::vector<int> dataset, int *counter_comparisons) override;
    std::variant<TDicionario*, TArvBin> testRetira(std::variant<TDicionario*, TArvBin> dicionario, std::vector<int> dataset, int *counter_comparisons) override;
};

#endif // BINARYSEARCH_H