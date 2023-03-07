#include <Arduino.h>

void LED_ON (void * pvParameters);
void LED_OFF(void * pvParameters);

int LED =2; 

SemaphoreHandle_t semaphore;

void setup(){

Serial.begin(115200);
pinMode(LED, OUTPUT);
semaphore= xSemaphoreCreateMutex();
xTaskCreate(LED_ON, "ON", 10000, NULL, 1, NULL);
xTaskCreate(LED_OFF, "OFF", 10000, NULL, 1, NULL);
}

void loop(){}

void LED_ON (void * pvParameters){
    for(;;){
        xSemaphoreTake(semaphore, portMAX_DELAY);
        digitalWrite(LED, HIGH);
        delay(3000);
        xSemaphoreGive(semaphore);
    }
}

void LED_OFF (void * pvParameters){
    for(;;){
        xSemaphoreTake(semaphore, portMAX_DELAY);
        digitalWrite(LED, LOW);
        delay(1500);
        xSemaphoreGive(semaphore);
    }
}
