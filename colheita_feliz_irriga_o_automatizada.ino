#include <LiquidCrystal.h>
LiquidCrystal lcd (10,9,4,7,3,5);

void monitorar_umd(float sinal);

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
  
  	//Definir pinos de saída
	pinMode(vermelho, OUTPUT);
  	pinMode(azul, OUTPUT);
  	pinMode(verde, OUTPUT);
  	pinMode(motor, OUTPUT);
  	Serial.begin(9600); 
  	//Para informar os parametros do lcd 
  	lcd.begin (16,2);   
}

void loop() {
	
  	//Ler do sinal do sensor
  	float sinal_umd = analogRead(sensor_umidade);
  
  	monitorar_umd(sinal_umd);
  	delay(2000);
}


void monitorar_umd(float sinal) {
  	
  	//Transformar o valor analógico recebido em porcentagem
  	int umidade = map(sinal, 1023, 0, 0, 100);
  
  	Serial.print("UMD (%): ");
  	Serial.println(umidade);
  
  	if(umidade > 40) {
    	
      	/*VERDE - Umidade registrada maior que 60%
          AMARELO - Umidade registrada maior que 40%*/
    	digitalWrite(vermelho, umidade > 60? LOW : HIGH);
    	digitalWrite(azul, LOW);
    	digitalWrite(verde, HIGH);
    
      	//Desligar sistema de irrigação
  		digitalWrite(motor, LOW);
    
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
  
  	return;
}