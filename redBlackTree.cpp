#include <iostream>
#include <vector>
#include <functional>
#include <map>
#include <string>
#include <utility>
#include <chrono>
#include <fstream>
#include <random>
#include <ctime>
#include <mutex>
#include <thread>
#include <atomic>
#include <iomanip>

#include "datasetGenerator.h"

#include "redBlackTree.h"

// using namespace std;

RedBlackTree::RedBlackTree() {}

int RedBlackTree::EhNegro(TArvBin No, int *counter_comparisons)
{   
    (*counter_comparisons) ++;
    return (No == NULL) || (No->cor == 0);
}

int RedBlackTree::EhRubro(TArvBin No, int *counter_comparisons)
{   
    (*counter_comparisons) ++;
    return (No != NULL) && (No->cor == 1);
}

int RedBlackTree::AlturaNegra(TArvBin No, int *counter_comparisons)
{
    int hEsq, hDir;

    (*counter_comparisons) ++;
    if (No == NULL)
        return 0;

    hEsq = AlturaNegra(No->Esq, counter_comparisons);
    hDir = AlturaNegra(No->Dir, counter_comparisons);

    (*counter_comparisons) ++;
    if (hEsq > hDir)
        return hEsq + EhNegro(No, counter_comparisons);
    else
        return hDir + EhNegro(No, counter_comparisons);
}

int RedBlackTree::ArvoreARN(TArvBin No, int *counter_comparisons)
{   
    (*counter_comparisons) ++;
    if (No == NULL)
        return 1;

    (*counter_comparisons) ++;
    if (!ArvoreARN(No->Esq, counter_comparisons))
        return 0;
    
    (*counter_comparisons) ++;
    if (!ArvoreARN(No->Dir, counter_comparisons))
        return 0;

    (*counter_comparisons) ++;
    if (EhRubro(No, counter_comparisons) && (!EhNegro(No->Esq, counter_comparisons) || !EhNegro(No->Dir, counter_comparisons)))
        return 0;

    (*counter_comparisons) ++;
    if (AlturaNegra(No->Esq, counter_comparisons) != AlturaNegra(No->Dir, counter_comparisons))
        return 0;

    return 1;
}

void RedBlackTree::InverteCor(TArvBin No, int *counter_comparisons)
{   
    (*counter_comparisons) ++;
    if (No != NULL) No->cor = !No->cor;
}

void RedBlackTree::TrocaCores(TArvBin No, int *counter_comparisons)
{
    InverteCor(No, counter_comparisons);
    InverteCor(No->Esq, counter_comparisons);
    InverteCor(No->Dir, counter_comparisons);
}

void RedBlackTree::RotacaoDireita(TArvBin *pA, int *counter_comparisons)
{
    TArvBin pB;
    pB = (*pA)->Esq;
    (*pA)->Esq = pB->Dir;
    pB->Dir = *pA;
    *pA = pB;
}

void RedBlackTree::RotacaoEsquerda(TArvBin *pA, int *counter_comparisons)
{
    TArvBin pB;
    pB = (*pA)->Dir;
    (*pA)->Dir = pB->Esq;
    pB->Esq = *pA;
    *pA = pB;
}

void RedBlackTree::BalancaDireitaInsere(TArvBin *pA, TArvBin *pB, TArvBin *pC, int *counter_comparisons)
{   
    (*counter_comparisons) ++;
    if (EhRubro((*pC)->Esq, counter_comparisons)) { // caso 1
        TrocaCores(*pC, counter_comparisons);
    } else {
        (*counter_comparisons) ++;
        if (*pB == (*pA)->Esq) { // caso 2b
            RotacaoDireita(pA, counter_comparisons);
        }

        InverteCor(*pA, counter_comparisons);
        InverteCor(*pC, counter_comparisons); // caso 3b
        RotacaoEsquerda(pC, counter_comparisons);  
    }
}

void RedBlackTree::BalancaEsquerdaInsere(TArvBin *pA, TArvBin *pB, TArvBin *pC, int *counter_comparisons)
{   
    (*counter_comparisons) ++;
    if (EhRubro((*pC)->Dir, counter_comparisons)) { // caso 1
        TrocaCores(*pC, counter_comparisons);
    } else {
        (*counter_comparisons) ++;
        if (*pB == (*pA)->Dir) { // caso 2a
            RotacaoEsquerda(pA, counter_comparisons);
        }

        InverteCor(*pA, counter_comparisons);
        InverteCor(*pC, counter_comparisons); // caso 3a
        RotacaoDireita(pC, counter_comparisons);
        
    }
}

