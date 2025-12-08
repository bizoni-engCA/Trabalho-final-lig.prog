#include "LinkedList.h"
#include <iostream>
//Construtor
LinkedList::LinkedList() : head(nullptr), tamanho(0){}
//Destrutor
LinkedList::~LinkedList(){
    clear();
}
//Inserção Ordenada
void LinkedList::insertOrdered(SensorData data){
    ListNode* novoNo = new ListNode(data);
    // Caso lista vazia ou novoNo menor que o head
    if (head == nullptr || data < head->data) {
        novoNo->next = head;
        head = novoNo;
    } else {
        // Percorre para encontrar a posição correta
        ListNode* atual = head;
        while (atual->next != nullptr && atual->next->data < data) {
            atual = atual->next;
        }
        novoNo->next = atual->next;
        atual->next = novoNo;
    }
    tamanho++;
}

//Limpar lista
void LinkedList::clear(){
    ListNode* atual = head;
    while (atual != nullptr) {
        ListNode* temp = atual;
        atual = atual->next;
        delete temp;
    }
    head = nullptr;
    tamanho = 0;
}

//Imprimir lista ordenada
void LinkedList::printSorted(){
    ListNode* atual = head;
    while (atual != nullptr) {
        atual->data.print();
        atual = atual->next;
    }
}

//Obtem o minimo
SensorData LinkedList::getMin(){
    if (head != nullptr) {
        return head->data;
    }
    return {0.0, 0.0}; // Retorno de erro
}

//Obtem o maximo
SensorData LinkedList::getMax(){
    if (head == nullptr) {
        return {0.0, 0.0}; // Retorno de erro
    }
    ListNode* atual = head;
    while (atual->next != nullptr) {
        atual = atual->next;
    }
    return atual->data;
}

//Obtem a mediana
float LinkedList::getMedian(){
    if (tamanho == 0) return 0.0; // Lista vazia

    ListNode* atual = head;
    int meio = tamanho / 2;

    // Percorre até o meio
    for (int i = 0; i < meio; i++) {
        atual = atual->next;
    }

    // Se tamanho é ímpar, retorna o valor do meio
    if (tamanho % 2 != 0) {
        return atual->data.temp;
    } else {
        // Se par, retorna a média dos dois valores centrais
        float temp1 = atual->data.temp;
        float temp2 = head->data.temp;
        ListNode* aux = head;
        for (int i = 0; i < meio - 1; i++) {
            aux = aux->next;
        }
        temp2 = aux->data.temp;
        return (temp1 + temp2) / 2.0;
    }
}
