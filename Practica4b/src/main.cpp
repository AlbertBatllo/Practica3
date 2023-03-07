#include <Arduino.h>

void LED_ON (void * pvParameters);
void LED_OFF(void * pvParameters);

int LED = 2; 
int LED2 = 19; 

void setup(){

Serial.begin(115200);
pinMode(LED, OUTPUT);
pinMode(LED2, OUTPUT);
xTaskCreate(LED_ON, "ON", 10000, NULL, 1, NULL);
xTaskCreate(LED_OFF, "OFF", 10000, NULL, 1, NULL);
}

void loop(){}

void LED_ON (void * pvParameters){
    for(;;){
        digitalWrite(LED, HIGH);
        Serial.println("a");
        vTaskDelay(1000);
        digitalWrite(LED, LOW);
        vTaskDelay(1000);
    }
}

void LED_OFF (void * pvParameters){
    for(;;){
        digitalWrite(LED2, HIGH);
        Serial.println("b");
        vTaskDelay(500);
        digitalWrite(LED2, LOW);
        vTaskDelay(500);
    }
}
