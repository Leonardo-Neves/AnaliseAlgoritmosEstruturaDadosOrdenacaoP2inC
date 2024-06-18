#include <stdio.h>
#include <stdlib.h> 
#include <iostream>
#define NIL 0

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

TDicionario *TDicionario_Inicia(int n)
{
    TDicionario *D;
    D = (TDicionario *) malloc(sizeof(TDicionario));
    D->n = 1;
    D->max = n;
    D->Item = (TItem *) malloc(D->max * sizeof(TItem));
    return D;
}

TApontador TDicionario_Pesquisa(TDicionario *D, TChave c)
{
    TApontador i;
    for (i = 0; i < D->n; i++)
        if (D->Item[i].Chave == c)
            return i;
    return NIL;
}

int TDicionario_Insere(TDicionario *D, TItem x)
{
    if (TDicionario_Pesquisa(D, x.Chave) != NIL)
        return 0;
    if (D->n == D->max) {
        D->max *= 2;
        D->Item = (TItem *) realloc(D->Item, D->max * sizeof(TItem));
    }
    D->Item[D->n++] = x;
    return 1;
}

int TDicionario_Retira(TDicionario *D, TChave c)
{
    TApontador i;
    i = TDicionario_Pesquisa(D, c);
    if (i == NIL)
        return 0;
    D->Item[i] = D->Item[--D->n];
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