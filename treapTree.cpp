#include <stdio.h>
#include <stdlib.h> 
#include <iostream>
#include <cstddef>
#include <ctime>
#include <cstdlib>

typedef int TChave;

typedef struct {
    TChave Chave;
    int Priority;
} TItem;

typedef int TApontador;

typedef struct SNo *TArvBin;

typedef struct SNo {
    TItem Item;
    TArvBin Esq, Dir;
} TNo;

typedef struct {
    TItem *Item;
    TArvBin Raiz;
    int n, max;
} TDicionario;

class Treap {
public:
    Treap();

    int Altura(TArvBin No, int *counter_comparisons);
    TArvBin* Pesquisa(TArvBin *No, TChave c, int *counter_comparisons);
    int Insere(TArvBin *pNo, TItem x, int *counter_comparisons);
    int Retira(TArvBin *p, TChave c, int *counter_comparisons);

private:
    void RR(TArvBin *pA, int *counter_comparisons);
    void LL(TArvBin *pA, int *counter_comparisons);
};

Treap::Treap() {
    srand(time(NULL));
}

int Treap::Altura(TArvBin No, int *counter_comparisons) {
    int hEsq, hDir;

    (*counter_comparisons)++;
    if (No == NULL)
        return -1;

    hEsq = Altura(No->Esq, counter_comparisons);
    hDir = Altura(No->Dir, counter_comparisons);

    (*counter_comparisons)++;
    if (hEsq > hDir)
        return hEsq + 1;
    else
        return hDir + 1;
}

void Treap::LL(TArvBin *pA, int *counter_comparisons) {
    TArvBin pB;
    pB = (*pA)->Esq;
    (*pA)->Esq = pB->Dir;
    pB->Dir = *pA;
    *pA = pB;
}

void Treap::RR(TArvBin *pA, int *counter_comparisons) {
    TArvBin pB;
    pB = (*pA)->Dir;
    (*pA)->Dir = pB->Esq;
    pB->Esq = *pA;
    *pA = pB;
}

TArvBin* Treap::Pesquisa(TArvBin *No, TChave c, int *counter_comparisons) {
    if (No == NULL) {
        (*counter_comparisons)++;
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

int Treap::Insere(TArvBin *pNo, TItem x, int *counter_comparisons) {
    if (*pNo == NULL) {
        (*counter_comparisons)++;
        *pNo = (TArvBin)malloc(sizeof(TNo));
        (*pNo)->Item = x; (*pNo)->Esq = NULL; (*pNo)->Dir = NULL;
        return 1;
    }
    else if (x.Chave < (*pNo)->Item.Chave) {
        (*counter_comparisons) += 2;
        if (Insere(&(*pNo)->Esq, x, counter_comparisons)) {
            (*counter_comparisons)++;
            if ((*pNo)->Esq->Item.Priority < (*pNo)->Item.Priority) {
                LL(pNo, counter_comparisons);
            }
        }
        return 1;
    }
    else if (x.Chave > (*pNo)->Item.Chave) {
        (*counter_comparisons) += 3;
        if (Insere(&(*pNo)->Dir, x, counter_comparisons)) {
            (*counter_comparisons)++;
            if ((*pNo)->Dir->Item.Priority < (*pNo)->Item.Priority) {
                RR(pNo, counter_comparisons);
            }
        }
        return 1;
    }
    else {
        (*counter_comparisons) += 3;
        return 0;
    }
}

int Treap::Retira(TArvBin *p, TChave c, int *counter_comparisons) {
    if (*p == NULL) {
        (*counter_comparisons)++;
        return 0;
    }
    else if (c < (*p)->Item.Chave) {
        (*counter_comparisons) += 2;
        return Retira(&(*p)->Esq, c, counter_comparisons);
    }
    else if (c > (*p)->Item.Chave) {
        (*counter_comparisons) += 3;
        return Retira(&(*p)->Dir, c, counter_comparisons);
    }
    else {
        (*counter_comparisons) += 3;
        TArvBin q = *p;
        if ((*p)->Esq == NULL) {
            *p = (*p)->Dir;
            free(q);
            return 1;
        }
        else if ((*p)->Dir == NULL) {
            *p = (*p)->Esq;
            free(q);
            return 1;
        }
        else {
            if ((*p)->Esq->Item.Priority < (*p)->Dir->Item.Priority) {
                LL(p, counter_comparisons);
                return Retira(&(*p)->Dir, c, counter_comparisons);
            }
            else {
                RR(p, counter_comparisons);
                return Retira(&(*p)->Esq, c, counter_comparisons);
            }
        }
    }
}

int main() {

    auto arvore = (TArvBin) malloc(sizeof(TNo));

    Treap treap;

    int comparisons = 0;
    TItem item1 = {10, rand()};
    TItem item2 = {20, rand()};
    TItem item3 = {5, rand()};

    treap.Insere(&arvore, item1, &comparisons);
    treap.Insere(&arvore, item2, &comparisons);
    treap.Insere(&arvore, item3, &comparisons);

    // TArvBin found = treap.Pesquisa(&arvore, 10, &comparisons);
    // if (found) {
    //     std::cout << "Found key: " << found->Item.Chave << std::endl;
    // } else {
    //     std::cout << "Key not found" << std::endl;
    // }

    // treap.Retira(&arvore, 10, &comparisons);

    // found = treap.Pesquisa(&arvore, 10, &comparisons);
    // if (found) {
    //     std::cout << "Found key: " << found->Item.Chave << std::endl;
    // } else {
    //     std::cout << "Key not found" << std::endl;
    // }

    return 0;
}
