#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "SensorData.h"

struct ListNode {
    SensorData data;
    ListNode* next;
    
    ListNode(SensorData d) : data(d), next(nullptr) {}
};

class LinkedList {
private:
    ListNode* head;
    int tamanho;

public:
    LinkedList();
    ~LinkedList();

    // Requisito: Inserção Ordenada (Insertion Sort)
    void insertOrdered(SensorData data); 

    // Requisitos do Trabalho
    void remove(float temp);
    void printSorted();
    SensorData getMin();
    SensorData getMax();
    float getMedian();
    
    // Auxiliar
    void clear();
};

#endif