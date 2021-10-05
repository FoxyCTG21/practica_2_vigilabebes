# practica_2_vigilabebes
Teniendo en cuenta el siguiente listado de materiales:
• ESP32
• Protoboard pequeña de pruebas
• LEDS RGB basados en WS2812B IP30
• Sensor PIR HC-SR501
• Sensor TH DHT11
• Zumbador pasivo
• Fotorresistor GL5537 LDR
• Módulo de relé de 2 canales optoacoplado bajo activador por flanco 5V
• Componentes simples (R, C) y cables de conexión
• Impresora 3D de resina (tal vez)
Más cualquier otro accesorio que no sea imprescindible para verlo funcionando en pruebas (por
ejemplo, una batería para que funcione desconectado de la red, conexión inalámbrica...), diseñar
(primero a nivel hardware con esquema visual y eléctrico) un sistema basado en microcontrolador que
cumpla una serie de requisitos:
• Se requiere tener en una habitación un sistema basado en microcontrolador que, nada más
arrancar, se quede encendido un led durante un tiempo (para pruebas 5 segundos) y al detectar
un movimiento accione ese led (luz de compañía) durante otro tiempo (para pruebas 3
segundos).
• El led no se encenderá en ningún caso si tenemos una luz ambiente por encima de un
determinado umbral que consideremos adecuado.
• Si detecta movimiento varias veces (3) en menos de 2 minutos, debe accionar un pitido de 3
segundos en un zumbador que tiene conectado (digamos que tenemos un cable muy largo,
porque tampoco queremos molestar al bebé, sino avisar a los padres).
• Si se ha llegado a accionar el pitido, seguirá sonando cada 10 segundos hasta que el
microcontrolador detecte alguna señal de entrada (pulsador) que le haga pensar que los padres
ya están avisados.
• Si llega a pitar 5 veces, se abrirá una manguera de agua fría sobre la cama de los padres
(accionada por relé).
• EXTRA: el microcontrolador debe enviar con una periodicidad de un paquete al minuto los
datos de temperatura y humedad a un servidor IOT en la nube como Thingspeak.
Se debe explicar todo el conexionado y los elementos empleados y cualquier otra mejora al sistema
que no modifique la funcionalidad básica.
