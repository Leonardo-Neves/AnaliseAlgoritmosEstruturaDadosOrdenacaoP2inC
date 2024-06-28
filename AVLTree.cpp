#include <stdio.h>
#include <stdlib.h> 
#include <iostream>
#include <cstddef>

#include "datasetGenerator.h"

#include "AVLTree.h"

AVLTree::AVLTree() {}

int AVLTree::Altura(TArvBin No, int *counter_comparisons)
{
    int hEsq, hDir;

    (*counter_comparisons) ++;
    if (No == NULL)
        return -1;

    hEsq = Altura(No->Esq, counter_comparisons);
    hDir = Altura(No->Dir, counter_comparisons);

    (*counter_comparisons) ++;
    if (hEsq > hDir)
        return hEsq + 1;
    else
        return hDir + 1;
}

int AVLTree::FB(TArvBin No, int *counter_comparisons)
{   
    (*counter_comparisons) ++;
    if (No == NULL)
        return 0;
    return No->fb;
}

int AVLTree::ArvoreAVL(TArvBin No, int *counter_comparisons)
{
    int fb;

    (*counter_comparisons) ++;
    if (No == NULL)
        return 1;

    (*counter_comparisons) ++;
    if (!ArvoreAVL(No->Esq, counter_comparisons))
        return 0;

    (*counter_comparisons) ++;
    if (!ArvoreAVL(No->Dir, counter_comparisons))
        return 0;

    fb = FB(No, counter_comparisons);

    (*counter_comparisons) ++;
    if ((fb > 1) || (fb < -1))
        return 0;
    else
        return 1;
}

void AVLTree::LL(TArvBin *pA, int *counter_comparisons)
{
    TArvBin pB;
    pB = (*pA)->Esq;
    (*pA)->Esq = pB->Dir;
    pB->Dir = *pA;

    (*counter_comparisons) ++;
    if (pB->fb == 0) { (*pA)->fb = +1; pB->fb = -1; }
    else { (*pA)->fb = 0; pB->fb = 0; }

    *pA = pB;
}

void AVLTree::RR(TArvBin *pA, int *counter_comparisons)
{
    TArvBin pB;
    pB = (*pA)->Dir;
    (*pA)->Dir = pB->Esq;
    pB->Esq = *pA;

    (*counter_comparisons) ++;
    if (pB->fb == 0) { (*pA)->fb = -1; pB->fb = +1; }
    else { (*pA)->fb = 0; pB->fb = 0; }

    *pA = pB;
}

void AVLTree::LR(TArvBin *pA, int *counter_comparisons)
{
    TArvBin pB, pC;
    pB = (*pA)->Esq;
    pC = pB->Dir;
    pB->Dir = pC->Esq;
    pC->Esq = pB;
    (*pA)->Esq = pC->Dir;
    pC->Dir = *pA;

    (*counter_comparisons) ++;
    if (pC->fb == +1) (*pA)->fb = -1; else (*pA)->fb = 0;

    (*counter_comparisons) ++;
    if (pC->fb == -1) pB->fb = +1; else pB->fb = 0;

    pC->fb = 0;
    *pA = pC;
}

void AVLTree::RL(TArvBin *pA, int *counter_comparisons)
{
    TArvBin pB, pC;
    pB = (*pA)->Dir;
    pC = pB->Esq;
    pB->Esq = pC->Dir;
    pC->Dir = pB;
    (*pA)->Dir = pC->Esq;
    pC->Esq = *pA;

    (*counter_comparisons) ++;
    if (pC->fb == -1) (*pA)->fb = +1; else (*pA)->fb = 0;

    (*counter_comparisons) ++;
    if (pC->fb == +1) pB->fb = -1; else pB->fb = 0;

    pC->fb = 0;
    *pA = pC;
}

int AVLTree::BalancaEsquerda(TArvBin *pNo, int *counter_comparisons)
{
    int fbe = FB((*pNo)->Esq, counter_comparisons);
    if (fbe > 0) {
        (*counter_comparisons) ++;

        LL(pNo, counter_comparisons);
        return 1;
    }
    else if (fbe < 0) {
        (*counter_comparisons) += 2;

        LR(pNo, counter_comparisons);
        return 1;
    }
    else {
        (*counter_comparisons) += 2;

        LL(pNo, counter_comparisons);
        return 0;
    }
}

