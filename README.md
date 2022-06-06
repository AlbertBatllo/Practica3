# Practica4: Sistemes operatius en temps real

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

- anotherTask: la funció que executa la tasca.
- "anotherTask": és el nom que li donem a la tasca.
- 10000: és el tamany de la tasca ("Stack size").
- NULL: és el paràmetre de la tasca (en aquest cas no requereix cap).
- 1: és la prioritat de la tasca. Com major sigui el nombre, major serà la prioritat.
- NULL: és l'identificador de la tasca.

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


# Practica 4b
