    #ifndef RBTREE_H
#define RBTREE_H

#include "SensorData.h"
#include <iostream>

enum Cor { VERMELHO, PRETO };

struct No {
    SensorData data;
    No *esquerda;
    No *direita;
    No *pai;
    Cor cor;

    No(SensorData dados) {
        this->data = dados;
        this->cor = VERMELHO;
        this->esquerda = nullptr;
        this->direita = nullptr;
        this->pai = nullptr;
    }
};

class RBTree {
private:
    No* raiz;
    int contador;

    // Funções auxiliares
    void rotacionarEsquerda(No*& pt);
    void rotacionarDireita(No*& pt);
    void corrigirInsercao(No*& pt); // Lógica corrigida
    void destruirArvore(No* no);
    void percursoEmOrdem(No* no);

public:
    RBTree();
    ~RBTree();

    void insert(SensorData data);
    void printSorted();
    SensorData getMin();
    SensorData getMax();
    int getSize();
};

#endif