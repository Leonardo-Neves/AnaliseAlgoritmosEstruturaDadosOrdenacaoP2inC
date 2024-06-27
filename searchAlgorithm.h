#include <vector>
#include <variant>

#ifndef SEARCHALGORITHM_H
#define SEARCHALGORITHM_H

typedef int TChave;

typedef struct {
    TChave Chave;
} TItem;

typedef int TApontador;

typedef struct SNo *TArvBin;

typedef struct SNo {
    TItem Item;
    TArvBin Esq, Dir;
    int fb;
    int cor;
} TNo;

typedef struct {
    TItem *Item;
    TArvBin Raiz;
    int n, max;
} TDicionario;

class SearchAlgorithm {
public:
    virtual ~SearchAlgorithm() {} 
    virtual std::variant<TDicionario*, TArvBin> testInsere(std::vector<int> dataset, int *counter_comparisons) = 0;
    virtual std::variant<TDicionario*, TArvBin> testPesquisa(std::variant<TDicionario*, TArvBin> dicionario, std::vector<int> dataset, int *counter_comparisons) = 0;
    virtual std::variant<TDicionario*, TArvBin> testRetira(std::variant<TDicionario*, TArvBin> dicionario, std::vector<int> dataset, int *counter_comparisons) = 0;
};

#endif // SEARCHALGORITHM_H