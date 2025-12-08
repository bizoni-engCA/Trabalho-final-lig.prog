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

void RBTree::corrigirInsercao(No*& pt) {
    No* pai_pt = nullptr;
    No* avo_pt = nullptr;

    while ((pt != raiz) && (pt->cor != PRETO) && (pt->pai->cor == VERMELHO)) {
        pai_pt = pt->pai;
        avo_pt = pt->pai->pai;

        // Caso A: Pai é filho à esquerda do Avô
        if (pai_pt == avo_pt->esquerda) {
            No* tio_pt = avo_pt->direita;

            // Caso 1: Tio é vermelho (Recolorir)
            if (tio_pt != nullptr && tio_pt->cor == VERMELHO) {
                avo_pt->cor = VERMELHO;
                pai_pt->cor = PRETO;
                tio_pt->cor = PRETO;
                pt = avo_pt;
            } else {
                // Caso 2: pt é filho à direita (Rotação Dupla - Parte 1)
                if (pt == pai_pt->direita) {
                    rotacionarEsquerda(pai_pt);
                    pt = pai_pt;
                    pai_pt = pt->pai;
                }
                // Caso 3: pt é filho à esquerda (Rotação Simples)
                rotacionarDireita(avo_pt);
                std::swap(pai_pt->cor, avo_pt->cor);
                pt = pai_pt;
            }
        }
        // Caso B: Pai é filho à direita do Avô
        else {
            No* tio_pt = avo_pt->esquerda;

            // Caso 1: Tio é vermelho (Recolorir)
            if ((tio_pt != nullptr) && (tio_pt->cor == VERMELHO)) {
                avo_pt->cor = VERMELHO;
                pai_pt->cor = PRETO;
                tio_pt->cor = PRETO;
                pt = avo_pt;
            } else {
                // Caso 2: pt é filho à esquerda (Rotação Dupla - Parte 1)
                if (pt == pai_pt->esquerda) {
                    rotacionarDireita(pai_pt);
                    pt = pai_pt;
                    pai_pt = pt->pai;
                }
                // Caso 3: pt é filho à direita (Rotação Simples)
                rotacionarEsquerda(avo_pt);
                std::swap(pai_pt->cor, avo_pt->cor);
                pt = pai_pt;
            }
        }
    }
    raiz->cor = PRETO;
}

void RBTree::insert(SensorData data) {
    No* novo = new No(data);
    contador++; // Já incrementa o tamanho

    // Inserção padrão de BST
    if (raiz == nullptr) {
        novo->cor = PRETO;
        raiz = novo;
        return;
    }

    No* Y = nullptr;
    No* X = raiz;

    while (X != nullptr) {
        Y = X;
        if (novo->data < X->data)
            X = X->esquerda;
        else
            X = X->direita;
    }

    novo->pai = Y;
    if (novo->data < Y->data)
        Y->esquerda = novo;
    else
        Y->direita = novo;

    // Se inseriu na raiz (impossível cair aqui mas por segurança)
    if (novo->pai == nullptr) {
        novo->cor = PRETO;
        return;
    }

    // Se o pai é preto, não precisa fazer nada
    if (novo->pai->pai == nullptr)
        return;

    // Corrige a árvore
    corrigirInsercao(novo);
}

void RBTree::printSorted() {
    percursoEmOrdem(raiz);
    std::cout << "\n";
}

void RBTree::percursoEmOrdem(No* no) {
    if (no == nullptr) return;
    percursoEmOrdem(no->esquerda);
    no->data.print();
    percursoEmOrdem(no->direita);
}

SensorData RBTree::getMin() {
    if (raiz == nullptr) return {0,0};
    No* atual = raiz;
    while (atual->esquerda != nullptr) atual = atual->esquerda;
    return atual->data;
}

SensorData RBTree::getMax() {
    if (raiz == nullptr) return {0,0};
    No* atual = raiz;
    while (atual->direita != nullptr) atual = atual->direita;
    return atual->data;
}

int RBTree::getSize() { return contador; }