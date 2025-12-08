#ifndef SENSORHEAP_H
#define SENSORHEAP_H

#include <vector>
#include <iostream>
#include "SensorData.h"

class SensorHeap {
private:
    std::vector<SensorData> dados;

    // Funções de navegação (inline para desempenho)
    int pai(int i) { return (i - 1) / 2; }
    int esquerda(int i) { return (2 * i) + 1; }
    int direita(int i) { return (2 * i) + 2; }

    void heapifyUp(int i);
    void heapifyDown(int i);

public:
    SensorHeap();

    // Insere um dado (O(log N))
    void insert(SensorData d);

    // Remove e retorna a maior temperatura (O(log N))
    SensorData extractMax();

    // Apenas olha a maior temperatura (O(1)) - Ponto forte da Heap!
    SensorData peekMax();
    
    // Retorna o tamanho atual
    int getSize();
};

#endif