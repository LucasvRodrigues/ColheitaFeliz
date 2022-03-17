#include <LiquidCrystal.h>
LiquidCrystal lcd (10,9,8,7,6,5);

#define PESO_MAXIMO 180.0

double obter_peso();
double obter_umd();
void controla_irrigacao(double peso, double umidade);

//Pino Sensor de Peso
const int sensor_peso = A0;

//Pino Sensor de Umidade
const int sensor_umidade = A5;

//Pinos LED RGB
const int vermelho = 2;
const int azul = 3;
const int verde = 4;

//Pino Bomba D'água 
const int motor = 13;

void setup() {
  	Serial.begin(9600);
  
  	// Definir pinos de saída
	pinMode(vermelho, OUTPUT);
  	pinMode(azul, OUTPUT);
  	pinMode(verde, OUTPUT);
  	pinMode(motor, OUTPUT);
  
  	// Para informar os parametros do lcd 
  	lcd.begin (16,2);
  
  	// Definir pinso de entrada
  	pinMode(sensor_peso, INPUT);
  	pinMode(sensor_umidade, INPUT);
}

void loop() {
  	// Limpa o display LCD
  	lcd.clear();
  
  	// Obtem o peso e exibe no display LCD
  	double peso = obter_peso();
  	lcd.setCursor(0,0);
  	lcd.print("PESO: ");
  	lcd.print(peso);
	
  	// Obtem a umidade e exibe no display LCD
  	double umidade = obter_umd();
  	lcd.setCursor(0,1);
  	lcd.print("UMD (%): ");
  	lcd.print(umidade);
  
  	// Efetua o controle da irrigação
  	controla_irrigacao(peso, umidade);
  
  	// Aguarda 200ms
  	delay(200);
}

double obter_peso() {
  	// Lê o sensor de peso
  	double result = analogRead(sensor_peso);
  	// Converte o valor lido para Kg e retorna
  	return result * PESO_MAXIMO / 1023.0;
}

double obter_umd() {
  	// Lê o sensor de umidade
  	float sinal = analogRead(sensor_umidade);
  	// Converte o valor lido para porcentagem e retorna
  	return map(sinal, 1023, 0, 0, 100);
}

void controla_irrigacao(double peso, double umidade) {
  	if(peso > 50) {
        if(umidade > 40) {
          	// AMARELO - Umidade registrada maior que 40%
          	digitalWrite(verde, HIGH);
          	digitalWrite(vermelho, HIGH);
    		digitalWrite(azul, LOW);
          
            if(umidade > 60) {
              	// VERDE - Umidade registrada maior que 60%
          		digitalWrite(vermelho, LOW);
            }
          
            //Desligar sistema de irrigação
            digitalWrite(motor, LOW);
            Serial.println("Irrigação parada...");
        }
        else {
            //VERMELHO - Umidade registrada menor ou igual a 40%
            digitalWrite(vermelho, HIGH);
            digitalWrite(azul, LOW);
            digitalWrite(verde, LOW);

            //Acionar sistema de irrigação
            digitalWrite(motor, HIGH);
            Serial.println("Irrigando...");
        }
    }
    else {
      // BRANCO - Peso insuficiente
      digitalWrite(vermelho, HIGH);
      digitalWrite(verde, HIGH);
      digitalWrite(azul, HIGH);
      
      //Desligar sistema de irrigação
      digitalWrite(motor, LOW);
      Serial.println("Peso insuficiente...");
    }
}