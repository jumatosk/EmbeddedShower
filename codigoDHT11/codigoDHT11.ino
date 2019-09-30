// Programa: Sensor de Temperatura e Umidade - Programa básico para teste do sensor DHT11
// Autor: Gleydson Zeca Monteiro

#include "DHT.h"                                  // Adiciona biblioteca DHT.h - referente ao sensor DHT11

#define DHTPIN A1                                 // Define o pino A1 do Arduino para receber o sinal do sensor DHT11
#define DHTTYPE DHT11                             // Define qual o modelo do sensor DHT que está sendo utilizado
 
DHT dht(DHTPIN, DHTTYPE);                         // Adiciona função dht da biblioteca DHT, a qual usa as definições implentadas nas linhas 6 e 7

 
void setup()                                      // Chama função setup() que é uma das funções principais do Arduino 
{                                                 // Abertura da função setup()
  Serial.begin(9600);                             // Inicia o monitor serial e informa qual a taxa de transmissão de dados (9600)
  Serial.println("Teste sensor DHT11");           // Solicita que seja impresso no monitor serial o texto Teste sensor DHT11
  dht.begin();                                    // Solicita que inicie a função dht existente na biblioteca DHT
}                                                 // Fechamento da função setup()

 
void loop()                                       // Chama função loop() que é uma das funções principais do Arduino 
{                                                 // Abertura da função loop()
  float umidade = dht.readHumidity();             // Definição de uma variável chamada umidade como float a qual irá receber o valor de umidade lido pelo sensor DHT
  float temperatura = dht.readTemperature();      // Definição de uma variável chamada temperatura como float a qual irá receber o valor de temperatura lido pelo sensor DHT
  
  // Testa se retorno é verdadeiro
  if (isnan(temperatura) || isnan(umidade))       // Função condicional if (se) de verificação
  {                                               // Abertura da função condicional if
    Serial.println("Falha ao ler sensor DHT");    // Solicita que seja impresso no monitor serial o texto Teste sensor DHT11
  }                                               // Fechamento da função condicional if 
  else                                            // Função condicional else (senão)
  {                                               // Abertura da função condicional else
    Serial.print("Umidade: ");                    // Solicita que seja impresso no monitor serial o texto Umidade
    Serial.print(umidade);                        // Solicita que seja impresso no monitor serial a variável umidade
    Serial.print("%");                            // Solicita que seja impresso no monitor serial o texto %
    Serial.print("Temperatura: ");                // Solicita que seja impresso no monitor serial o texto Temperatura
    Serial.print(temperatura);                    // Solicita que seja impresso no monitor serial a variável temperatura
    Serial.println("*C");                         // Solicita que seja impresso no monitor serial o texto *C
    delay(1000);                                  // Adiciona um atraso de 1000ms para que o Arduino não fique lendo continuamente
  }                                               // Fechamento da função condicional else
}                                                 // Fechamento da função loop()