void RedBlackTree::BalancaNoInsere(TArvBin *pA, TArvBin *pB, TArvBin *pC, int *counter_comparisons)
{   
    (*counter_comparisons) ++;
    if ((pC != NULL) && EhRubro(*pA, counter_comparisons) && EhRubro(*pB, counter_comparisons)) {
        (*counter_comparisons) ++;
        if (*pA == (*pC)->Esq)
            BalancaEsquerdaInsere(pA, pB, pC, counter_comparisons);
        else
            BalancaDireitaInsere(pA, pB, pC, counter_comparisons);
    }
}

int RedBlackTree::BalancaEsquerda(TArvBin *pC, int *counter_comparisons)
{
    TArvBin pD = (*pC)->Esq;

    (*counter_comparisons) ++;
    if (EhRubro(pD, counter_comparisons)) {
        RotacaoDireita(pC, counter_comparisons);
        pC = &(*pC)->Dir;
        pD = (*pC)->Esq;
    }

    (*counter_comparisons) ++;
    if (pD != NULL) {

        (*counter_comparisons) ++;
        if (EhNegro(pD->Esq, counter_comparisons) && EhNegro(pD->Dir, counter_comparisons)) {
            InverteCor(pD, counter_comparisons);

            (*counter_comparisons) ++;
            if (EhRubro(*pC, counter_comparisons)) {
                InverteCor(*pC, counter_comparisons);
                return 0;
            }
        }
        else {
            int cor = (*pC)->cor;
            (*pC)->cor = 0;

            (*counter_comparisons) ++;
            if (EhNegro(pD->Esq, counter_comparisons))
                RotacaoEsquerda(&(*pC)->Esq, counter_comparisons);
            else
                InverteCor(pD->Esq, counter_comparisons);

            RotacaoDireita(pC, counter_comparisons);
            (*pC)->cor = cor;
            return 0;
        }
    }
    return 1;
}

int RedBlackTree::BalancaDireita(TArvBin *pC, int *counter_comparisons)
{
    TArvBin pD = (*pC)->Dir;

    (*counter_comparisons) ++;
    if (EhRubro(pD, counter_comparisons)) {
        RotacaoEsquerda(pC, counter_comparisons);
        pC = &(*pC)->Esq;
        pD = (*pC)->Dir;
    }

    (*counter_comparisons) ++;
    if (pD != NULL) {

        (*counter_comparisons) ++;
        if (EhNegro(pD->Esq, counter_comparisons) && EhNegro(pD->Dir, counter_comparisons)) { // caso 1
            InverteCor(pD, counter_comparisons);

            (*counter_comparisons) ++;
            if (EhRubro(*pC, counter_comparisons)) {
                InverteCor(*pC, counter_comparisons);
                return 0;
            }
        }
        else {
            int cor = (*pC)->cor;
            (*pC)->cor = 0;

            (*counter_comparisons) ++;
            if (EhNegro(pD->Dir, counter_comparisons)) // caso 2a
                RotacaoDireita(&(*pC)->Dir, counter_comparisons);
            else
                InverteCor(pD->Dir, counter_comparisons);
                
            RotacaoEsquerda(pC, counter_comparisons); // caso 3a
            (*pC)->cor = cor;
            return 0;
        }
    }
    return 1;
}

void RedBlackTree::InsereRecursivo(TArvBin *pA, TArvBin *pC, TItem x, int *counter_comparisons)
{   
    if (*pA == NULL) {
        (*counter_comparisons) ++;

        *pA = (TArvBin) malloc(sizeof(TNo));
        (*pA)->Item = x; 
        (*pA)->Esq = NULL;
        (*pA)->Dir = NULL;
        (*pA)->cor = 1;
        
    }
    else if (x.Chave < (*pA)->Item.Chave) {
        (*counter_comparisons) += 2;

        InsereRecursivo(&(*pA)->Esq, pA, x, counter_comparisons);
        BalancaNoInsere(pA, &(*pA)->Esq, pC, counter_comparisons);
    }
    else if (x.Chave > (*pA)->Item.Chave) {
        (*counter_comparisons) += 3;
        
        InsereRecursivo(&(*pA)->Dir, pA, x, counter_comparisons);
        BalancaNoInsere(pA, &(*pA)->Dir, pC, counter_comparisons);
    }
}

void RedBlackTree::Insere(TArvBin *pRaiz, TItem x, int *counter_comparisons)
{
    InsereRecursivo(pRaiz, NULL, x, counter_comparisons);
    (*pRaiz)->cor = 0;
}

int RedBlackTree::Sucessor(TArvBin *q, TArvBin *r, int *counter_comparisons)
{
    int bh;

    (*counter_comparisons) ++;
    if ((*r)->Esq != NULL) {

        (*counter_comparisons) ++;
        if (Sucessor(q, &(*r)->Esq, counter_comparisons))
            return BalancaDireita(r, counter_comparisons);
        return 0;
    }
    else {
        (*q)->Item = (*r)->Item;
        *q = *r;
        *r = (*r)->Dir;
        bh = EhNegro(*q, counter_comparisons) && EhNegro(*r, counter_comparisons);

        (*counter_comparisons) ++;
        if (!bh && EhNegro(*q, counter_comparisons))
            (*r)->cor = 0;
        return bh;
    }
}

