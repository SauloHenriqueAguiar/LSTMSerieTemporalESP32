#include <EloquentTinyML.h>
// temperatura_model.h contém a matriz que você exportou da etapa anterior com xxd ou tinymlgen
#include "temperatura_modelTF.h"

#define NUMBER_OF_INPUTS 1
#define NUMBER_OF_OUTPUTS 1
// em projetos futuros você pode precisar ajustar esse valor: é um processo de tentativa e erro
#define TENSOR_ARENA_SIZE 2*1024

const int LM35 = A0; // Define o pino que lera a saída do LM35
float temperatura; // Variável que armazenará a temperatura medida

Eloquent::TinyML::TfLite<NUMBER_OF_INPUTS, NUMBER_OF_OUTPUTS, TENSOR_ARENA_SIZE> ml;


void setup() {
    Serial.begin(115200);
    ml.begin(temperatura_modelTF);
}

void loop() {
   

   
    temperatura = (float(analogRead(LM35))*5/(1023))/0.01;
    float x = temperatura;
   
    float input[1] = { x };
    float predicted = ml.predict(input);

    Serial.print(" temperatura");
    Serial.print(x);
    Serial.print(") = ");
   
    Serial.print("\t predicted: ");
    Serial.println(predicted);
    delay(1000);

   
 

    
}
