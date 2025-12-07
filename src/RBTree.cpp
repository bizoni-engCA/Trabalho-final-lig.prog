#include "RBTree.h"

RBTree::RBTree() {
    raiz = nullptr;
    contador = 0;
}

RBTree::~RBTree() {
    destruirArvore(raiz);
}

void RBTree::destruirArvore(No* no) {
    if (no == nullptr) return;
    destruirArvore(no->esquerda);
    destruirArvore(no->direita);
    delete no;
}

// *** ROTAÇÃO À ESQUERDA ***
void RBTree::rotacionarEsquerda(No*& pt) {
    No* pt_direita = pt->direita;
    pt->direita = pt_direita->esquerda;

    if (pt->direita != nullptr)
        pt->direita->pai = pt;

    pt_direita->pai = pt->pai;

    if (pt->pai == nullptr)
        raiz = pt_direita;
    else if (pt == pt->pai->esquerda)
        pt->pai->esquerda = pt_direita;
    else
        pt->pai->direita = pt_direita;

    pt_direita->esquerda = pt;
    pt->pai = pt_direita;
}

// *** ROTAÇÃO À DIREITA ***
void RBTree::rotacionarDireita(No*& pt) {
    No* pt_esquerda = pt->esquerda;
    pt->esquerda = pt_esquerda->direita;

    if (pt->esquerda != nullptr)
        pt->esquerda->pai = pt;

    pt_esquerda->pai = pt->pai;

    if (pt->pai == nullptr)
        raiz = pt_esquerda;
    else if (pt == pt->pai->esquerda)
        pt->pai->esquerda = pt_esquerda;
    else
        pt->pai->direita = pt_esquerda;

    pt_esquerda->direita = pt;
    pt->pai = pt_esquerda;
}

// *** BALANCEAMENTO PÓS-INSERÇÃO ***
void RBTree::balancearInsercao(No*& pt) {
    No* pai_pt = nullptr;
    No* avo_pt = nullptr;

    while ((pt != raiz) && (pt->cor != PRETO) && (pt->pai->cor == VERMELHO)) {
        pai_pt = pt->pai;
        avo_pt = pt->pai->pai;

        /* Caso A: Pai do pt é filho à esquerda do avô */
        if (pai_pt == avo_pt->esquerda) {
            No* tio_pt = avo_pt->direita;

            /* Caso 1: O tio é vermelho (apenas recolorir) */
            if (tio_pt != nullptr && tio_pt->cor == VERMELHO) {
                avo_pt->cor = VERMELHO;
                pai_pt->cor = PRETO;
                tio_pt->cor = PRETO;
                pt = avo_pt;
            } else {
                /* Caso 2: pt é filho à direita (rotação dupla necessária) */
                if (pt == pai_pt->direita) {
                    rotacionarEsquerda(pai_pt);
                    pt = pai_pt;
                    pai_pt = pt->pai;
                }
                /* Caso 3: pt é filho à esquerda (rotação simples) */
                rotacionarDireita(avo_pt);
                std::swap(pai_pt->cor, avo_pt->cor);
                pt = pai_pt;
            }
        }
        /* Caso B: Pai do pt é filho à direita do avô */
        else {
            No* tio_pt = avo_pt->esquerda;

            /* Caso 1: O tio é vermelho (apenas recolorir) */
            if ((tio_pt != nullptr) && (tio_pt->cor == VERMELHO)) {
                avo_pt->cor = VERMELHO;
                pai_pt->cor = PRETO;
                tio_pt->cor = PRETO;
                pt = avo_pt;
            } else {
                /* Caso 2: pt é filho à esquerda (rotação dupla necessária) */
                if (pt == pai_pt->esquerda) {
                    rotacionarDireita(pai_pt);
                    pt = pai_pt;
                    pai_pt = pt->pai;
                }
                /* Caso 3: pt é filho à direita (rotação simples) */
                rotacionarEsquerda(avo_pt);
                std::swap(pai_pt->cor, avo_pt->cor);
                pt = pai_pt;
            }
        }
    }
    raiz->cor = PRETO;
}

// *** INSERÇÃO PÚBLICA ***
void RBTree::insert(SensorData data) {
    No* novo = new No(data);
    raiz =  (raiz == nullptr) ? novo : raiz; // Proteção inicial

    No* Y = nullptr;
    No* X = raiz;

    // Busca a posição (BST normal)
    while (X != nullptr) {
        Y = X;
        // Usa o operador < que definimos no SensorData
        if (novo->data < X->data)
            X = X->esquerda;
        else
            X = X->direita;
    }

    // Conecta o novo nó
    novo->pai = Y;
    if (Y == nullptr) {
        raiz = novo;
    } else if (novo->data < Y->data) {
        Y->esquerda = novo;
    } else {
        Y->direita = novo;
    }

    // Se for raiz, é preto e acabou
    if (novo->pai == nullptr) {
        novo->cor = PRETO;
        contador++;
        return;
    }

    // Se o pai for raiz, não precisa balancear
    if (novo->pai->pai == nullptr) {
        contador++;
        return;
    }

    // Balanceia a árvore
    balancearInsercao(novo);
    contador++;
}

void RBTree::printSorted() {
    percursoEmOrdem(raiz);
    std::cout << "\n";
}

void RBTree::percursoEmOrdem(No* no) {
    if (no == nullptr) return;
    percursoEmOrdem(no->esquerda);
    // Imprime o dado usando a função que criamos no SensorData
    no->data.print(); 
    percursoEmOrdem(no->direita);
}

SensorData RBTree::getMin() {
    if (raiz == nullptr) return {0,0,0};
    No* atual = raiz;
    while (atual->esquerda != nullptr) {
        atual = atual->esquerda;
    }
    return atual->data;
}

SensorData RBTree::getMax() {
    if (raiz == nullptr) return {0,0,0};
    No* atual = raiz;
    while (atual->direita != nullptr) {
        atual = atual->direita;
    }
    return atual->data;
}

int RBTree::getSize() {
    return contador;
}