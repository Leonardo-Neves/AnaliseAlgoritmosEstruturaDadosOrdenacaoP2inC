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
    int cor; 
} TNo;

int EhNegro(TArvBin No)
{
    return (No == NULL) || (No->cor == 0);
}

int EhRubro(TArvBin No)
{
    return (No != NULL) && (No->cor == 1);
}

int AlturaNegra(TArvBin No)
{
    int hEsq, hDir;
    if (No == NULL)
        return 0;
    hEsq = AlturaNegra(No->Esq);
    hDir = AlturaNegra(No->Dir);
    if (hEsq > hDir)
        return hEsq + EhNegro(No);
    else
        return hDir + EhNegro(No);
}

int ArvoreARN(TArvBin No)
{
    if (No == NULL)
        return 1;
    if (!ArvoreARN(No->Esq))
        return 0;
    if (!ArvoreARN(No->Dir))
        return 0;
    if (EhRubro(No) && (!EhNegro(No->Esq) || !EhNegro(No->Dir)))
        return 0;
    if (AlturaNegra(No->Esq) != AlturaNegra(No->Dir))
        return 0;
    return 1;
}

void InverteCor(TArvBin No)
{
    if (No != NULL) No->cor = !No->cor;
}

void TrocaCores(TArvBin No)
{
    InverteCor(No);
    InverteCor(No->Esq);
    InverteCor(No->Dir);
}

void RotacaoDireita(TArvBin *pA)
{
    TArvBin pB;
    pB = (*pA)->Esq;
    (*pA)->Esq = pB->Dir;
    pB->Dir = *pA;
    *pA = pB;
}

void RotacaoEsquerda(TArvBin *pA)
{
    TArvBin pB;
    pB = (*pA)->Dir;
    (*pA)->Dir = pB->Esq;
    pB->Esq = *pA;
    *pA = pB;
}

int BalancaEsquerda(TArvBin *pC)
{
    TArvBin pD = (*pC)->Esq;
    if (EhRubro(pD)) {
        RotacaoDireita(pC);
        pC = &(*pC)->Dir;
        pD = (*pC)->Esq;
    }
    if (pD != NULL) {
        if (EhNegro(pD->Esq) && EhNegro(pD->Dir)) {
            InverteCor(pD);
            if (EhRubro(*pC)) {
                InverteCor(*pC);
                return 0;
            }
        }
        else {
            int cor = (*pC)->cor;
            (*pC)->cor = 0;
            if (EhNegro(pD->Esq))
                RotacaoEsquerda(&(*pC)->Esq);
            else
                InverteCor(pD->Esq);
            RotacaoDireita(pC);
            (*pC)->cor = cor;
            return 0;
        }
    }
    return 1;
}

int BalancaDireita(TArvBin *pC)
{
    TArvBin pD = (*pC)->Dir;
    if (EhRubro(pD)) {
        RotacaoEsquerda(pC);
        pC = &(*pC)->Esq;
        pD = (*pC)->Dir;
    }
    if (pD != NULL) {
        if (EhNegro(pD->Esq) && EhNegro(pD->Dir)) { // caso 1
            InverteCor(pD);
            if (EhRubro(*pC)) {
                InverteCor(*pC);
                return 0;
            }
        }
        else {
            int cor = (*pC)->cor;
            (*pC)->cor = 0;
            if (EhNegro(pD->Dir)) // caso 2a
                RotacaoDireita(&(*pC)->Dir);
            else
                InverteCor(pD->Dir);
            RotacaoEsquerda(pC); // caso 3a
            (*pC)->cor = cor;
            return 0;
        }
    }
    return 1;
}

void BalancaNo(TArvBin *pA, TArvBin *pB, TArvBin *pC)
{
    if ((pC != NULL) && EhRubro(*pA) && EhRubro(*pB)) {
        if (*pA == (*pC)->Esq)
            BalancaEsquerda(pA, pB, pC);
        else
            BalancaDireita(pA, pB, pC);
    }
}

void InsereRecursivo(TArvBin *pA, TArvBin *pC, TItem x)
{
    if (*pA == NULL) {
        *pA = (TArvBin) malloc(sizeof(TNo));
        (*pA)->Item = x; (*pA)->Esq = NULL; (*pA)->Dir = NULL;
        (*pA)->cor = 1;
    }
    else if (x.Chave < (*pA)->Item.Chave) {
        InsereRecursivo(&(*pA)->Esq, pA, x);
        BalancaNo(pA, &(*pA)->Esq, pC);
    }
    else if (x.Chave > (*pA)->Item.Chave) {
        InsereRecursivo(&(*pA)->Dir, pA, x);
        BalancaNo(pA, &(*pA)->Dir, pC);
    }
}

void Insere(TArvBin *pRaiz, TItem x)
{
    InsereRecursivo(pRaiz, NULL, x);
    (*pRaiz)->cor = 0;
}

int Sucessor(TArvBin *q, TArvBin *r)
{
    int bh;
    if ((*r)->Esq != NULL) {
        if (Sucessor(q, &(*r)->Esq))
            return BalancaDireita(r);
        return 0;
    }
    else {
        (*q)->Item = (*r)->Item;
        *q = *r;
        *r = (*r)->Dir;
        bh = EhNegro(*q) && EhNegro(*r);
        if (!bh && EhNegro(*q))
            (*r)->cor = 0;
        return bh;
    }
}

int RetiraRecursivo(TArvBin *p, TChave x)
{
    TArvBin q;
    int bh;
    if (*p == NULL)
        return 0;
    else if (x < (*p)->Item.Chave) {
        if (RetiraRecursivo(&(*p)->Esq, x))
            return BalancaDireita(p);
        return 0;
    }
    else if (x > (*p)->Item.Chave) {
        if (RetiraRecursivo(&(*p)->Dir, x))
            return BalancaEsquerda(p);
        return 0;
    }
    else {
        q = *p;
        if (q->Esq == NULL) {
            *p = q->Dir;
            bh = EhNegro(*p) && EhNegro(q);
            if (!bh && EhNegro(q))
                (*p)->cor = 0;
        }
        else if (q->Dir == NULL) {
            *p = q->Esq;
            bh = EhNegro(*p) && EhNegro(q);
            if (!bh && EhNegro(q))
                (*p)->cor = 0;
        }
        else { // possui dois filhos
            if (Sucessor(&q, &q->Dir))
                bh = BalancaEsquerda(p);
            else bh = 0;
        }
        free(q);
        return bh;
    }
}

void Retira(TArvBin *pRaiz, TChave x)
{
    RetiraRecursivo(pRaiz, x);
    if (*pRaiz != NULL)
    (*pRaiz)->cor = 0;
}
