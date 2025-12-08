#include "SensorHeap.h"
#include <algorithm> // Para std::swap

SensorHeap::SensorHeap() {}

void SensorHeap::heapifyUp(int i) {
    // Enquanto não for a raiz e for maior que o pai, sobe
    while (i > 0 && dados[pai(i)].temp < dados[i].temp) {
        std::swap(dados[pai(i)], dados[i]);
        i = pai(i);
    }
}

void SensorHeap::heapifyDown(int i) {
    int maxIndex = i;
    int l = esquerda(i);
    int r = direita(i);
    int n = dados.size();

    // Compara com filho da esquerda
    if (l < n && dados[l].temp > dados[maxIndex].temp)
        maxIndex = l;

    // Compara com filho da direita
    if (r < n && dados[r].temp > dados[maxIndex].temp)
        maxIndex = r;

    // Se o maior não for o pai, troca e continua descendo
    if (i != maxIndex) {
        std::swap(dados[i], dados[maxIndex]);
        heapifyDown(maxIndex);
    }
}

void SensorHeap::insert(SensorData d) {
    dados.push_back(d);      // Coloca no final
    heapifyUp(dados.size() - 1); // Conserta subindo
}

SensorData SensorHeap::extractMax() {
    if (dados.empty()) return {0.0, 0.0}; // Retorno de erro

    SensorData maximo = dados[0];
    dados[0] = dados.back(); // Traz o último para o topo
    dados.pop_back();        // Remove o último
    heapifyDown(0);          // Reorganiza descendo
    
    return maximo;
}

SensorData SensorHeap::peekMax() {
    if (!dados.empty()) return dados[0];
    return {0.0, 0.0};
}

int SensorHeap::getSize() {
    return dados.size();
}