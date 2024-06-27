#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include "searchAlgorithm.h"

class RedBlackTree : public SearchAlgorithm  {
public:
    RedBlackTree();

    int EhNegro(TArvBin No, int *counter_comparisons);
    int EhRubro(TArvBin No, int *counter_comparisons);
    int AlturaNegra(TArvBin No, int *counter_comparisons);
    int ArvoreARN(TArvBin No, int *counter_comparisons);
    void InverteCor(TArvBin No, int *counter_comparisons);
    void TrocaCores(TArvBin No, int *counter_comparisons);
    void RotacaoDireita(TArvBin *pA, int *counter_comparisons);
    void RotacaoEsquerda(TArvBin *pA, int *counter_comparisons);
    void BalancaDireitaInsere(TArvBin *pA, TArvBin *pB, TArvBin *pC, int *counter_comparisons);
    void BalancaEsquerdaInsere(TArvBin *pA, TArvBin *pB, TArvBin *pC, int *counter_comparisons);
    void BalancaNoInsere(TArvBin *pA, TArvBin *pB, TArvBin *pC, int *counter_comparisons);
    int BalancaEsquerda(TArvBin *pC, int *counter_comparisons);
    int BalancaDireita(TArvBin *pC, int *counter_comparisons);
    void InsereRecursivo(TArvBin *pA, TArvBin *pC, TItem x, int *counter_comparisons);
    void Insere(TArvBin *pRaiz, TItem x, int *counter_comparisons);
    int Sucessor(TArvBin *q, TArvBin *r, int *counter_comparisons);
    int RetiraRecursivo(TArvBin *p, TChave x, int *counter_comparisons);
    void Retira(TArvBin *pRaiz, TChave x, int *counter_comparisons);
    TArvBin* Pesquisa(TArvBin *No, TChave c, int *counter_comparisons);
    
    std::pair<int, std::pair<int, std::pair<int, std::pair<long double, std::pair<long double, long double>>>>> test(std::vector<int> dataset);
    std::variant<TDicionario*, TArvBin> testInsere(std::vector<int> dataset, int *counter_comparisons) override;
    std::variant<TDicionario*, TArvBin> testPesquisa(std::variant<TDicionario*, TArvBin> dicionario, std::vector<int> dataset, int *counter_comparisons) override;
    std::variant<TDicionario*, TArvBin> testRetira(std::variant<TDicionario*, TArvBin> dicionario, std::vector<int> dataset, int *counter_comparisons) override;
};

#endif // REDBLACKTREE_H