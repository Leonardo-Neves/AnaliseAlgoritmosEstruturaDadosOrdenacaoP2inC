#include <stdio.h>
#include <stdlib.h> 
#include <iostream>
#include <cstddef>

#include "datasetGenerator.h"

#include "binarySearchTree.h"

#define NIL NULL

BinarySearchTree::BinarySearchTree() {}

TDicionario *BinarySearchTree::TDicionario_Inicia(int n, int *counter_comparisons)
{
    TDicionario *D;
    D = (TDicionario *) malloc(n * sizeof(TDicionario));
    D->n = 0;
    D->Raiz = NULL;
    return D;
}

TArvBin BinarySearchTree::Pesquisa(TArvBin Raiz, TChave c, int *counter_comparisons)
{
    TArvBin No;
    No = Raiz;

    (*counter_comparisons)++;
    while ((No != NULL) && (c != No->Item.Chave)) {

        (*counter_comparisons)++;
        if (c < No->Item.Chave)
            No = No->Esq;
        else if (c > No->Item.Chave)
            No = No->Dir;
    }
    return No;

}

// int BinarySearchTree::Insere(TArvBin *pNo, TItem x, int *counter_comparisons)
// {
//     if (*pNo == NULL) {
//         (*counter_comparisons) ++;

//         *pNo = (TArvBin) malloc(sizeof(TNo));
//         (*pNo)->Item = x;
//         (*pNo)->Esq = NULL;
//         (*pNo)->Dir = NULL;
//         return 1;
//     }
//     else if (x.Chave < (*pNo)->Item.Chave) {
//         (*counter_comparisons) += 2;

//         return Insere(&(*pNo)->Esq, x, counter_comparisons);
//     }
//     else if (x.Chave > (*pNo)->Item.Chave) {
//         (*counter_comparisons) += 3;

//         return Insere(&(*pNo)->Dir, x, counter_comparisons);
//     }
//     else {
//         (*counter_comparisons) += 3;

//         return 0;
//     }
// }

int BinarySearchTree::Insere(TArvBin *pRaiz, TItem x, int *counter_comparisons)
{
    TArvBin *pNo;
    pNo = pRaiz;

    (*counter_comparisons)++;
    while ((*pNo != NULL) && (x.Chave != (*pNo)->Item.Chave)) {
        (*counter_comparisons)++;
        if (x.Chave < (*pNo)->Item.Chave)
            pNo = &(*pNo)->Esq;
        else if (x.Chave > (*pNo)->Item.Chave)
            pNo = &(*pNo)->Dir;
    }

    (*counter_comparisons)++;
    if (*pNo == NULL) {
        *pNo = (TArvBin) malloc(sizeof(TNo));
        (*pNo)->Item = x;
        (*pNo)->Esq = NULL;
        (*pNo)->Dir = NULL;
        return 1;
    }

    return 0;
}

void BinarySearchTree::Predecessor(TArvBin *q, TArvBin *r, int *counter_comparisons)
{   
    (*counter_comparisons) ++;
    if ((*r)->Dir != NULL)
        Predecessor(q, &(*r)->Dir, counter_comparisons);
    else {
        (*q)->Item = (*r)->Item;
        *q = *r;
        *r = (*r)->Esq;
    }
}

void BinarySearchTree::Sucessor(TArvBin *q, TArvBin *r, int *counter_comparisons)
{   
    (*counter_comparisons) ++;
    if ((*r)->Esq != NULL)
        Sucessor(q, &(*r)->Esq, counter_comparisons);
    else {
        (*q)->Item = (*r)->Item;
        *q = *r;
        *r = (*r)->Dir;
    }
}

int BinarySearchTree::Retira(TArvBin *pRaiz, TChave c, int *counter_comparisons)
{
    TArvBin *p, q;
    p = pRaiz;

    (*counter_comparisons)++;
    while ((*p != NULL) && (c != (*p)->Item.Chave)) {

        (*counter_comparisons)++;
        if (c < (*p)->Item.Chave)
            p = &(*p)->Esq;
        else if (c > (*p)->Item.Chave)
            p = &(*p)->Dir;
    }

    (*counter_comparisons)++;
    if (*p != NULL) {
        q = *p;
        (*counter_comparisons)++;
        if (q->Esq == NULL)
            *p = q->Dir;
        else if (q->Dir == NULL)
            *p = q->Esq;
        else
            Sucessor(&q, &q->Dir, counter_comparisons);
        free(q);
        return 1;
    }
    return 0;
}

void BinarySearchTree::TDicionario_Pesquisa(TDicionario *D, TChave c, int *counter_comparisons)
{
    Pesquisa(D->Raiz, c, counter_comparisons);
}

int BinarySearchTree::TDicionario_Insere(TDicionario *D, TItem x, int *counter_comparisons)
{
    (*counter_comparisons)++;
    if (!Insere(&D->Raiz, x, counter_comparisons))
        return 0;
    D->n++;
    return 1;
}

int BinarySearchTree::TDicionario_Retira(TDicionario *D, TChave c, int *counter_comparisons)
{   
    (*counter_comparisons)++;
    if (!Retira(&D->Raiz, c, counter_comparisons))
        return 0;
    D->n--;
    return 1;
}

// int main() {
//     int n = 10;

//     auto dicionario = TDicionario_Inicia(n);

//     DatasetGenerator datasetGenerator;

//     std::vector<int> dataset = datasetGenerator.generateOrderedInverse(n);

//     for (int i = 0; i < n; ++i) {
//         TItem item;
//         item.Chave = dataset[i];

//         TDicionario_Insere(dicionario, item);
//     }

//     TChave chave = 8;

//     std::cout << TDicionario_Pesquisa(dicionario, chave) << " ";

//     return 0;
// }

std::variant<TDicionario*, TArvBin> BinarySearchTree::testInsere(std::vector<int> dataset, int *counter_comparisons) {

    auto dicionario = TDicionario_Inicia(dataset.size(), counter_comparisons);

    int sum = 0;

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

std::variant<TDicionario*, TArvBin> BinarySearchTree::testPesquisa(std::variant<TDicionario*, TArvBin> dicionario, std::vector<int> dataset, int *counter_comparisons) {

    if (std::holds_alternative<TDicionario*>(dicionario)) {
        TDicionario* dic_ptr = std::get<TDicionario*>(dicionario);

        int sum = 0;

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

std::variant<TDicionario*, TArvBin> BinarySearchTree::testRetira(std::variant<TDicionario*, TArvBin> dicionario, std::vector<int> dataset, int *counter_comparisons) {

    if (std::holds_alternative<TDicionario*>(dicionario)) {

        TDicionario* dic_ptr = std::get<TDicionario*>(dicionario);

        int sum = 0;

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