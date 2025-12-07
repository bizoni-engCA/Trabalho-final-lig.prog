#include "DHT.h"

// --- Configurações do Hardware ---
#define DHTPIN 3      // Pino digital conectado ao sensor (verifique sua montagem)
#define DHTTYPE DHT11 // Defina aqui o modelo: DHT11 ou DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  Serial.println(F("Iniciando leitura do sensor DHT..."));
}

void loop() {
  // O sensor requer um intervalo mínimo de 2 segundos entre leituras
  delay(2000);

  // Leitura da umidade e temperatura (Celsius)
  float umidade = dht.readHumidity();
  float temperatura = dht.readTemperature();

  // Verifica se houve falha na leitura (retorna NaN se falhar)
  if (isnan(umidade) || isnan(temperatura)) {
    Serial.println(F("Erro: Falha ao ler do sensor DHT!"));
    return;
  }

  // --- Saída Formatada ---
  // Formato ideal para copiar os dados depois ou integrar via Serial
  Serial.print(F("Umidade: "));
  Serial.print(umidade);
  Serial.print(F("% | Temperatura: "));
  Serial.print(temperatura);
  Serial.println(F("°C"));
}
