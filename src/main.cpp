
#include <Arduino.h>

/////////////////////////LIBRERIAS
#include <Adafruit_NeoPixel.h> //Incluimos la libreria de Adafruit NeoPixel con la que controlaremos los LED.
#include <Adafruit_Sensor.h>
///////////////////////Definición de pines
#define PINLEDRGB 5 // pin data 12
#define NUMPIXELS 1 // numero de leds en la tira
#define LDR 15
#define BUZZER 19
#define RELE 22
//////////////////////Definicion de variables
int num_mov = 0;
int inicio = 0;
int resettime = 30; // Periodo de tiempo en el que se resetea la cuenta de movimientos
int resetpito = 10;
boolean pitar = 0;   // Creamos una variable booleana que indica si debe o no pitar cada 10 segundos (apartado 4)
int num_pitidos = 0; // Numero de pitidos para activar el relé
byte sensorpir = 21; // pin de salida del sensor, en el Arduino es entrada.
////////////////////////////////////
Adafruit_NeoPixel pixels(NUMPIXELS, PINLEDRGB, NEO_GRB + NEO_KHZ800); // inicializamos el LED PIXEL
/////////////////////////////////////////////////
boolean check_ldr() // funcion LDR
{
    int data = 0;
    //////////////////////Leemos el LDR y salimos en serial
    data = analogRead(LDR); // Leemos el valor de LDR
    Serial.print("LDR: ");
    Serial.println(data);
    //////////////////////Valor LDR menor de 410
    if (data <= 410)
    {
        Serial.print("Es de noche\n");
        return 0;
    }
    ///////////////////////Valor LDR mayor de 410
    else if (data > 410)
    {
        Serial.print("Es de dia\n");
        return 1;
    }
}

void pita() ///////// función del buzzer
{
    ledcWriteTone(0, 200);     // Realiza el pitido
    Serial.println("Pitando"); // Indicamos en Serial el pitido
    delay(3000);               // Durante 3 segundos
    ledcWriteTone(0, 0);       // Realiza el pitido
}

void check_movs() ////////////// Encaso de que se detecte movimiento 3 veces
{
    if (num_mov == 3)
    {
        pita();
        pitar = 1; // Hacemos que pite cada 10 segundos
    }
}

void check_rele() ////////////función rele
{
    if (num_pitidos == 5) ////////// Si se activa 5 veces el zumbador se activa el rele
    {
        num_pitidos = 0;
        digitalWrite(RELE, HIGH); // activa el relé
        Serial.println("Relé activado");
        delay(3000);
        digitalWrite(RELE, LOW); // cierra el relé
        Serial.println("Relé desactivado");
    }
}

void clean_led() /////////// funcion simple de limpieza del LED
{
    pixels.clear();                                 // limpiamos
    pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // establecemos 20 (intensidad) en el nivel de verde de la matrz (R,G,B)
    pixels.show();                                  // Mostramos el color
}

void led_inicial() /////////// función del LED inicial dejandolo en rojo tenue
{
    pixels.clear();                                  // limpiamos
    pixels.setPixelColor(0, pixels.Color(20, 0, 0)); // establecemos 20 (intensidad) en el nivel de rojo de la matrz (R,G,B)
    pixels.show();                                   // Mostramos el color
    delay(5000);                                     // Hace una espera de 5 segundos con el LED en rojo.
    clean_led();
}

void setup()
{
    ////////////////////////////////////////////////// declaración de librerias
    ledcSetup(0, 1E5, 12); // Inicializamos el buzzer
    ledcAttachPin(27, 0);  // Establecemos el pin del buzzer
    /////////////////////////////////////////////////// declaración de pines
    pinMode(LDR, INPUT);
    pinMode(BUZZER, INPUT);
    pinMode(RELE, OUTPUT);
    pinMode(sensorpir, INPUT); // declaramos los pines de entrada y salida del sensor
    //////////////////////////////////////////////////// Inicializamiento
    analogReadResolution(10); // Establecemos el rango a 10 bits para que vaya de 0 a 1024
    pixels.begin();           // Inicializamos el objeto "pixels"
    Serial.begin(9600);       // conf. velocidad del monitor Serial
    led_inicial();
    ///////////////////////////////////////////////////
}

void loop() ///////////////////////////// INICIO DEL CODIGO
{
    ////////////////////////////////////////////////////////////
    int secstime = millis() / 1000; // Temporizamos en segundos desde que inicia el programa

    Serial.println("");
    Serial.print("Tiempo total: ");
    Serial.println(secstime);

    int tiempo = resettime - secstime; // Creamos una variable que cuenta el tiempo para el siguiente reseteo

    Serial.print("Tiempo reset: ");
    Serial.println(tiempo);
    //////////////////////////////////////////////////////////////
    if (tiempo <= 1)
    {
        resettime = resettime + 30; // Cuando llegamos a 0 En el tiempo, cambiamos el reset time y reseteamos movimientos
        num_mov = 0;
    }
    ///////////////////////////////////////////////////////////////
    int tiempopitar = resetpito - secstime; // Contaremos para que cada 10 segundos se repita el pitido
    Serial.print("Tiempo reset pito: ");
    Serial.println(tiempopitar);
    if (tiempopitar <= 1)
    {
        resetpito = resetpito + 10;
    }
    //////////////////////////////////////////////////////////////////
    Serial.print("Movimientos: ");
    Serial.println(num_mov);
    //////////////////////////////////////////////////////////////////
    boolean umbral = check_ldr();
    /////////////////////////////////////////////////////////////////
    if (umbral == 0)
    {                                       // Si no supera el umbral:
        if (digitalRead(sensorpir) == HIGH) // Si el sensor realiza una lectura
        {
            num_mov++;
            Serial.println("Detectado movimiento por el sensor pir");
            pixels.clear();                                  // limpiamos el posible color anterior
            pixels.setPixelColor(0, pixels.Color(0, 0, 50)); // establecemos 50 (intensidad) en el nivel de verde de la matrz (R,G,B)
            pixels.show();                                   // Mostramos el color
            delay(1500);                                     // Hace una espera de 5 segundos con el LED en azul.
            clean_led();
        }
        else
        {
            Serial.println("Ya no se detecta movimiento");
            pixels.clear(); // limpiamos el posible color anterior
        }
    }
    ////////////////////////////////////////////////////////////////////
    Serial.print("Variable pitar: ");
    Serial.println(pitar);
    /////////////////////////////////////////////////////////////////////
    if (pitar == 0)
    { // Si pitar está desactivado, comprobamos si hay 3 movimientos
        check_movs();
    }
    else if (pitar == 1 && tiempopitar <= 1)
    {
        pita();        // Si pitar está activado, hacemos que pite cada 10 segundos
        num_pitidos++; // Añadimos 1 al contador de activación de relé
    }
    //////////////////////////////////////////////////////////////////////
    Serial.println("Buzzer Sin pulsar "); // Si pulsamos el botón reseteamos la variable pitar para que deje de pitar cada 10.
    /////////////////////////////////////////////////////////////////////
    if (digitalRead(BUZZER) == HIGH)
    {
        Serial.println("Buzzer pulsado ");
        pitar = 0;
    }
    ////////////////////////////////////////////////////////////////////////
    check_rele(); // Comprobamos si hay que activar la manguera (relé).
    Serial.print("Número de pitidos (5 para rele): ");
    Serial.println(num_pitidos);
    delay(500); // Pequeño delay para que descanse el controlador.
}
