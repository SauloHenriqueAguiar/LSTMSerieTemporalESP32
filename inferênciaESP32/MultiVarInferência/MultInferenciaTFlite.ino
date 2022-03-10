#include <EloquentTinyML.h>
// temperatura_model.h contém a matriz que você exportou da etapa anterior com xxd ou tinymlgen
#include "multivar_modelTF.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
 
#define PressaoaNivelDoMar_HPA (1013.25)
 
Adafruit_BME280 bme;
#define NUMBER_OF_INPUTS 3
#define NUMBER_OF_OUTPUTS 72
// em projetos futuros você pode precisar ajustar esse valor: é um processo de tentativa e erro
#define TENSOR_ARENA_SIZE 2*1024



Eloquent::TinyML::TfLite<NUMBER_OF_INPUTS, NUMBER_OF_OUTPUTS, TENSOR_ARENA_SIZE> ml;


void setup() {
    Serial.begin(115200);
    ml.begin(multivar_modelTF);
    bme.begin();
}

void loop() {
   
    float temp     = bme.readTemperature();
    float umid     = bme.readHumidity();
    float pressao  = bme.readPressure() / 100.0F;
   
   
    float x = temp;
    float y = umid;
    float z = pressao;
    
    float input[3] = { x, y, z };
    float predicted = ml.predict(input);

    Serial.print(" temperatura");
    Serial.print(x);
    Serial.print(") = ");

    Serial.print(" Umidade");
    Serial.print(y);
    Serial.print(") = ");

    Serial.print(" Pressão ");
    Serial.print(z);
    Serial.print(") = ");
    
    Serial.print("\t predicted: ");
    Serial.println(predicted);
    delay(1000);

   
 

    
}
