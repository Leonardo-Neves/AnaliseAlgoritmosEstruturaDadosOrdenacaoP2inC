#include <stdio.h>
#include <stdlib.h> 
#include <iostream>
#define NIL -1

#include "datasetGenerator.h"

#include "binarySearch.h"

BinarySearch::BinarySearch() {}

TDicionario *BinarySearch::TDicionario_Inicia(int n, int *counter_comparisons)
{
    TDicionario *D;
    D = (TDicionario *) malloc(sizeof(TDicionario));
    D->n = 0;
    D->max = n;
    D->Item = (TItem *) malloc(D->max * sizeof(TItem));
    return D;
}

TApontador BinarySearch::TDicionario_Binaria(TDicionario *D, TApontador esq, TApontador dir, TChave c, int *counter_comparisons)
{
    TApontador meio;
    meio = (esq + dir) / 2;

    if (esq > dir) {
        (*counter_comparisons) ++;
        return NIL;
    }
    else if (c > D->Item[meio].Chave) {
        (*counter_comparisons) += 2;
        return TDicionario_Binaria(D, meio+1, dir, c, counter_comparisons);
    }   
    else if (c < D->Item[meio].Chave) {
        (*counter_comparisons) += 3;
        return TDicionario_Binaria(D, esq, meio-1, c, counter_comparisons);
    }
    else {
        (*counter_comparisons) += 3;

        return meio;
    }
        
}

TApontador BinarySearch::TDicionario_Pesquisa(TDicionario *D, TChave c, int *counter_comparisons)
{
    return TDicionario_Binaria(D, 0, D->n-1, c, counter_comparisons);
}

int BinarySearch::TDicionario_Insere(TDicionario *D, TItem x, int *counter_comparisons)
{
    TApontador i;

    (*counter_comparisons) ++;
    if (TDicionario_Pesquisa(D, x.Chave, counter_comparisons) != NIL) {
        return 0;
    }

    (*counter_comparisons) ++;
    if (D->n == D->max) {
        D->max *= 2;
        D->Item = (TItem *) realloc(D->Item, D->max * sizeof(TItem));
    }

    i = D->n - 1;
    while ((i >= 0) && (x.Chave < D->Item[i].Chave)) {
        (*counter_comparisons) ++;

        D->Item[i + 1] = D->Item[i];
        i--;
    }

    D->Item[i + 1] = x;
    D->n++;

    return 1;
}

int BinarySearch::TDicionario_Retira(TDicionario *D, TChave c, int *counter_comparisons)
{
    TApontador i;
    i = TDicionario_Pesquisa(D, c, counter_comparisons);

    (*counter_comparisons) ++;
    if (i == NIL) {
        return 0;
    }

    while (i < D->n - 1) {
        (*counter_comparisons) ++;
        D->Item[i] = D->Item[i + 1];
        i++;
    }
    D->n--;

    (*counter_comparisons) ++;
    if (4 * D->n == D->max) {
        D->max /= 2;
        D->Item = (TItem *) realloc(D->Item, D->max * sizeof(TItem));
    }
    return 1;
}

std::variant<TDicionario*, TArvBin> BinarySearch::testInsere(std::vector<int> dataset, int *counter_comparisons) {

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

std::variant<TDicionario*, TArvBin> BinarySearch::testPesquisa(std::variant<TDicionario*, TArvBin> dicionario, std::vector<int> dataset, int *counter_comparisons) {

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

std::variant<TDicionario*, TArvBin> BinarySearch::testRetira(std::variant<TDicionario*, TArvBin> dicionario, std::vector<int> dataset, int *counter_comparisons) {

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