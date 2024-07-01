#ifndef TREAP_H
#define TREAP_H

#include "searchAlgorithm.h"
#include <string> 
class Treap: public SearchAlgorithm {
public:
    Treap();
    
    void RotacaoDireita(TArvBin *pA);
    void RotacaoEsquerda(TArvBin *pA);
    int Insere(TArvBin *pNo, TItem x, int *counter_comparisons);
    TArvBin* Pesquisa(TArvBin *No, TChave c, int *counter_comparisons);
    int Retira(TArvBin *pNo, TChave c, int *counter_comparisons);
    void printTree(TArvBin arvore) const;
    
    std::variant<TDicionario*, TArvBin> testInsere(std::vector<int> dataset, int *counter_comparisons) override;
    std::variant<TDicionario*, TArvBin> testPesquisa(std::variant<TDicionario*, TArvBin> dicionario, std::vector<int> dataset, int *counter_comparisons) override;
    std::variant<TDicionario*, TArvBin> testRetira(std::variant<TDicionario*, TArvBin> dicionario, std::vector<int> dataset, int *counter_comparisons) override;

private:
    void printTreeRec(TArvBin node, int depth, std::string prefix, bool isLeft) const;
};

#endif // TREAP_H
