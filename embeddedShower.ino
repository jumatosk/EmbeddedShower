//Projeto: Embedded Shower
//Aluna: Juliana Matos
//Disciplina: Fundamentos de Sistemas Embarcados

//LED's
#define temperaturaMinima 10 
#define temperaturaMedia 9
#define temperaturaMaxima 8
#define agua 11

//Sensor de presença
#define sensorPresenca 4

//Sensor de temperatura
#define sensorTemperatura 2 //Porta digital
#define sensorTInterrupcao 0 
#include<idDHT11.h>

//Funções
void iniciaLeds();
void iniciaSensorPresenca();
bool identificaPresenca();
void sensorTemperaturaWrapper(); //declaração da função de controle da interrupção
void loopDHT(); //atualiza a leitura do sensor
void tempoLigado();
idDHT11 DHT11(sensorTemperatura, sensorTInterrupcao, sensorTemperaturaWrapper); 

void setup() {
  // put your setup code here, to run once:
   // Serial.begin(9600) -> taxa de transferencia de bits
  Serial.begin(9600);
  iniciaLeds();
  iniciaSensorPresenca();
  
  //duvida na funcao Serial.begin() -> sensor de presença e temperatura utilizam essa funcao no setup
  //é necessário duas declarações?

}

//Variavel que verifica presenca
bool verificaPresenca = identificaPresenca();

//Variaveis do sensor de temperatura
float grausCelsius;

void loop() {
    loopDHT();
  Serial.println("Temperatura atual ");
  Serial.println(grausCelsius);
  tempoLigado();
  //incluir o Serial.print(temperaturaEmCelsius);
}

void iniciaLeds(){
  pinMode(temperaturaMinima, OUTPUT);
  pinMode(temperaturaMedia, OUTPUT);
  pinMode(temperaturaMaxima, OUTPUT);
  pinMode(agua, OUTPUT);
}

void iniciaSensorPresenca(){
  pinMode(sensorPresenca, INPUT);
}

bool identificaPresenca(){
  bool verificaPresenca = digitalRead(sensorPresenca);
  return verificaPresenca;
}

void sensorTemperaturaWrapper(){
    DHT11.isrCallback();
}

void loopDHT(){
#define tempoLeitura 1000
static unsigned long delayLeitura = millis() + tempoLeitura + 1;
static bool request = false;

  if ((millis() - delayLeitura) > tempoLeitura) { 
      if (!request) {
         DHT11.acquire(); 
         request = true;
      }
  }

  if (request && !DHT11.acquiring()) {
    request = false;

    int result = DHT11.getStatus();
      
    switch (result)
    {
    case IDDHTLIB_OK: 
        Serial.println("Leitura OK"); 
        break;
    case IDDHTLIB_ERROR_CHECKSUM: 
        Serial.println("Erro\n\r\tErro Checksum"); 
        break;
    case IDDHTLIB_ERROR_ISR_TIMEOUT: 
        Serial.println("Erro\n\r\tISR Time out"); 
        break;
    case IDDHTLIB_ERROR_RESPONSE_TIMEOUT: 
        Serial.println("Erro\n\r\tResponse time out"); 
        break;
    case IDDHTLIB_ERROR_DATA_TIMEOUT: 
        Serial.println("Erro\n\r\tData time out erro"); 
        break;
    case IDDHTLIB_ERROR_ACQUIRING: 
        Serial.println("Erro\n\r\tAcquiring"); 
        break;
    case IDDHTLIB_ERROR_DELTA: 
        Serial.println("Erro\n\r\tDelta time to small"); 
        break;
    case IDDHTLIB_ERROR_NOTSTARTED: 
        Serial.println("Erro\n\r\tNao iniciado"); 
        break;
    default: 
        Serial.println("Erro Desconhecido"); 
        break;
    }
    
    float valor = DHT11.getCelsius();
     
    if (!isnan(valor)) {             
      grausCelsius = valor;
    }
    delayLeitura = millis();     
  }
}

void tempoLigado(){
  
  if(grausCelsius >= 20 && grausCelsius <= 25 && verificaPresenca){
      digitalWrite(temperaturaMinima, HIGH);
      digitalWrite(agua, HIGH);
      delay(1000);
      digitalWrite(temperaturaMinima, LOW);
      digitalWrite(agua, LOW);
      delay(5000);

  }
}
