#ifndef DHTSIM_H
#define DHTSIM_H

#include "SensorData.h"
#include <cstdlib> // rand

class DHTSim {
public:
    // Simula uma leitura do sensor
    static SensorData ler() {
        // Gera temperatura entre 20.0 e 40.0 (típico de operação industrial)
        float t = 20.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 20.0));
        
        // Gera umidade entre 30% e 80%
        float h = 30.0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 50.0));

        return {t, h};
    }
};

#endif