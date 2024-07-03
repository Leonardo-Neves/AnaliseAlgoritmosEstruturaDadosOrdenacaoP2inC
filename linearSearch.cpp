#include <stdio.h>
#include <stdlib.h> 
#include <iostream>
#include <typeinfo>
#define NIL 0

#include "linearSearch.h"

// typedef int TChave;

// typedef struct {
//     TChave Chave;
// } TItem;

// typedef int TApontador;

// typedef struct {
//     TItem *Item;
//     int n, max;
// } TDicionario;

LinearSearch::LinearSearch() {}

TDicionario *LinearSearch::TDicionario_Inicia(int n, int *counter_comparisons)
{
    TDicionario *D;
    D = (TDicionario *) malloc(sizeof(TDicionario));
    D->n = 1;
    D->max = n;
    D->Item = (TItem *) malloc(D->max * sizeof(TItem));
    return D;
}

TApontador LinearSearch::TDicionario_Pesquisa(TDicionario *D, TChave c, int *counter_comparisons)
{
    TApontador i;
    for (i = 0; i < D->n; i++)
        (*counter_comparisons) ++;

        (*counter_comparisons) ++;
        if (D->Item[i].Chave == c)
            return i;
    return NIL;
}

int LinearSearch::TDicionario_Insere(TDicionario *D, TItem x, int *counter_comparisons)
{   
    (*counter_comparisons) ++;
    if (TDicionario_Pesquisa(D, x.Chave, counter_comparisons) != NIL)
        return 0;

    (*counter_comparisons) ++;
    if (D->n == D->max) {
        D->max *= 2;
        D->Item = (TItem *) realloc(D->Item, D->max * sizeof(TItem));
    }
    D->Item[D->n++] = x;
    return 1;
}

int LinearSearch::TDicionario_Retira(TDicionario *D, TChave c, int *counter_comparisons)
{
    TApontador i;
    i = TDicionario_Pesquisa(D, c, counter_comparisons);

    (*counter_comparisons) ++;
    if (i == NIL)
        return 0;
    D->Item[i] = D->Item[--D->n];

    (*counter_comparisons) ++;
    if (4 * D->n == D->max) {
        D->max /= 2;
        D->Item = (TItem *) realloc(D->Item, D->max * sizeof(TItem));
    }
    return 1;
}

std::variant<TDicionario*, TArvBin> LinearSearch::testInsere(std::vector<int> dataset, int *counter_comparisons) {

    auto dicionario = TDicionario_Inicia(dataset.size(), counter_comparisons);

    long long sum = 0;

    for (int i = 0; i < dataset.size(); ++i) {

        TItem item;
        item.Chave = dataset[i];

        int counter_comparisons_insertion = 0;

        TDicionario_Insere(dicionario, item, &counter_comparisons_insertion);

        sum += counter_comparisons_insertion;
    }

    (*counter_comparisons) = sum / dataset.size();

    return dicionario;
}

std::variant<TDicionario*, TArvBin> LinearSearch::testPesquisa(std::variant<TDicionario*, TArvBin> dicionario, std::vector<int> dataset, int *counter_comparisons) {

    if (std::holds_alternative<TDicionario*>(dicionario)) {
        TDicionario* dic_ptr = std::get<TDicionario*>(dicionario);

        long long sum = 0;

        for (int i = 0; i < dataset.size(); ++i) {

            int counter_comparisons_pesquisa = 0;

            TChave chave = dataset[i];
            TDicionario_Pesquisa(dic_ptr, chave, &counter_comparisons_pesquisa);

            sum += counter_comparisons_pesquisa;
        }

        (*counter_comparisons) = sum / dataset.size();
    }

    return dicionario;
}

std::variant<TDicionario*, TArvBin> LinearSearch::testRetira(std::variant<TDicionario*, TArvBin> dicionario, std::vector<int> dataset, int *counter_comparisons) {

    if (std::holds_alternative<TDicionario*>(dicionario)) {

        TDicionario* dic_ptr = std::get<TDicionario*>(dicionario);

        long long sum = 0;

        for (int i = 0; i < dataset.size(); ++i) {

            int counter_comparisons_retira = 0;

            TChave chave = dataset[i];

            TDicionario_Retira(dic_ptr, chave, &counter_comparisons_retira);

            sum += counter_comparisons_retira;
        }

        (*counter_comparisons) = sum / dataset.size();
    }

    return dicionario;
}