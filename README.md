# Practica 3: Sistemes operatius en temps real

L'objectiu de la pràctica es comprendre el funcionament d'un sistema operatiu en temps real
Per a aquesta practica generarem varies tasques i veurem com sexecuten dividint el temps dús de la cpu.

## Codi

```

#include <Arduino.h>

void anotherTask( void * parameter );
void setup()
{
    Serial.begin(115200);
    /* we create a new task here */
    xTaskCreate(anotherTask, "another Task", 10000, NULL, 1, NULL); /* Task handle to keep track of created task */
}
 
/* the forever loop() function is invoked by Arduino ESP32 loopTask */
void loop()
{
    Serial.println("this is ESP32 Task");
    delay(1000);
}
 
/* this function will be invoked when additionalTask was created */
void anotherTask( void * parameter )
{
    /* loop forever */
    for(;;)
    {
        Serial.println("this is another Task");
        delay(1000);
    }
    /* delete a task when finish,
    this will never happen because this is infinity loop */
    vTaskDelete( NULL );
}
```

## Explicació del Codi

**Set Up:**

Al setup creem la tasca amb la funció xTaskCreate(), els paràmetres de la qual són els següents:

- anotherTask: Funció que executa la tasca.
- "anotherTask": Nom que li donem a la tasca.
- 10000: Tamany de la tasca "Stack size" (en bytes).
- NULL: Paràmetre de la tasca.
- 1:  Prioritat de la tasca. Com major sigui el nombre, major serà la prioritat.
- NULL: Maneig de la tasca.

```
void setup(){
    Serial.begin(112500);
    xTaskCreate( anotherTask, "another Task", 10000, NULL, 1, NULL); 
    }
```

**Loop:**

```
void loop()
{
    Serial.println("this is ESP32 Task");
    delay(1000);
}
```

La funció anotherTask és un bucle for infinit que mostrarà pel terminal: "this is another Task", i  aplicarà un delay de 1000ms posteriorment:

```
void anotherTask( void * parameter )
{
    /* loop forever */
    for(;;)
    {
        Serial.println("this is another Task");
        delay(1000);
    }
    /* delete a task when finish,
    this will never happen because this is infinity loop */
    vTaskDelete( NULL );
}
```

# Practica 3b
L'objectiu d'aquesta part de la pràctica és realitzar un programa que utilitzi dues tasques: una encén un led i una altra l'apaga aquestes tasques han d'estar sincronitzades.
 
## Codi

```
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
```

