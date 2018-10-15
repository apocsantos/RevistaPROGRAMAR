//Thanks for the idea Bernardo Ferreira
//Thanks for the motivation RP ;) "Descontos é na RP!"
#include "HX711.h"
#include <OneWire.h> 
#include <DallasTemperature.h>


#define ONE_WIRE_BUS 4 //pino de dados do DS18B20 fica definido como 4
#define calibration_factor -7050.0 //este valor é obtido usando o SparkFun_HX711_Calibration sketch
#define DOUT  3
#define CLK  2

HX711 scale(DOUT, CLK);

// Prepara uma instancia oneWire para comuicar com dispositivos OneWire
//no caso o DS18B20
OneWire oneWire(ONE_WIRE_BUS); 
/********************************************************************/
//Passa a referencia oneWire para o sensor DS18B20 (DallasTemperature)
DallasTemperature sensors(&oneWire);
/********************************************************************/ 

int solenoidPin = 5;    //Este é o pino usado para controlar a solenoide

void setup() {
  
  Serial.begin(9600); //apenas para debug
  scale.set_scale(calibration_factor); //Carrega a calibração da celula de carga 
  scale.tare(); //Zera após a tara (no caso o recipiente)
  sensors.begin(); 
  pinMode(solenoidPin, OUTPUT); //Define o pino como output
}

void loop() {
//loop principal 

//código da celula
  Serial.print("Peso: ");
  Serial.print(scale.get_units(), 1); 
  Serial.print(" kg"); 
  Serial.println();
//end

//codigo da temperatura
 Serial.print(" Lendo temperatura..."); 
 sensors.requestTemperatures(); //manda executar a leitura da temperatura
 Serial.println("DONE"); 
/********************************************************************/
 Serial.print("Temperatura é: "); 
 Serial.print(sensors.getTempCByIndex(0)); //
//end


/**************PERMISSAS PARA ABRIR E FECHAR A VÁLVULA****************/
//quente
if(sensors.getTempCByIndex(0) > 15)
{
  digitalWrite(solenoidPin, HIGH); 
}
else{ digitalWrite(solenoidPin, LOW);}

//abaixo do nível minimo de água
if ( (scale.get_units(), 1) =< 3)
{
  digitalWrite(solenoidPin, HIGH); 
}
else{ digitalWrite(solenoidPin, LOW);}
//acima do nível maximo de água
if ( (scale.get_units(), 1) >= 4)
{
  digitalWrite(solenoidPin, HIGH); 
}
else{ digitalWrite(solenoidPin, LOW);}
/********************************************************************/

delay(5000); //aguarda 5 segundos
//end
}