int AVLTree::BalancaDireita(TArvBin *pNo, int *counter_comparisons)
{
    int fbd = FB((*pNo)->Dir, counter_comparisons);
    if (fbd < 0) {
        (*counter_comparisons) ++;

        RR(pNo, counter_comparisons);
        return 1;
    }
    else if (fbd > 0) {
        (*counter_comparisons) += 2;

        RL(pNo, counter_comparisons);
        return 1;
    }
    else {
        (*counter_comparisons) += 2;

        RR(pNo, counter_comparisons);
        return 0;
    }
}

int AVLTree::BalancaNo(TArvBin *pNo, int *counter_comparisons)
{
    int fb = FB(*pNo, counter_comparisons);

    if (fb > 1) {
        (*counter_comparisons) ++;
        return BalancaEsquerda(pNo, counter_comparisons);
    }
    else if (fb < -1) {
        (*counter_comparisons) += 2;
        return BalancaDireita(pNo, counter_comparisons);
    }
        
    return 0;
}

int AVLTree::Insere(TArvBin *pNo, TItem x, int *counter_comparisons)
{
    if (*pNo == NULL) {
        (*counter_comparisons) ++;
        *pNo = (TArvBin) malloc(sizeof(TNo));
        (*pNo)->Item = x; (*pNo)->Esq = NULL; (*pNo)->Dir = NULL; (*pNo)->fb = 0;
        return 1;
    }
    else if (x.Chave < (*pNo)->Item.Chave) {
        (*counter_comparisons) += 2;

        (*counter_comparisons) ++;
        if (Insere(&(*pNo)->Esq, x, counter_comparisons)) {

            (*counter_comparisons) ++;
            switch ((*pNo)->fb) {
                case -1: (*pNo)->fb = 0; return 0;
                case 0: (*pNo)->fb = +1; return 1;
                case +1: return !BalancaEsquerda(pNo, counter_comparisons);
            }
        }
            
        return 0;
    }
    else if (x.Chave > (*pNo)->Item.Chave) {
        (*counter_comparisons) += 3;

        (*counter_comparisons) ++;
        if (Insere(&(*pNo)->Dir, x, counter_comparisons)) {

            (*counter_comparisons) ++;
            switch ((*pNo)->fb) { 
                case +1: (*pNo)->fb = 0; return 0;
                case 0: (*pNo)->fb = -1; return 1;
                case -1: return !BalancaDireita(pNo, counter_comparisons);
            }
        }
            
        return 0;
    }
    else {
        (*counter_comparisons) += 3;

        return 0;
    }
}

int AVLTree::Sucessor(TArvBin *q, TArvBin *r, int *counter_comparisons)
{   
    (*counter_comparisons) ++;
    if ((*r)->Esq != NULL) {

        (*counter_comparisons) ++;
        if (Sucessor(q, &(*r)->Esq, counter_comparisons)) {

            (*counter_comparisons) ++;
            switch ((*r)->fb) {
                case +1: (*r)->fb = 0; return 1;
                case 0: (*r)->fb = -1; return 0;
                case -1: return BalancaDireita(r, counter_comparisons);
            }
        }
            
        return 0;
    }
    else {
        (*q)->Item = (*r)->Item;
        *q = *r;
        *r = (*r)->Dir;
        return 1;
    }
}

