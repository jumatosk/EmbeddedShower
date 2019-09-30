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
//#include<idDHT11.h>

//Funções
void iniciaLeds();
void iniciaSensorPresenca();
int getTemperatura();

void setup() {
  // put your setup code here, to run once:
  iniciaLeds();
  iniciaSensorPresenca();
  
  //duvida na funcao Serial.begin() -> sensor de presença e temperatura utilizam essa funcao no setup
  //é necessário duas declarações?

}

void loop() {
  // put your main code here, to run repeatedly:

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

int getTemperatura(){
  
}
