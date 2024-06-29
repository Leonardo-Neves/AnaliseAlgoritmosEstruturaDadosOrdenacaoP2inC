#ifndef TREAPTREE_H
#define TREAPTREE_H

#include "searchAlgorithm.h"

class TreapTree : public SearchAlgorithm  {
public:
    TreapTree();

    int Retira(TArvBin *p, TChave c, int *counter_comparisons);
    
    std::variant<TDicionario*, TArvBin> testInsere(std::vector<int> dataset, int *counter_comparisons) override;
    std::variant<TDicionario*, TArvBin> testPesquisa(std::variant<TDicionario*, TArvBin> dicionario, std::vector<int> dataset, int *counter_comparisons) override;
    std::variant<TDicionario*, TArvBin> testRetira(std::variant<TDicionario*, TArvBin> dicionario, std::vector<int> dataset, int *counter_comparisons) override;
};

#endif // TREAPTREE_H