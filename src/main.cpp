#include <Arduino.h>

int SENSOR = 21;
int LUZ = 22;
int LDR = 4;
int ALARMA = 19;
//////////////////////////////////////////////////////////////////////////////////////
unsigned long millisanterior;
int tiempo_luz = 0;
int tiempo_alarma_disparo = 0;
int val_ldr = 0;
int estado_anterior_sensor = 0;
int veces_sensor_disparado = 0;

int casos = 0;

void setup() {
    Serial.begin(9600);
//////////////////////////////////////////////////////////////////////////////////////
    pinMode(SENSOR, INPUT);
    pinMode(LDR, INPUT);
    pinMode(LUZ, OUTPUT);
    pinMode(ALARMA, OUTPUT);
    pinMode(23, OUTPUT);
//////////////////////////////////////////////////////////////////////////////////////
    digitalWrite(23, HIGH);
    delay(5000);
    digitalWrite(23, LOW);
}

void loop() {
    if(digitalRead(SENSOR) == HIGH && analogRead(LDR) <= 500){ //Si se dispara el sensor se enciende la luz
        digitalWrite(LUZ, HIGH);
        tiempo_luz = 0;
    }
//////////////////////////////////////////////////////////////////////////////////////
    if((millis() - millisanterior) >= 1000){        //Reloj del programa donde se toma el tiempo
        millisanterior=millis();
        tiempo_luz++;
        if(veces_sensor_disparado >= 1){
            tiempo_alarma_disparo++;
        }
    }
//////////////////////////////////////////////////////////////////////////////////////
    if(tiempo_luz >= 3 || analogRead(LDR) >= 500){      //Si tanto la luz como el LDR se superan, se apaga la luz
        digitalWrite(LUZ, LOW);
    }
//////////////////////////////////////////////////////////////////////////////////////
    if(digitalRead(SENSOR) == 1 && estado_anterior_sensor == 0){        //El sensor se dispara, cuenta las veces disparadas
        estado_anterior_sensor = 1;
        veces_sensor_disparado++;
    }
    if(digitalRead(SENSOR) == 0 && estado_anterior_sensor == 1){
        estado_anterior_sensor = 0;
    }
//////////////////////////////////////////////////////////////////////////////////////
    if(tiempo_alarma_disparo >= 8){     //Si se aplica un numero mayor de segundos en la alarma se reinicia
        tiempo_alarma_disparo = 0;
        veces_sensor_disparado = 0;
    }
//////////////////////////////////////////////////////////////////////////////////////
//    val_ldr = analogRead(LDR);
    Serial.println(tiempo_alarma_disparo);

    switch (casos) //Vamos a pasar todo lo de arriba a casos para organizar y facilitar los tramos
        {
        case 0:
            
            break;
        case 1:

            break;
        case 2:




















}