#ifndef RBTREE_H
#define RBTREE_H
#include "SensorData.h"
#include <iostream>

enum Cor { VERMELHO, PRETO };

struct No {
    SensorData data; // Mudamos de int valor para SensorData
    No *esquerda;
    No *direita;
    No *pai;
    Cor cor;

    No(SensorData dados) {
        this->data = dados;
        this->cor = VERMELHO; // Novos nós são sempre vermelhos na inserção
        this->esquerda = nullptr;
        this->direita = nullptr;
        this->pai = nullptr;
    }
};

class RBTree {
private:
    No* raiz;
    int contador; // Para saber o tamanho da árvore rapidamente

    // Funções auxiliares internas
    void rotacionarEsquerda(No*& pt);
    void rotacionarDireita(No*& pt);
    void balancearInsercao(No*& pt);
    void destruirArvore(No* no); // Auxiliar para o destrutor
    void percursoEmOrdem(No* no); // Auxiliar para o print

    // Auxiliares para consultas
    void rangeQueryRec(No* no, float min, float max, int& count);
    
public:
    RBTree();
    ~RBTree();

    void insert(SensorData data);
    void printSorted(); // Imprime em ordem (Crescente)
    
    // Funções extras para o trabalho
    SensorData getMin();
    SensorData getMax();
    int getSize(); // Para cálculo da mediana
};

#endif