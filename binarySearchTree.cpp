#include <stdio.h>
#include <stdlib.h> 
#include <iostream>
#include <cstddef>

#include "datasetGenerator.h"

typedef int TChave;

typedef struct {
    TChave Chave;
} TItem;

typedef struct SNo *TArvBin;

typedef struct SNo {
    TItem Item;
    TArvBin Esq, Dir;
} TNo;

#define NIL NULL

typedef TArvBin TApontador;

typedef struct {
    TArvBin Raiz;
    int n;
} TDicionario;


TDicionario *TDicionario_Inicia(int n = 0)
{
    TDicionario *D;
    D = (TDicionario *) malloc(sizeof(TDicionario));
    D->n = 0;
    D->Raiz = NULL;
    return D;
}

TArvBin Pesquisa(TArvBin No, TChave c)
{
    if (No == NULL)
        return NULL;
    else if (c < No->Item.Chave)
        return Pesquisa(No->Esq, c);
    else if (c > No->Item.Chave)
        return Pesquisa(No->Dir, c);
    else
        return No;
}

int Insere(TArvBin *pNo, TItem x)
{
    if (*pNo == NULL) {
        *pNo = (TArvBin) malloc(sizeof(TNo));
        (*pNo)->Item = x;
        (*pNo)->Esq = NULL;
        (*pNo)->Dir = NULL;
        return 1;
    }
    else if (x.Chave < (*pNo)->Item.Chave)
        return Insere(&(*pNo)->Esq, x);
    else if (x.Chave > (*pNo)->Item.Chave)
        return Insere(&(*pNo)->Dir, x);
    else
        return 0;
}

void Predecessor(TArvBin *q, TArvBin *r)
{
    if ((*r)->Dir != NULL)
        Predecessor(q, &(*r)->Dir);
    else {
        (*q)->Item = (*r)->Item;
        *q = *r;
        *r = (*r)->Esq;
    }
}

void Sucessor(TArvBin *q, TArvBin *r)
{
    if ((*r)->Esq != NULL)
        Sucessor(q, &(*r)->Esq);
    else {
        (*q)->Item = (*r)->Item;
        *q = *r;
        *r = (*r)->Dir;
    }
}

int Retira(TArvBin *p, TChave c)
{
    TArvBin q;
    if (*p == NULL)
        return 0;
    else if (c < (*p)->Item.Chave)
        return Retira(&(*p)->Esq, c);
    else if (c > (*p)->Item.Chave)
        return Retira(&(*p)->Dir, c);
    else {
        q = *p;
        if (q->Esq == NULL)
            *p = q->Dir;
        else if (q->Dir == NULL)
            *p = q->Esq;
        else 
            Sucessor(&q, &q->Dir);
        free(q);
        return 1;
    }
}

TApontador TDicionario_Pesquisa(TDicionario *D, TChave c)
{
    return Pesquisa(D->Raiz, c);
}

int TDicionario_Insere(TDicionario *D, TItem x)
{
    if (!Insere(&D->Raiz, x))
        return 0;
    D->n++;
    return 1;
}

int TDicionario_Retira(TDicionario *D, TChave c)
{
    if (!Retira(&D->Raiz, c))
        return 0;
    D->n--;
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