int AVLTree::Retira(TArvBin *p, TChave c, int *counter_comparisons)
{
    TArvBin q; int ret;
    if (*p == NULL) {
        (*counter_comparisons) ++;

        return 0;
    }
    else if (c < (*p)->Item.Chave) {
        (*counter_comparisons) += 2;

        (*counter_comparisons) ++;
        if (Retira(&(*p)->Esq, c, counter_comparisons)) {

            (*counter_comparisons) ++;
            switch ((*p)->fb) {
                case +1: (*p)->fb = 0; return 1;
                case 0: (*p)->fb = -1; return 0;
                case -1: return BalancaDireita(p, counter_comparisons);
            }
        }            
        return 0;
    }
    else if (c > (*p)->Item.Chave) {
        (*counter_comparisons) += 3;

        (*counter_comparisons) ++;
        if (Retira(&(*p)->Dir, c, counter_comparisons)) {

            (*counter_comparisons) ++;
            switch ((*p)->fb) {
                case -1: (*p)->fb = 0; return 1;
                case 0: (*p)->fb = +1; return 0;
                case +1: return BalancaEsquerda(p, counter_comparisons);
            }
        }

        return 0;
    }
    else {
        (*counter_comparisons) += 3;

        q = *p;
        if (q->Esq == NULL) { 
            (*counter_comparisons) ++;

            *p = q->Dir; ret = 1; 
        }
        else if (q->Dir == NULL) { 
            (*counter_comparisons) += 2;

            *p = q->Esq; ret = 1; 
        }
        else {
            (*counter_comparisons) += 2;

            (*counter_comparisons) ++;
            if (Sucessor(&q, &q->Dir, counter_comparisons)) {

                (*counter_comparisons) ++;
                switch ((*p)->fb) {
                    case -1: (*p)->fb = 0; ret = 1; break;
                    case 0: (*p)->fb = +1; ret = 0; break;
                    case +1: ret = BalancaEsquerda(p, counter_comparisons); break;
                }
            }
            else {
                ret = 0;
            }
        }
        free(q);
        return ret;
    }
}

TArvBin* AVLTree::Pesquisa(TArvBin *No, TChave c, int *counter_comparisons)
{
    if (No == NULL) {
        (*counter_comparisons) ++;

        return NULL;
    }
    else if (c < (*No)->Item.Chave) {
        (*counter_comparisons) += 2;

        return Pesquisa(&(*No)->Esq, c, counter_comparisons);
    }
    else if (c > (*No)->Item.Chave) {
        (*counter_comparisons) += 3;

        return Pesquisa(&(*No)->Dir, c, counter_comparisons);
    }
    else {
        (*counter_comparisons) += 3;

        return No;
    }
        
}

std::variant<TDicionario*, TArvBin> AVLTree::testInsere(std::vector<int> dataset, int *counter_comparisons) {

    auto arvore = (TArvBin) malloc(sizeof(TNo));

    int sum = 0;

    for (int i = 0; i < dataset.size(); ++i) {
        TItem item;
        item.Chave = dataset[i];

        int counter_comparisons_insertion = 0;

        Insere(&arvore, item, &counter_comparisons_insertion);

        sum += counter_comparisons_insertion;
    }

    (*counter_comparisons) = sum / dataset.size();

    return arvore;
}

std::variant<TDicionario*, TArvBin> AVLTree::testPesquisa(std::variant<TDicionario*, TArvBin> dicionario, std::vector<int> dataset, int *counter_comparisons) {

    if (std::holds_alternative<TArvBin>(dicionario)) {

        TArvBin dic_ptr = std::get<TArvBin>(dicionario);

        if (dic_ptr == NULL) {
            return dicionario;
        }

        int sum = 0;

        for (int i = 0; i < dataset.size(); ++i) {

            int counter_comparisons_retira = 0;

            TChave chave = dataset[i];

            Pesquisa(&dic_ptr, chave, &counter_comparisons_retira);

            sum += counter_comparisons_retira;
        }

        (*counter_comparisons) = sum / dataset.size();

    }

    return dicionario;
}

std::variant<TDicionario*, TArvBin> AVLTree::testRetira(std::variant<TDicionario*, TArvBin> dicionario, std::vector<int> dataset, int *counter_comparisons) {

    if (std::holds_alternative<TArvBin>(dicionario)) {

        TArvBin dic_ptr = std::get<TArvBin>(dicionario);

        int sum = 0;

        for (int i = 0; i < dataset.size(); ++i) {

            int counter_comparisons_retira = 0;

            TChave chave = dataset[i];

            Retira(&dic_ptr, chave, &counter_comparisons_retira);

            sum += counter_comparisons_retira;
        }

        (*counter_comparisons) = sum / dataset.size();
    }

    return dicionario;
}
