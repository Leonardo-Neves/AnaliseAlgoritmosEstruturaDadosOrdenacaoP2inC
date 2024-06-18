#include <stdio.h>
#include <stdlib.h> 
#include <iostream>
#define NIL -1

#include "datasetGenerator.h"

typedef int TChave;

typedef struct {
    TChave Chave;
} TItem;

typedef int TApontador;

typedef struct {
    TItem *Item;
    int n, max;
} TDicionario;

TDicionario *TDicionario_Inicia()
{
    TDicionario *D;
    D = (TDicionario *) malloc(sizeof(TDicionario));
    D->n = 0;
    D->max = 10;
    D->Item = (TItem *) malloc(D->max * sizeof(TItem));
    return D;
}

TApontador TDicionario_Binaria(TDicionario *D, TApontador esq, TApontador dir, TChave c)
{
    TApontador meio;
    meio = (esq + dir) / 2;
    if (esq > dir)
        return NIL;
    else if (c > D->Item[meio].Chave)
        return TDicionario_Binaria(D, meio+1, dir, c);
    else if (c < D->Item[meio].Chave)
        return TDicionario_Binaria(D, esq, meio-1, c);
    else
        return meio;
}

TApontador TDicionario_Pesquisa(TDicionario *D, TChave c)
{
    return TDicionario_Binaria(D, 0, D->n-1, c);
}

TApontador TDicionario_Pesquisa(TDicionario *D, TChave c)
{
    TApontador meio, esq, dir;
    esq = 0;
    dir = D->n-1;
    while (esq <= dir) {
        meio = (esq + dir) / 2;
        if (c > D->Item[meio].Chave)
            esq = meio + 1;
        else if (c < D->Item[meio].Chave)
            dir = meio - 1;
        else
            return meio;
    }
    return NIL;
}

int TDicionario_Insere(TDicionario *D, TItem x)
{
    TApontador i;
    if (TDicionario_Pesquisa(D, x.Chave) != NIL)
        return 0;
    if (D->n == D->max) {
        D->max *= 2;
        D->Item = (TItem *) realloc(D->Item, D->max * sizeof(TItem));
    }
    i = D->n - 1;
    while ((i >= 0) && (x.Chave < D->Item[i].Chave)) {
        D->Item[i + 1] = D->Item[i];
        i--;
    }
    D->Item[i + 1] = x;
    D->n++;
    return 1;
}

int TDicionario_Retira(TDicionario *D, TChave c)
{
    TApontador i;
    i = TDicionario_Pesquisa(D, c);
    if (i == NIL)
        return 0;
    while (i < D->n - 1) {
        D->Item[i] = D->Item[i + 1];
        i++;
    }
    D->n--;
    if (4 * D->n == D->max) {
        D->max /= 2;
        D->Item = (TItem *) realloc(D->Item, D->max * sizeof(TItem));
    }
    return 1;
}

int main() {
    int n = 10;

    auto dicionario = TDicionario_Inicia(n);

    DatasetGenerator datasetGenerator;

    std::vector<int> dataset = datasetGenerator.generateOrderedInverse(n);

    for (int i = 0; i < n; ++i) {
        TItem item;
        item.Chave = dataset[i];

        TDicionario_Insere(dicionario, item);
    }

    TChave chave = 8;

    std::cout << TDicionario_Pesquisa(dicionario, chave) << " ";

    return 0;
}