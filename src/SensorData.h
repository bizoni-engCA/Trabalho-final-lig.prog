#ifndef SENSORDATA_H
#define SENSORDATA_H
#include <iostream>

struct SensorData {
    float temp; // Critério de ordenação principal
    float hum;

    // Sobrecarga de operadores para facilitar a comparação na Árvore e na Lista
    bool operator<(const SensorData& outro) const {
        return temp < outro.temp;
    }

    bool operator>(const SensorData& outro) const {
        return temp > outro.temp;
    }

    // Facilita o print
    void print() const {
        std::cout << "[DHT] Temp: " << temp << " C | Hum: " << hum <<  "\n";
    }
};

#endif