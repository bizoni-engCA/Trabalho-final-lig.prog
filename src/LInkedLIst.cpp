#include "LinkedList.h"
#include <iostream>
//Construtor
LinkedList::LinkedList() : head(nullptr), tamanho(0){}
//Destrutor
LinkedList::~LinkedList(){
    clear();
}
//Inserção Ordenada
void LinkedList::insertOrdered(SensorData data){}

//Limpar lista
void LinkedList::clear(){}

//Imprimir lista ordenada
void LinkedList::printSorted(){}

//Obtem o minimo
SensorData LinkedList::getMin(){}

//Obtem o maximo
SensorData LinkedList::getMax(){}

//Obtem a mediana
float LinkedList::getMedian(){}