int RedBlackTree::RetiraRecursivo(TArvBin *p, TChave x, int *counter_comparisons)
{
    TArvBin q;
    int bh;
    if (*p == NULL) {
        (*counter_comparisons) ++;
        return 0;
    }
    else if (x < (*p)->Item.Chave) {
        (*counter_comparisons) += 2;

        (*counter_comparisons) ++;
        if (RetiraRecursivo(&(*p)->Esq, x, counter_comparisons))
            return BalancaDireita(p, counter_comparisons);
        return 0;
    }
    else if (x > (*p)->Item.Chave) {
        (*counter_comparisons) += 3;

        (*counter_comparisons) ++;
        if (RetiraRecursivo(&(*p)->Dir, x, counter_comparisons))
            return BalancaEsquerda(p, counter_comparisons);
        return 0;
    }
    else {
        (*counter_comparisons) += 3;

        q = *p;
        if (q->Esq == NULL) {
            (*counter_comparisons) ++;

            *p = q->Dir;
            bh = EhNegro(*p, counter_comparisons) && EhNegro(q, counter_comparisons);

            (*counter_comparisons) ++;
            if (!bh && EhNegro(q, counter_comparisons))
                (*p)->cor = 0;
        }
        else if (q->Dir == NULL) {
            (*counter_comparisons) += 2;

            *p = q->Esq;
            bh = EhNegro(*p, counter_comparisons) && EhNegro(q, counter_comparisons);

            (*counter_comparisons) ++;
            if (!bh && EhNegro(q, counter_comparisons))
                (*p)->cor = 0;
        }
        else { // possui dois filhos
            (*counter_comparisons) += 2;

            (*counter_comparisons) ++;
            if (Sucessor(&q, &q->Dir, counter_comparisons))
                bh = BalancaEsquerda(p, counter_comparisons);
            else bh = 0;
        }
        free(q);
        return bh;
    }
}

void RedBlackTree::Retira(TArvBin *pRaiz, TChave x, int *counter_comparisons)
{
    RetiraRecursivo(pRaiz, x, counter_comparisons);

    (*counter_comparisons) ++;
    if (*pRaiz != NULL)
        (*pRaiz)->cor = 0;
}

TArvBin* RedBlackTree::Pesquisa(TArvBin *No, TChave c, int *counter_comparisons)
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

// std::variant<TDicionario*, TArvBin> RedBlackTree::testInsere(std::vector<int> dataset, int *counter_comparisons) {
    
//     auto arvore = (TArvBin) malloc(dataset.size() * sizeof(TNo));
//     long long sum = 0;
    
//     for (int i = 0; i < dataset.size(); ++i) {
//         TItem item;
//         item.Chave = dataset[i];

//         int counter_comparisons_insertion = 0;
        
//         Insere(&arvore, item, &counter_comparisons_insertion);
        
//         sum += counter_comparisons_insertion;
//     }

//     (*counter_comparisons) = sum / dataset.size();

//     return arvore;
// }

std::variant<TDicionario*, TArvBin> RedBlackTree::testInsere(std::vector<int> dataset, int *counter_comparisons) {
    TArvBin arvore = NULL;
    long long sum = 0;

    for (int i = 0; i < dataset.size(); ++i) {
        TItem item;
        item.Chave = dataset[i];

        int counter_comparisons_insertion = 0;
        
        Insere(&arvore, item, &counter_comparisons_insertion);
        
        sum += counter_comparisons_insertion;
    }

    (*counter_comparisons) = sum / dataset.size();

    // Retornar arvore como um ponteiro de tipo TArvBin para evitar cópia desnecessária
    return arvore;
}

std::variant<TDicionario*, TArvBin> RedBlackTree::testPesquisa(std::variant<TDicionario*, TArvBin> dicionario, std::vector<int> dataset, int *counter_comparisons) {

    if (std::holds_alternative<TArvBin>(dicionario)) {

        TArvBin dic_ptr = std::get<TArvBin>(dicionario);

        if (dic_ptr == NULL) {
            return dicionario;
        }

        long long sum = 0;

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

std::variant<TDicionario*, TArvBin> RedBlackTree::testRetira(std::variant<TDicionario*, TArvBin> dicionario, std::vector<int> dataset, int *counter_comparisons) {

    if (std::holds_alternative<TArvBin>(dicionario)) {

        TArvBin dic_ptr = std::get<TArvBin>(dicionario);

        if (dic_ptr == NULL) {
            return dicionario;
        }

        long long sum = 0;

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
